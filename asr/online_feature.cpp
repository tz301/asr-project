// Created by tz301 on 2020/06/19

#include "asr/online_feature.h"

#include <string>

namespace tz_asr {

/**
 * @brief Read mfcc options from config file.
 * @param config_file mfcc config file.
 * @return mfcc options.
 */
kaldi::MfccOptions ReadMfccOptions(const std::string &config_file) {
  kaldi::MfccOptions mfcc_opts;
  kaldi::ReadConfigFromFile(config_file, &mfcc_opts);
  return mfcc_opts;
}

/**
 * @brief Mfcc extractor accept waveform.
 * @param online_mfcc online mfcc extractor.
 * @param sample_rate sample rate.
 * @param waveform wave form data.
 * @param is_end is end.
 */
void MfccAcceptWaveform(const std::unique_ptr<kaldi::OnlineMfcc> &online_mfcc,
                        float sample_rate, const std::vector<char> &waveform,
                        bool is_end) {
  auto cols = waveform.size() / 2;
  std::unique_ptr<float[]> waveform_array(new float[cols]);

  char *buffer = const_cast<char *>(&waveform[0]);
  uint16_t *waveform_ptr = reinterpret_cast<uint16_t *>(buffer);
  for (unsigned i = 0; i < cols; i++) {
    int16_t k = *waveform_ptr++;
    waveform_array[i] = k;
  }

  kaldi::SubVector<float> wave(waveform_array.get(), cols);
  online_mfcc->AcceptWaveform(sample_rate, wave);

  if (is_end) {
    online_mfcc->InputFinished();
  }
}

OnlineMfccExtractor::OnlineMfccExtractor(const std::string &config_file)
    : mfcc_opts_(ReadMfccOptions(config_file)),
      online_mfcc_(std::unique_ptr<kaldi::OnlineMfcc>(
          new kaldi::OnlineMfcc(mfcc_opts_))) {}

void OnlineMfccExtractor::AcceptWaveform(float sample_rate,
                                         const std::vector<char> &waveform,
                                         bool is_end) {
  MfccAcceptWaveform(online_mfcc_, sample_rate, waveform, is_end);
}

unsigned OnlineMfccExtractor::NumFramesReady() const {
  return online_mfcc_->NumFramesReady();
}

unsigned OnlineMfccExtractor::Dim() const { return online_mfcc_->Dim(); }

kaldi::Matrix<float> OnlineMfccExtractor::GetFrames(unsigned start,
                                                    unsigned end) {
  kaldi::Matrix<float> mfcc(end - start, Dim());
  for (unsigned frame = start, row = 0; frame < end; frame++, row++) {
    kaldi::Vector<float> one_row(Dim());
    online_mfcc_->GetFrame(frame, &one_row);
    mfcc.CopyRowFromVec(one_row, row);
  }
  return mfcc;
}

OnlineMfccExtractor::~OnlineMfccExtractor() = default;

OnlineIvectorExtractor::OnlineIvectorExtractor(const std::string &iv_dir)
    : mfcc_opts_(ReadMfccOptions(iv_dir + "/mfcc.conf")),
      ivector_conf_(ReadIvectorConfig(iv_dir)),
      ivector_info_(ivector_conf_),
      online_mfcc_(std::unique_ptr<kaldi::OnlineMfcc>(
          new kaldi::OnlineMfcc(mfcc_opts_))),
      online_ivector_(ivector_info_, online_mfcc_.get()) {}

void OnlineIvectorExtractor::AcceptWaveform(float sample_rate,
                                            const std::vector<char> &waveform,
                                            bool is_end) {
  MfccAcceptWaveform(online_mfcc_, sample_rate, waveform, is_end);
}

unsigned OnlineIvectorExtractor::NumFramesReady() const {
  return online_ivector_.NumFramesReady();
}

unsigned OnlineIvectorExtractor::Dim() const { return online_ivector_.Dim(); }

kaldi::Vector<float> OnlineIvectorExtractor::GetFrame(unsigned frame) {
  kaldi::Vector<float> ivector(Dim());
  online_ivector_.GetFrame(frame, &ivector);
  return ivector;
}

OnlineIvectorExtractor::~OnlineIvectorExtractor() = default;

kaldi::OnlineIvectorExtractionConfig OnlineIvectorExtractor::ReadIvectorConfig(
    const std::string &iv_dir) {
  kaldi::OnlineIvectorExtractionConfig config;
  config.cmvn_config_rxfilename = iv_dir + "/online_cmvn.conf";
  config.diag_ubm_rxfilename = iv_dir + "/final.dubm";
  config.global_cmvn_stats_rxfilename = iv_dir + "/global_cmvn.stats";
  config.ivector_extractor_rxfilename = iv_dir + "/final.ie";
  config.lda_mat_rxfilename = iv_dir + "/final.mat";
  config.splice_config_rxfilename = iv_dir + "/splice.conf";
  return config;
}

OnlineFeaturePipeline::OnlineFeaturePipeline(const std::string &ivector_dir)
    : online_mfcc_(ivector_dir + "/mfcc.conf"), online_ivector_(ivector_dir) {}

void OnlineFeaturePipeline::AcceptWaveform(float sample_rate,
                                           const std::vector<char> &waveform,
                                           bool is_end) {
  online_mfcc_.AcceptWaveform(sample_rate, waveform, is_end);
  online_ivector_.AcceptWaveform(sample_rate, waveform, is_end);
}

unsigned OnlineFeaturePipeline::MfccFramesReady() const {
  return online_mfcc_.NumFramesReady();
}

unsigned OnlineFeaturePipeline::IvectorFramesReady() const {
  return online_ivector_.NumFramesReady();
}

unsigned OnlineFeaturePipeline::MfccDim() const { return online_mfcc_.Dim(); }

unsigned OnlineFeaturePipeline::IvectorDim() const {
  return online_ivector_.Dim();
}

kaldi::Matrix<float> OnlineFeaturePipeline::GetMfccFrames(unsigned start,
                                                          unsigned end) {
  return online_mfcc_.GetFrames(start, end);
}

kaldi::Vector<float> OnlineFeaturePipeline::GetIvectorFrame(unsigned frame) {
  return online_ivector_.GetFrame(frame);
}

OnlineFeaturePipeline::~OnlineFeaturePipeline() = default;

}  // namespace tz_asr
