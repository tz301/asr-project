// Created by tz301 on 2020/06/17

#include "asr/asr/online_asr.h"

#include <algorithm>
#include <iostream>

namespace tz_asr {

OnlineAsr::OnlineAsr(const std::string &model_dir)
    : online_feature_(model_dir + "/ivector_extractor"),
      model_(model_dir + "/final.pb", {"input:0", "ivector:0"},
             {"output.affine:0"}),
      online_decoder_(model_dir),
      num_frames_computed_(0),
      num_chunks_computed_(0) {
  WarmUp();
}

std::string OnlineAsr::Recognize(float sample_rate,
                                 const std::vector<char> &waveform,
                                 bool is_end) {
  online_feature_.AcceptWaveform(sample_rate, waveform, is_end);
  auto num_frames_ready = NumFramesReady(is_end);

  std::string transcript;
  while (num_frames_computed_ < num_frames_ready) {
    auto feature = GetFeatureForInference();
    auto prob = model_.Infer(feature);
    transcript = online_decoder_.Decode(prob, is_end);
    num_frames_computed_ += frames_per_chunk_ / subsample_factor_;
  }

  if (is_end) {
    Reset();
  }
  return transcript;
}

OnlineAsr::~OnlineAsr() = default;

void OnlineAsr::WarmUp() {
  const std::vector<char> waveform(32000, '\000');
  online_feature_.AcceptWaveform(16000, waveform, true);

  auto frames = left_context_ + frames_per_chunk_ + right_context_;
  kaldi::Matrix<float> mfcc(frames, online_feature_.MfccDim());
  kaldi::Matrix<float> ivector(frames, online_feature_.IvectorDim());

  for (auto i = 0; i < frames; ++i) {
    kaldi::SubVector<float> mfcc_this_row(mfcc, i);
    kaldi::SubVector<float> ivector_this_row(ivector, i);
    online_feature_.GetMfccFrame(i, &mfcc_this_row);
    online_feature_.GetIvectorFrame(frames - 1, &ivector_this_row);
  }

  auto prob = model_.Infer({mfcc, ivector});
  online_decoder_.Decode(prob, true);
  Reset();
}

void OnlineAsr::Reset() {
  online_feature_.Reset();
  online_decoder_.Reset();
  num_frames_computed_ = 0;
  num_chunks_computed_ = 0;
}

int OnlineAsr::NumFramesReady(bool is_end) const {
  auto features_ready = online_feature_.MfccFramesReady();
  if (features_ready == 0) {
    return 0;
  } else if (is_end) {
    return (features_ready + subsample_factor_ - 1) / subsample_factor_;
  } else {
    auto non_subsampled_output_frames_ready =
        std::max<int>(0, features_ready - right_context_);
    auto num_chunks_ready =
        non_subsampled_output_frames_ready / frames_per_chunk_;
    return num_chunks_ready * frames_per_chunk_ / subsample_factor_;
  }
}

const std::vector<kaldi::Matrix<float>> OnlineAsr::GetFeatureForInference() {
  auto begin = -left_context_ + num_chunks_computed_ * frames_per_chunk_;
  auto end = (num_chunks_computed_ + 1) * frames_per_chunk_ + right_context_;
  ++num_chunks_computed_;

  auto frames = end - begin;
  auto num_mfcc_frames_ready = online_feature_.MfccFramesReady();
  kaldi::Matrix<float> mfcc(frames, online_feature_.MfccDim());
  for (auto i = begin; i < end; ++i) {
    kaldi::SubVector<float> this_row(mfcc, i - begin);
    int input_frame = i;
    if (input_frame < 0) {
      input_frame = 0;
    } else if (input_frame > num_mfcc_frames_ready - 1) {
      input_frame = num_mfcc_frames_ready - 1;
    }
    online_feature_.GetMfccFrame(input_frame, &this_row);
  }

  kaldi::Matrix<float> ivector(frames, online_feature_.IvectorDim());
  auto ivector_frame = online_feature_.IvectorFramesReady() - 1;
  for (auto i = 0; i < frames; ++i) {
    kaldi::SubVector<float> ivector_this_row(ivector, i);
    online_feature_.GetIvectorFrame(ivector_frame, &ivector_this_row);
  }
  return {mfcc, ivector};
}

}  // namespace tz_asr
