// Created by tz301 on 2020/06/18

#include "gtest/gtest.h"

#include "asr/feature.h"
#include "asr/wave_reader.h"

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
    mfcc_conf_ = "tests/mfcc.conf";
  }

  std::string wav_file_;
  std::string mfcc_conf_;
};

/**
 * @brief Test OnlineAsr.
 */
TEST_F(AsrTest, WaveReaderTest) {
  tz_asr::PcmData pcm_data(wav_file_);
  EXPECT_EQ(pcm_data.SampleRate(), 16000u);
  EXPECT_EQ(pcm_data.Data().size(), static_cast<size_t>(134526));
}

Test_F(AsrTest, FeatureMfccTest) {
  tz_asr::MfccExtractor mfcc(mfcc_conf_);
  tz_asr::PcmData pcm_data(wav_file_);

  mfcc.AcceptWaveform(pcm_data.SampleRate(), pcm_data.Data(), true);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
