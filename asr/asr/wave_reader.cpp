// Created by tz301 on 2020/06/19.

#include "asr/asr/wave_reader.h"

#include <fstream>

namespace tz_asr {

PcmData::PcmData(const std::string &wav_file) : wav_file_(wav_file) {
  ReadAndCheck();
}

const std::vector<char> &PcmData::Data() const { return pcm_data_; }

uint32_t PcmData::SampleRate() const { return sample_rate_; }

void PcmData::ReadAndCheck() {
  std::ifstream fin(wav_file_, std::ios_base::binary);
  if (!fin) {
    std::string msg = "Error open " + wav_file_ + ".";
    throw std::ios_base::failure(msg);
  }

  fin.seekg(0, std::ios_base::end);
  auto length = static_cast<uint32_t>(fin.tellg()) - 44;
  fin.seekg(0, std::ios_base::beg);

  // 0:4, RIFF.
  char chunk_id[4];
  fin.read(chunk_id, 4);
  Check(0, chunk_id, "RIFF");

  uint32_t chunk_size;
  fin.read(reinterpret_cast<char *>(&chunk_size), 4);
  Check(4, chunk_size, length + 36);

  char format[4];
  fin.read(format, 4);
  Check(8, format, "WAVE");

  char sub_chunk1_id[4];
  fin.read(sub_chunk1_id, 4);
  Check(12, sub_chunk1_id, "fmt ");

  uint32_t sub_chunk1_size;
  fin.read(reinterpret_cast<char *>(&sub_chunk1_size), 4);
  Check(16, sub_chunk1_size, static_cast<uint32_t>(16));

  uint16_t audio_format;
  fin.read(reinterpret_cast<char *>(&audio_format), 2);
  Check(20, audio_format, static_cast<uint16_t>(1));

  uint16_t channel;
  fin.read(reinterpret_cast<char *>(&channel), 2);
  Check(22, channel, static_cast<uint16_t>(1));

  fin.read(reinterpret_cast<char *>(&sample_rate_), 4);

  uint32_t bytes_per_second;
  fin.read(reinterpret_cast<char *>(&bytes_per_second), 4);

  uint16_t block_align;
  fin.read(reinterpret_cast<char *>(&block_align), 2);
  Check(32, block_align, static_cast<uint16_t>(2));

  uint16_t sample_width;
  fin.read(reinterpret_cast<char *>(&sample_width), 2);
  Check(34, sample_width, static_cast<uint16_t>(16));

  char sub_chunk2_id[4];
  fin.read(sub_chunk2_id, 4);
  Check(36, sub_chunk2_id, "data");

  uint32_t sub_chunk2_size;
  fin.read(reinterpret_cast<char *>(&sub_chunk2_size), 4);
  Check(40, sub_chunk2_size, length);

  pcm_data_.resize(length);
  fin.read(&pcm_data_[0], length);
}

template <typename T>
void PcmData::Check(unsigned begin, T value, T true_value) const {
  if (value != true_value) {
    auto end = begin + sizeof(T);
    std::string msg = "Error read " + wav_file_ + " " + std::to_string(begin) +
                      "-" + std::to_string(end) + ": " + std::to_string(value) +
                      " = " + std::to_string(true_value) + ".";
    throw std::invalid_argument(msg);
  }
}

void PcmData::Check(unsigned begin, const char *value,
                    const std::string true_value) const {
  auto length = true_value.size();
  std::string value_str(value, length);
  if (value_str != true_value) {
    auto end = begin + length;
    std::string msg = "Error read " + wav_file_ + " " + std::to_string(begin) +
                      "-" + std::to_string(end) + ": " + value_str +
                      " != " + true_value + ".";
    throw std::invalid_argument(msg);
  }
}

}  // namespace tz_asr
