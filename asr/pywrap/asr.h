// Created by tz301 on 2020/07/22

#ifndef ASR_PYWRAP_ASR_H_
#define ASR_PYWRAP_ASR_H_

#include <string>
#include <vector>

#include "asr/asr.h"

namespace asr_py {

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
  const std::vector<char>& data() const;

  /**
   * @brief Get sample rate.
   * @return sample rate.
   */
  uint32_t sample_rate() const;

 private:
  asr::PcmData pcm_data_;  // Pcm data.
};

}  // namespace asr_py

#endif  // ASR_PYWRAP_ASR_H_
