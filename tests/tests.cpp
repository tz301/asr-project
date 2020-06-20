// Created by tz301 on 2020/06/18

#include "gtest/gtest.h"

#include "asr/wave_reader.h"

/**
 * @brief AsrTest.
 */
class AsrTest : public ::testing::Test {
 protected:
  /**
   * @brief Set up .
   */
  void SetUp() override { wav_file_ = "tests/test.wav"; }

  std::string wav_file_;
};

/**
 * @brief Test OnlineAsr.
 */
TEST_F(AsrTest, WaveReaderTest) {
  tz_asr::PcmData pcm_data(wav_file_);
  EXPECT_EQ(pcm_data.Data().size(), static_cast<size_t>(134526));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
