// Created by tz301 on 2020/06/18

#include "gtest/gtest.h"

#include "asr/online_feature.h"
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
    ivector_dir_ = "tests/ivector_extractor";
    mfcc_conf_ = ivector_dir_ + "/mfcc.conf";
  }

  std::string wav_file_;
  std::string ivector_dir_;
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

/**
 * @brief Test OnlineMfccExtractor.
 */
TEST_F(AsrTest, OnlineMfccExtractorTest) {
  tz_asr::OnlineMfccExtractor mfcc(mfcc_conf_);
  tz_asr::PcmData pcm_data(wav_file_);

  mfcc.AcceptWaveform(pcm_data.SampleRate(), pcm_data.Data(), true);
  auto dim = mfcc.Dim();
  auto frames_ready = mfcc.NumFramesReady();
  EXPECT_EQ(dim, 40);
  EXPECT_EQ(frames_ready, 418);

  auto feature = mfcc.GetFrames(0, frames_ready);
  EXPECT_EQ(feature.NumRows(), 418);
  EXPECT_EQ(feature.NumCols(), 40);
  EXPECT_TRUE(std::fabs(feature(0, 0) - 50.2571) < 0.0001);
}

/**
 * @brief Test OnlineIvectorExtractor.
 */
TEST_F(AsrTest, OnlineIvectorExtractorTest) {
  tz_asr::OnlineIvectorExtractor ivector(ivector_dir_);
  tz_asr::PcmData pcm_data(wav_file_);

  ivector.AcceptWaveform(pcm_data.SampleRate(), pcm_data.Data(), true);
  auto dim = ivector.Dim();
  auto frames_ready = ivector.NumFramesReady();
  EXPECT_EQ(dim, 100);
  EXPECT_EQ(frames_ready, 418);

  auto feature = ivector.GetFrame(frames_ready);
  EXPECT_EQ(feature.Dim(), 100);
  EXPECT_TRUE(std::fabs(feature(0) - (-0.128915)) < 0.0001);
}

/**
 * @brief Test OnlineFeaturePipeline.
 */
TEST_F(AsrTest, OnlineFeaturePipelineTest) {
  tz_asr::OnlineFeaturePipeline feature_pipeline(mfcc_conf_);
  tz_asr::PcmData pcm_data(wav_file_);

  feature_pipeline.AcceptWaveform(pcm_data.SampleRate(), pcm_data.Data(), true);
  auto frames_ready = feature_pipeline.NumFramesReady();
  EXPECT_EQ(frames_ready, 418);

  auto feature = feature_pipeline.GetFrames(0, frames_ready);
  auto mfcc = feature.first;
  EXPECT_EQ(mfcc.NumRows(), 418);
  EXPECT_EQ(mfcc.NumCols(), 40);
  EXPECT_TRUE(std::fabs(mfcc(0, 0) - 50.2571) < 0.0001);
}
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
