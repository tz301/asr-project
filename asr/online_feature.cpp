// Created by tz301 on 2020/06/19

#include "asr/online_feature.h"

#include <string>

namespace tz_asr {

OnlineFeaturePipeline::OnlineFeaturePipeline(const std::string &ivector_dir)
    : mfcc_opts_(ReadMfccOptions(ivector_dir + "/mfcc.conf")),
      ivector_conf_(ReadIvectorConfig(ivector_dir)),
      ivector_info_(ivector_conf_),
      online_mfcc_(std::unique_ptr<kaldi::OnlineMfcc>(
          new kaldi::OnlineMfcc(mfcc_opts_))),
      online_ivector_(std::unique_ptr<kaldi::OnlineIvectorFeature>(
          new kaldi::OnlineIvectorFeature(ivector_info_, online_mfcc_.get()))) {
}

void OnlineFeaturePipeline::AcceptWaveform(float sample_rate,
                                           const std::vector<char> &waveform,
                                           bool is_end) {
  auto cols = waveform.size() / 2;
  std::unique_ptr<float[]> waveform_array(new float[cols]);

  char *buffer = const_cast<char *>(&waveform[0]);
  uint16_t *waveform_ptr = reinterpret_cast<uint16_t *>(buffer);
  for (unsigned i = 0; i < cols; i++) {
    int16_t k = *waveform_ptr++;
    waveform_array[i] = k;
  }

  kaldi::SubVector<float> wave(waveform_array.get(), cols);
  online_mfcc_->AcceptWaveform(sample_rate, wave);

  if (is_end) {
    online_mfcc_->InputFinished();
  }
}

int OnlineFeaturePipeline::MfccFramesReady() const {
  return online_mfcc_->NumFramesReady();
}

int OnlineFeaturePipeline::IvectorFramesReady() const {
  return online_ivector_->NumFramesReady();
}

unsigned OnlineFeaturePipeline::MfccDim() const { return online_mfcc_->Dim(); }

unsigned OnlineFeaturePipeline::IvectorDim() const {
  return online_ivector_->Dim();
}

void OnlineFeaturePipeline::GetMfccFrame(int frame,
                                         kaldi::VectorBase<float> *feature) {
  online_mfcc_->GetFrame(frame, feature);
}

void OnlineFeaturePipeline::GetIvectorFrame(int frame,
                                            kaldi::VectorBase<float> *feature) {
  online_ivector_->GetFrame(frame, feature);
}

void OnlineFeaturePipeline::Reset() {
  online_mfcc_ =
      std::unique_ptr<kaldi::OnlineMfcc>(new kaldi::OnlineMfcc(mfcc_opts_));
  online_ivector_ = std::unique_ptr<kaldi::OnlineIvectorFeature>(
      new kaldi::OnlineIvectorFeature(ivector_info_, online_mfcc_.get()));
}

OnlineFeaturePipeline::~OnlineFeaturePipeline() = default;

kaldi::MfccOptions OnlineFeaturePipeline::ReadMfccOptions(
    const std::string &config_file) {
  kaldi::MfccOptions mfcc_opts;
  kaldi::ReadConfigFromFile(config_file, &mfcc_opts);
  return mfcc_opts;
}

kaldi::OnlineIvectorExtractionConfig OnlineFeaturePipeline::ReadIvectorConfig(
    const std::string &iv_dir) {
  kaldi::OnlineIvectorExtractionConfig config;
  config.cmvn_config_rxfilename = iv_dir + "/online_cmvn.conf";
  config.diag_ubm_rxfilename = iv_dir + "/final.dubm";
  config.global_cmvn_stats_rxfilename = iv_dir + "/global_cmvn.stats";
  config.ivector_extractor_rxfilename = iv_dir + "/final.ie";
  config.lda_mat_rxfilename = iv_dir + "/final.mat";
  config.splice_config_rxfilename = iv_dir + "/splice.conf";
  return config;
}

}  // namespace tz_asr
