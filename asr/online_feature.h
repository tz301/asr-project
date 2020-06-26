// Created by tz301 on 2020/06/19

#ifndef ASR_ONLINE_FEATURE_H_
#define ASR_ONLINE_FEATURE_H_

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
 * @brief Online mfcc feature extractor.
 */
class OnlineMfccExtractor {
 public:
  /**
   * @brief Construct a new Online Mfcc Extractor object.
   * @param config_file mfcc config file.
   */
  explicit OnlineMfccExtractor(const std::string &config_file);

  /**
   * @brief Accept wave form.
   * @param sample_rate sample rate.
   * @param waveform wave form data.
   * @param is_end is end.
   */
  void AcceptWaveform(float sample_rate, const std::vector<char> &waveform,
                      bool is_end);

  /**
   * @brief Get number of ready frames.
   * @return number of ready frames.
   */
  unsigned NumFramesReady() const;

  /**
   * @brief Get feature dimension.
   * @return feature dimension.
   */
  unsigned Dim() const;

  /**
   * @brief Get feature matrix.
   * @param start start frame index.
   * @param end end frame index.
   * @return feature matrix.
   */
  kaldi::Matrix<float> GetFrames(unsigned start, unsigned end);

  /**
   * @brief Destroy the Online Mfcc Extractor object.
   */
  ~OnlineMfccExtractor();

 private:
  const kaldi::MfccOptions mfcc_opts_;  // Mfcc options.
  kaldi::OnlineMfcc online_mfcc_;       // Online mfcc feature object.
};

/**
 * @brief Online i-vector feature extractor.
 */
class OnlineIvectorExtractor {
 public:
  /**
   * @brief Construct a new Online Ivector Extractor object.
   * @param ivector_dir i-vector extractor model dir,
   *                    also contains mfcc.conf file.
   */
  explicit OnlineIvectorExtractor(const std::string &ivector_dir);

  /**
   * @brief Accept wave form.
   * @param sample_rate sample rate.
   * @param waveform wave form data.
   * @param is_end is end.
   */
  void AcceptWaveform(float sample_rate, const std::vector<char> &waveform,
                      bool is_end);

  /**
   * @brief Get number of ready frames.
   * @return number of ready frames.
   */
  unsigned NumFramesReady() const;

  /**
   * @brief Get feature dimension.
   * @return dimension.
   */
  unsigned Dim() const;

  /**
   * @brief Get feature vector.
   * @param frame frame index.
   * @return feature vector.
   */
  kaldi::Vector<float> GetFrame(unsigned frame);

  /**
   * @brief Destroy the Online Ivector Extractor object.
   */
  ~OnlineIvectorExtractor();

 private:
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
  kaldi::OnlineMfcc online_mfcc_;               // Online mfcc extractor.
  kaldi::OnlineIvectorFeature online_ivector_;  // Online i-vector extractor.
};

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
   * @brief Get number of ready frames.
   * @return number of ready frames.
   */
  unsigned NumFramesReady() const;

  /**
   * @brief Get feature matrix pair, {mfcc, i-vector}.
   * @param start start frame index.
   * @param end end frame index.
   * @return feature matrix pair, {mfcc, i-vector}.
   */
  std::pair<kaldi::Matrix<float>, kaldi::Matrix<float>> GetFrames(
      unsigned start, unsigned end);

  ~OnlineFeaturePipeline();

 private:
  OnlineMfccExtractor online_mfcc_;  // !< Online mfcc extractor.
};

}  // namespace tz_asr

#endif  // ASR_ONLINE_FEATURE_H_
