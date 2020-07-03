// Created by tz301 on 2020/07/01

#include "asr/asr/online_decoder.h"

#include <utility>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-compare"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-variable"

#include "boost/algorithm/string.hpp"
#include "nnet3/am-nnet-simple.h"
#include "nnet3/nnet-utils.h"

#pragma GCC diagnostic pop

namespace tz_asr {

Decodable::Decodable(kaldi::Matrix<float> prob, const std::vector<int> &pdf_ids,
                     const kaldi::Vector<float> &log_priors,
                     int num_frames_decoded)
    : prob_(std::move(prob)),
      pdf_ids_(pdf_ids),
      num_frames_decoded_(num_frames_decoded) {
  if (log_priors.Dim() != 0) {
    prob_.AddVecToRows(-1.0, log_priors);
  }
}

float Decodable::LogLikelihood(int frame, int index) {
  return prob_(frame - num_frames_decoded_, pdf_ids_[index]);
}

bool Decodable::IsLastFrame(int frame) const {
  return frame == NumFramesReady() - 1;
}

int Decodable::NumFramesReady() const {
  return prob_.NumRows() + num_frames_decoded_;
}

int Decodable::NumIndices() const { return prob_.NumCols(); }

OnlineDecoder::OnlineDecoder(const std::string &model_dir)
    : symbol_table_(ReadSymbolTable(model_dir + "/words.txt")),
      hclg_fst_(fst::ReadFstKaldiGeneric(model_dir + "/HCLG.fst")),
      online_decoder_(*hclg_fst_, DecoderConfig()),
      transition_model_(std::make_shared<kaldi::TransitionModel>()),
      pdf_ids_(std::make_shared<std::vector<int>>()),
      log_priors_(std::make_shared<kaldi::Vector<float>>()),
      num_frames_decoded_(0) {
  ReadTransitionModel(model_dir + "/final.mdl");
  online_decoder_.InitDecoding();
}

std::string OnlineDecoder::Decode(const kaldi::Matrix<float> &prob,
                                  bool is_end) {
  Decodable decodable(prob, *pdf_ids_, *log_priors_, num_frames_decoded_);
  num_frames_decoded_ = decodable.NumFramesReady();
  online_decoder_.AdvanceDecoding(&decodable);

  kaldi::Lattice lattice;
  online_decoder_.GetBestPath(&lattice, is_end);

  std::string transcript;
  if (lattice.Start() != fst::kNoStateId) {
    std::vector<int> alignment;
    std::vector<int> words;
    kaldi::LatticeWeight weight;
    fst::GetLinearSymbolSequence(lattice, &alignment, &words, &weight);

    for (const auto &word : words) {
      transcript += symbol_table_.Find(word);
    }
  }
  return transcript;
}

void OnlineDecoder::Reset() {
  online_decoder_.InitDecoding();
  num_frames_decoded_ = 0;
}

OnlineDecoder::~OnlineDecoder() = default;

fst::SymbolTable OnlineDecoder::ReadSymbolTable(const std::string &words_txt) {
  std::ifstream ifs(words_txt);
  if (!ifs.is_open()) {
    throw std::invalid_argument("Error open file: " + words_txt + ".");
  }

  std::string line;
  fst::SymbolTable symbol_table;
  while (getline(ifs, line)) {
    std::vector<std::string> fields;
    boost::split(fields, line, boost::is_space());
    if (fields.size() == 2) {
      auto key = static_cast<int64_t>(std::stoi(fields[1]));
      symbol_table.AddSymbol(fields[0], key);
    } else {
      std::string msg = "Error format for " + words_txt + ": " + line + ".";
      throw std::invalid_argument(msg);
    }
  }
  ifs.close();
  return symbol_table;
}

kaldi::LatticeFasterDecoderConfig OnlineDecoder::DecoderConfig() {
  kaldi::LatticeFasterDecoderConfig decoder_config;
  decoder_config.min_active = 200;
  decoder_config.max_active = 7000;
  decoder_config.beam = 15.0;
  decoder_config.lattice_beam = 6.0;
  return decoder_config;
}

void OnlineDecoder::ReadTransitionModel(
    const std::string &transition_model_file) {
  bool binary;
  kaldi::Input ki(transition_model_file, &binary);
  transition_model_->Read(ki.Stream(), binary);

  kaldi::nnet3::AmNnetSimple am_nnet;
  am_nnet.Read(ki.Stream(), binary);

  kaldi::nnet3::Nnet *nnet = &(am_nnet.GetNnet());
  SetBatchnormTestMode(true, nnet);
  SetDropoutTestMode(true, nnet);

  kaldi::nnet3::CollapseModel(kaldi::nnet3::CollapseModelConfig(), nnet);
  *log_priors_ = am_nnet.Priors();
  log_priors_->ApplyLog();

  for (int i = 0; i <= transition_model_->NumTransitionIds(); ++i) {
    pdf_ids_->push_back(transition_model_->TransitionIdToPdf(i));
  }
}

}  // namespace tz_asr
