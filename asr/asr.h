// Created by tz301 on 2020/07/03

#ifndef ASR_ASR_H_
#define ASR_ASR_H_

#include <memory>
#include <string>
#include <vector>

namespace asr {

/**
 * @brief Pcm Data.
 */
class PcmData {
 public:
  /**
   * @brief Construct a new Pcm Data object.
   * @param wav_file pcm format wav file, only support 16bit, mono.
   */
  explicit PcmData(const std::string& wav_file);

  /**
   * @brief Get pcm data.
   * @return pcm data.
   */
  const std::vector<char>& Data() const;

  /**
   * @brief Get sample rate.
   * @return sample rate.
   */
  uint32_t SampleRate() const;

 private:
  class PcmDataImpl;                       // Implement class.
  std::shared_ptr<PcmDataImpl> impl_ptr_;  // Implement point.
};

/**
 * @brief Online Asr.
 */
class OnlineAsr {
 public:
  /**
   * @brief Construct a new Online Asr object.
   * @param model_dir model dir.
   */
  explicit OnlineAsr(const std::string& model_dir);

  /**
   * @brief Recognize waveform.
   * @param sample_rate sample rate.
   * @param waveform wave form data.
   * @param is_end id end.
   * @return transcript.
   */
  std::string Recognize(float sample_rate, const std::vector<char>& waveform,
                        bool is_end);

  /**
   * @brief Destroy the Online Asr object.
   */
  ~OnlineAsr();

 private:
  class OnlineAsrImpl;                       // Implement class.
  std::shared_ptr<OnlineAsrImpl> impl_ptr_;  // Implement point.
};

}  // namespace asr

#endif  // ASR_ASR_H_
