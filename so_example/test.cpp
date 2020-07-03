// Created by tz301 on 2020/07/03

#include <iostream>
#include <string>
#include <vector>

#include "../asr/asr.h"

/**
 * @brief Test OnlineAsr.
 * @param model_dir model directory.
 * @param wav_file wav file.
 */
void TestOnlineAsr(const std::string &model_dir, const std::string &wav_file) {
  asr::OnlineAsr online_asr(model_dir);
  asr::PcmData pcm_data(wav_file);

  size_t chunk_size = 6400;  // 200ms for 16k wav.
  auto data = pcm_data.Data();
  auto sample_rate = pcm_data.SampleRate();
  auto length = data.size();

  size_t start = 0;
  for (unsigned i = 1; start + chunk_size < length; start += chunk_size, ++i) {
    auto end = start + chunk_size;
    std::vector<char> chunk_data(data.begin() + start, data.begin() + end);
    auto transcript = online_asr.Recognize(sample_rate, chunk_data, false);
    std::cout << "Chunk " << i << ": " << transcript << std::endl;
  }

  std::vector<char> end_data(data.begin() + start, data.end());
  auto transcript = online_asr.Recognize(sample_rate, end_data, true);
  std::cout << "Chunk end: " << transcript << std::endl;
}

/**
 * @brief Main function.
 */
int main() {
  std::string model_dir = "../tests/model";
  std::string wav_file = "../tests/test.wav";
  TestOnlineAsr(model_dir, wav_file);
}
