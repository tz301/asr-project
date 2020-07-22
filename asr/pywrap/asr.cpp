// Created by tz301 on 2020/07/22

#include "asr/pywrap/asr.h"

namespace asr_py {

PcmData::PcmData(const std::string& wav_file) : pcm_data_(wav_file) {}

const std::vector<char>& PcmData::data() const { return pcm_data_.Data(); }

uint32_t PcmData::sample_rate() const { return pcm_data_.SampleRate(); }

}  // namespace asr_py
