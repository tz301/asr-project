// Created by tz301 on 2020/07/01

#ifndef ASR_ASR_ONLINE_DECODER_H_
#define ASR_ASR_ONLINE_DECODER_H_

#include <memory>
#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-compare"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-variable"

#include "decoder/lattice-faster-online-decoder.h"

#pragma GCC diagnostic pop

namespace tz_asr {

/**
 * @brief Decodable, inherit from kaldi::DecodableInterface.
 */
class Decodable : public kaldi::DecodableInterface {
 public:
  /**
   * @brief Construct a new Decodable object.
   * @param prob prob matrix.
   * @param pdf_ids pdf id list.
   * @param log_priors log prior list.
   * @param num_frames_decoded number of decoded frames.
   */
  Decodable(kaldi::Matrix<float> prob, const std::vector<int> &pdf_ids,
            const kaldi::Vector<float> &log_priors, int num_frames_decoded);

  /**
   * @brief Get log likelihood.
   * @param frame frame index.
   * @param index transition id index.
   * @return log likelihood.
   */
  kaldi::BaseFloat LogLikelihood(int frame, int index) override;

  /**
   * @brief If frame is last frame.
   * @param frame frame index.
   * @return If frame is last frame.
   */
  bool IsLastFrame(int frame) const override;

  /**
   * @brief Get number of ready frames.
   * @return number of ready frames.
   */
  int NumFramesReady() const override;

  /**
   * @brief Get number of pdf ids.
   * @return number of pdf ids.
   */
  int NumIndices() const override;

 private:
  kaldi::Matrix<float> prob_;       // Prob matrix.
  const std::vector<int> pdf_ids_;  // Pdf id list.
  int num_frames_decoded_;          // Number of decoded frames.
};

/**
 * @brief Online Decoder.
 */
class OnlineDecoder {
 public:
  /**
   * @brief Construct a new Online Decoder object.
   * @param model_dir model dir.
   */
  explicit OnlineDecoder(const std::string &model_dir);

  /**
   * @brief Decode.
   * @param prob prob matrix.
   * @param is_end is end.
   * @return transcript.
   */
  std::string Decode(const kaldi::Matrix<float> &prob, bool is_end);

  /**
   * @brief Reset all internal variables.
   */
  void Reset();

  /**
   * @brief Destroy the Online Decoder object.
   */
  ~OnlineDecoder();

 private:
  /**
   * @brief Read symbol table from words.txt.
   * @param words_txt words.txt.
   * @return symbol table.
   */
  static fst::SymbolTable ReadSymbolTable(const std::string &words_txt);

  /**
   * @brief Get decoder config.
   * @return decoder config.
   */
  static kaldi::LatticeFasterDecoderConfig DecoderConfig();

  void ReadTransitionModel(const std::string &transition_model_file);

  fst::SymbolTable symbol_table_;                    // Symbol table.
  std::unique_ptr<fst::Fst<fst::StdArc>> hclg_fst_;  // HCLG.fst.
  // Online Decoder.
  kaldi::LatticeFasterOnlineDecoderTpl<fst::Fst<fst::StdArc>> online_decoder_;
  // Transition model.
  const std::shared_ptr<kaldi::TransitionModel> transition_model_;
  const std::shared_ptr<std::vector<int>> pdf_ids_;         // Pdf id list.
  const std::shared_ptr<kaldi::Vector<float>> log_priors_;  // Log prior.
  unsigned num_frames_decoded_;  // Number of decoded frames.
};

}  // namespace tz_asr

#endif  // ASR_ASR_ONLINE_DECODER_H_
