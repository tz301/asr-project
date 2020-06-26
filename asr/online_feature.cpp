// Created by tz301 on 2020/06/19

#include "asr/online_feature.h"

#include <string>

namespace tz_asr {

/**
 * @brief Read mfcc options from config file.
 * @param config_file mfcc config file.
 * @return mfcc options.
 */
kaldi::MfccOptions ReadMfccOptions(const std::string &config_file) {
  kaldi::MfccOptions mfcc_opts;
  kaldi::ReadConfigFromFile(config_file, &mfcc_opts);
  return mfcc_opts;
}

/**
 * @brief Construct waveform array.
 * @param waveform waveform.
 * @return Waveform array.
 */
std::unique_ptr<float[]> WaveformArray(const std::vector<char> &waveform) {
  auto cols = waveform.size() / 2;
  std::unique_ptr<float[]> waveform_array(new float[cols]);

  char *buffer = const_cast<char *>(&waveform[0]);
  uint16_t *waveform_ptr = reinterpret_cast<uint16_t *>(buffer);
  for (unsigned i = 0; i < cols; i++) {
    int16_t k = *waveform_ptr++;
    waveform_array[i] = k;
  }
  return waveform_array;
}

OnlineMfccExtractor::OnlineMfccExtractor(const std::string &config_file)
    : mfcc_opts_(ReadMfccOptions(config_file)), online_mfcc_(mfcc_opts_) {}

void OnlineMfccExtractor::AcceptWaveform(float sample_rate,
                                         const std::vector<char> &waveform,
                                         bool is_end) {
  auto waveform_array = WaveformArray(waveform);
  kaldi::SubVector<float> wave(waveform_array.get(), waveform.size() / 2);
  online_mfcc_.AcceptWaveform(sample_rate, wave);

  if (is_end) {
    online_mfcc_.InputFinished();
  }
}

unsigned OnlineMfccExtractor::NumFramesReady() const {
  return online_mfcc_.NumFramesReady();
}

unsigned OnlineMfccExtractor::Dim() const { return online_mfcc_.Dim(); }

kaldi::Matrix<float> OnlineMfccExtractor::GetFrames(unsigned start,
                                                    unsigned end) {
  kaldi::Matrix<float> mfcc(end - start, Dim());
  for (unsigned frame = start, row = 0; frame < end; frame++, row++) {
    kaldi::Vector<float> one_row(Dim());
    online_mfcc_.GetFrame(frame, &one_row);
    mfcc.CopyRowFromVec(one_row, row);
  }
  return mfcc;
}

OnlineMfccExtractor::~OnlineMfccExtractor() = default;

OnlineIvectorExtractor::OnlineIvectorExtractor(const std::string &iv_dir)
    : mfcc_opts_(ReadMfccOptions(iv_dir + "/mfcc.conf")),
      ivector_conf_(ReadIvectorConfig(iv_dir)),
      ivector_info_(ivector_conf_),
      online_mfcc_(mfcc_opts_),
      online_ivector_(ivector_info_, &online_mfcc_) {}

void OnlineIvectorExtractor::AcceptWaveform(float sample_rate,
                                            const std::vector<char> &waveform,
                                            bool is_end) {
  auto waveform_array = WaveformArray(waveform);
  kaldi::SubVector<float> wave(waveform_array.get(), waveform.size() / 2);
  online_mfcc_.AcceptWaveform(sample_rate, wave);

  if (is_end) {
    online_mfcc_.InputFinished();
  }
}

unsigned OnlineIvectorExtractor::NumFramesReady() const {
  return online_ivector_.NumFramesReady();
}

unsigned OnlineIvectorExtractor::Dim() const { return online_ivector_.Dim(); }

kaldi::Vector<float> OnlineIvectorExtractor::GetFrame(unsigned frame) {
  kaldi::Vector<float> ivector(Dim());
  online_ivector_.GetFrame(frame, &ivector);
  return ivector;
}

OnlineIvectorExtractor::~OnlineIvectorExtractor() = default;

kaldi::OnlineIvectorExtractionConfig OnlineIvectorExtractor::ReadIvectorConfig(
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

OnlineFeaturePipeline::OnlineFeaturePipeline(const std::string &config_file)
    : online_mfcc_(config_file) {}

void OnlineFeaturePipeline::AcceptWaveform(float sample_rate,
                                           const std::vector<char> &waveform,
                                           bool is_end) {
  online_mfcc_.AcceptWaveform(sample_rate, waveform, is_end);
}

unsigned OnlineFeaturePipeline::NumFramesReady() const {
  return online_mfcc_.NumFramesReady();
}

std::pair<kaldi::Matrix<float>, kaldi::Matrix<float>>
OnlineFeaturePipeline::GetFrames(unsigned start, unsigned end) {
  return {online_mfcc_.GetFrames(start, end),
          online_mfcc_.GetFrames(start, end)};
}

OnlineFeaturePipeline::~OnlineFeaturePipeline() = default;

}  // namespace tz_asr
