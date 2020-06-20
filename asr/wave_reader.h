// Created by tz301 on 2020/06/19.

#ifndef ASR_WAVE_READER_H_
#define ASR_WAVE_READER_H_

#include <string>
#include <vector>

namespace tz_asr {

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
  /**
   * @brief Read pcm data from wav file and check header.
   */
  void ReadAndCheck();

  /**
   * @brief Check if field readed from wav file is correct.
   * @tparam T uint16_t or uint32_t.
   * @param index begin index of field.
   * @param value readed value.
   * @param true_value true value of field.
   */
  template <typename T>
  void Check(unsigned begin, T value, T true_value) const;

  /**
   * @brief Check if string field readed from wav file is correct.
   * @param begin begin index of field.
   * @param value readed value.
   * @param true_value true value of field.
   */
  void Check(unsigned begin, const char* value,
             const std::string true_value) const;

  const std::string wav_file_;  // Wav file.
  uint32_t sample_rate_;        // Sample rate.
  std::vector<char> pcm_data_;  // Pcm data.
};

}  // namespace tz_asr

#endif  // ASR_WAVE_READER_H_
