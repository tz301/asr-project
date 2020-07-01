// Created by tz301 on 2020/06/18

#include "gtest/gtest.h"

#include "asr/online_asr.h"
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
    model_dir_ = "tests/model";
  }

  std::string wav_file_;
  std::string model_dir_;
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
 * @brief Test OnlineFeaturePipeline.
 */
TEST_F(AsrTest, OnlineFeaturePipelineTest) {
  std::string ivector_dir = model_dir_ + "/ivector_extractor";
  tz_asr::OnlineFeaturePipeline feature_pipeline(ivector_dir);
  tz_asr::PcmData pcm_data(wav_file_);

  for (unsigned i = 0; i < 2; ++i) {
    feature_pipeline.AcceptWaveform(pcm_data.SampleRate(), pcm_data.Data(),
                                    true);

    auto mfcc_frames_ready = feature_pipeline.MfccFramesReady();
    auto ivector_frames_ready = feature_pipeline.IvectorFramesReady();
    EXPECT_EQ(mfcc_frames_ready, 418);
    EXPECT_EQ(ivector_frames_ready, 418);

    auto mfcc_dim = feature_pipeline.MfccDim();
    auto ivector_dim = feature_pipeline.IvectorDim();
    EXPECT_EQ(mfcc_dim, 40);
    EXPECT_EQ(ivector_dim, 100);

    kaldi::Vector<float> mfcc(mfcc_dim);
    kaldi::Vector<float> ivector(ivector_dim);
    feature_pipeline.GetMfccFrame(0, &mfcc);
    feature_pipeline.GetIvectorFrame(66, &ivector);
    EXPECT_TRUE(std::fabs(mfcc(0) - 50.2571) < 0.0001);
    EXPECT_TRUE(std::fabs(ivector(0) - (-0.136949)) < 0.0001);

    feature_pipeline.Reset();
  }
}

/**
 * @brief Test OnlineAsr.
 */
TEST_F(AsrTest, OnlineAsrTest) {
  tz_asr::OnlineAsr online_asr(model_dir_);
  tz_asr::PcmData pcm_data(wav_file_);

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
