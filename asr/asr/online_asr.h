// Created by tz301 on 2020/06/17

#ifndef ASR_ASR_ONLINE_ASR_H_
#define ASR_ASR_ONLINE_ASR_H_

#include <string>
#include <vector>

#include "asr/asr/model.h"
#include "asr/asr/online_decoder.h"
#include "asr/asr/online_feature.h"
#include "asr/asr/wave_reader.h"

namespace tz_asr {

/**
 * @brief Online Asr.
 */
class OnlineAsr {
 public:
  /**
   * @brief Construct a new Online Asr object.
   * @param model_dir model dir.
   */
  explicit OnlineAsr(const std::string &model_dir);

  /**
   * @brief Recognize waveform.
   * @param sample_rate sample rate.
   * @param waveform wave form data.
   * @param is_end id end.
   * @return transcript.
   */
  std::string Recognize(float sample_rate, const std::vector<char> &waveform,
                        bool is_end);

  /**
   * @brief Destroy the Online Asr object.
   */
  ~OnlineAsr();

 private:
  /**
   * @brief Warm up.
   */
  void WarmUp();

  /**
   * @brief Reset all internal variables.
   */
  void Reset();

  /**
   * @brief Get number of ready frames.
   * @param is_end is end.
   * @return number of ready frames.
   */
  int NumFramesReady(bool is_end) const;

  /**
   * @brief Get mfcc and ivector feature for acoustic model inference.
   * @return mfcc and ivector feature.
   */
  const std::vector<kaldi::Matrix<float>> GetFeatureForInference();

  OnlineFeaturePipeline online_feature_;  // Online feature pipeline.
  const Model model_;                     // Acoustic model.
  OnlineDecoder online_decoder_;          // Online decoder.

  int num_frames_computed_;  // Number of computed frames.
  int num_chunks_computed_;  // Number of computed chunks.

  const int subsample_factor_ = 3;   // Subsample factor.
  const int frames_per_chunk_ = 21;  // Frames per chunk.
  const int left_context_ = 34;      // Left context.
  const int right_context_ = 34;     // Right context.
};

}  // namespace tz_asr

#endif  // ASR_ASR_ONLINE_ASR_H_
