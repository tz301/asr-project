// Created by tz301 on 2020/06/18

#include "gtest/gtest.h"

#include "asr/asr.h"

/**
 * @brief AsrTest.
 */
class AsrTest : public ::testing::Test {
 protected:
  /**
   * @brief Set up .
   */
  void SetUp() override {
    wav_file_ = "tests/test.wav";
    model_dir_ = "tests/model";
  }

  std::string wav_file_;
  std::string model_dir_;
};

/**
 * @brief Test OnlineAsr.
 */
TEST_F(AsrTest, WaveReaderTest) {
  asr::PcmData pcm_data(wav_file_);
  EXPECT_EQ(pcm_data.SampleRate(), 16000u);
  EXPECT_EQ(pcm_data.Data().size(), static_cast<size_t>(134526));
}

/**
 * @brief Test OnlineAsr.
 */
TEST_F(AsrTest, OnlineAsrTest) {
  asr::OnlineAsr online_asr(model_dir_);
  asr::PcmData pcm_data(wav_file_);

  size_t chunk_size = 6400;  // 200ms for 16k wav.
  auto data = pcm_data.Data();
  auto length = data.size();

  size_t start = 0;
  for (; start + chunk_size < length; start += chunk_size) {
    auto end = start + chunk_size;
    std::vector<char> chunk_data(data.begin() + start, data.begin() + end);
    online_asr.Recognize(pcm_data.SampleRate(), chunk_data, false);
  }

  std::vector<char> end_data(data.begin() + start, data.end());
  auto transcript = online_asr.Recognize(pcm_data.SampleRate(), end_data, true);
  EXPECT_EQ(transcript, "甚至出现交易几乎停滞的情况");
}

/**
 * @brief Main.
 * @param argc argc.
 * @param argv argv.
 * @return test flag.
 */
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
