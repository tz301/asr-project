// Created by tz301 on 2020/06/19

#ifndef ASR_ASR_ONLINE_FEATURE_H_
#define ASR_ASR_ONLINE_FEATURE_H_

#include <memory>
#include <string>
#include <utility>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-compare"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-variable"

#include "feat/online-feature.h"
#include "online2/online-ivector-feature.h"

#pragma GCC diagnostic pop

namespace tz_asr {

/**
 * @brief Online feature pipeline.
 */
class OnlineFeaturePipeline {
 public:
  /**
   * @brief Construct a new Online Feature Pipeline object.
   * @param ivector_dir i-vector extractor model dir,
   *                    also contains mfcc.conf file.
   */
  explicit OnlineFeaturePipeline(const std::string &ivector_dir);

  /**
   * @brief Accept wave form.
   * @param sample_rate sample rate.
   * @param waveform wave form data.
   * @param is_end id end.
   */
  void AcceptWaveform(float sample_rate, const std::vector<char> &waveform,
                      bool is_end);

  /**
   * @brief Get number of ready frames for mfcc.
   * @return number of ready frames for mfcc.
   */
  int MfccFramesReady() const;

  /**
   * @brief Get number of ready frames for i-vector.
   * @return number of ready frames for i-vector.
   */
  int IvectorFramesReady() const;

  /**
   * @brief Get mfcc feature dimension.
   * @return mfcc feature dimension.
   */
  unsigned MfccDim() const;

  /**
   * @brief Get i-vector feature dimension.
   * @return i-vector feature dimension.
   */
  unsigned IvectorDim() const;

  /**
   * @brief Get mfcc frame.
   * @param frame frame index.
   * @param feature feature.
   */
  void GetMfccFrame(int frame, kaldi::VectorBase<float> *feature);

  /**
   * @brief Get i-vector frame.
   * @param frame frame index.
   * @param feature feature.
   */
  void GetIvectorFrame(int frame, kaldi::VectorBase<float> *feature);

  /**
   * @brief Reset all inner variables.
   */
  void Reset();

  /**
   * @brief Destroy the Online Feature Pipeline object.
   */
  ~OnlineFeaturePipeline();

 private:
  /**
   * @brief Read mfcc options from config file.
   * @param config_file mfcc config file.
   * @return mfcc options.
   */
  kaldi::MfccOptions ReadMfccOptions(const std::string &config_file);

  /**
   * @brief Construct i-vector config from directory.
   * @param ivector_dir i-vector extractor model dir,
   *                    also contains mfcc.conf file.
   * @return i-vector config.
   */
  static kaldi::OnlineIvectorExtractionConfig ReadIvectorConfig(
      const std::string &ivector_dir);

  const kaldi::MfccOptions mfcc_opts_;                       // Mfcc options.
  const kaldi::OnlineIvectorExtractionConfig ivector_conf_;  // I-vector config.
  const kaldi::OnlineIvectorExtractionInfo ivector_info_;    // I-vector info.
  std::unique_ptr<kaldi::OnlineMfcc> online_mfcc_;  // Online mfcc extractor.
  // Online i-vector extractor.
  std::unique_ptr<kaldi::OnlineIvectorFeature> online_ivector_;
};

}  // namespace tz_asr

#endif  // ASR_ASR_ONLINE_FEATURE_H_
