// Created by tz301 on 2020/07/03

#include "asr/asr.h"

#include "asr/asr/online_asr.h"

namespace asr {

/**
 * @brief PcmData implement class.
 */
class PcmData::PcmDataImpl {
 public:
  /**
   * @brief Construct a new Pcm Data Impl object.
   * @param wav_file pcm format wav file, only support 16bit, mono.
   */
  explicit PcmDataImpl(const std::string& wav_file) : pcm_data_(wav_file) {}

  /**
   * @brief Get pcm data.
   * @return pcm data.
   */
  const std::vector<char>& Data() const { return pcm_data_.Data(); }

  /**
   * @brief Get sample rate.
   * @return sample rate.
   */
  uint32_t SampleRate() const { return pcm_data_.SampleRate(); }

 private:
  tz_asr::PcmData pcm_data_;  // Internal PcmData object.
};

PcmData::PcmData(const std::string& wav_file)
    : impl_ptr_{std::make_shared<PcmDataImpl>(wav_file)} {}

const std::vector<char>& PcmData::Data() const { return impl_ptr_->Data(); }

uint32_t PcmData::SampleRate() const { return impl_ptr_->SampleRate(); }

/**
 * @brief OnlineAsr implement class.
 */
class OnlineAsr::OnlineAsrImpl {
 public:
  /**
   * @brief Construct a new Online Asr Impl object.
   * @param model_dir model dir.
   */
  explicit OnlineAsrImpl(const std::string& model_dir)
      : online_asr_(model_dir) {}

  /**
   * @brief Recognize waveform.
   * @param sample_rate sample rate.
   * @param waveform wave form data.
   * @param is_end id end.
   * @return transcript.
   */
  std::string Recognize(float sample_rate, const std::vector<char>& waveform,
                        bool is_end) {
    return online_asr_.Recognize(sample_rate, waveform, is_end);
  }

 private:
  tz_asr::OnlineAsr online_asr_;  // Internal OnlineAsr object.
};

OnlineAsr::OnlineAsr(const std::string& model_dir)
    : impl_ptr_{std::make_shared<OnlineAsrImpl>(model_dir)} {}

std::string OnlineAsr::Recognize(float sample_rate,
                                 const std::vector<char>& waveform,
                                 bool is_end) {
  return impl_ptr_->Recognize(sample_rate, waveform, is_end);
}

OnlineAsr::~OnlineAsr() = default;

}  // namespace asr
