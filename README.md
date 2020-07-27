# asr-project

[![Build Status](https://travis-ci.com/tz301/asr-project.svg?branch=master)](https://travis-ci.com/tz301/asr-project)

## Introduction

This project shows how to build / deploy fast and independent ASR system based on [Kaldi](https://github.com/kaldi-asr/kaldi)
and [Tensorflow](https://github.com/tensorflow/tensorflow).

`ASR demo` can be found [here](http://119.45.150.149:9000/).

## Environment

* gcc=7.5.0
* g++=7.5.0
* bazel=2.0.0

## Dependencies

1. Kaldi dependencies: git clone [Kaldi](https://github.com/kaldi-asr/kaldi)
   to your local repository and install kaldi dependencies.
   `kaldi/tools/extras/check_dependencies.sh` will help.
2. Check if mkl is successfully installed and check if mkl path is
   `/opt/intel/mkl`. If not, change mkl path in [WORKSPACE](WORKSPACE).
3. Change kaldi path in [WORKSPACE](WORKSPACE).

## Dynamic library generate and usage

You can use dynamic library for asr system depolyment.

1. build: `bazel build asr:libasr.so.0.0.0`,
   dynamic library path is `bazel-bin/asr/libasr.so.0.0.0`.
2. Include `asr/asr.h` and link to `libasr.so.0.0.0` in your code.
3. Example see [server.cpp](server/server.cpp).

## Deployment

You can find server example in [server](server).

## Model preparation

The ASR model is trained using
[Kaldi Speech Recognition Toolkit](https://github.com/kaldi-asr/kaldi).

Below is the structure of model directory need for `OnlineAsr` in asr/asr.h.

├── final.mdl

├── final.pb

├── HCLG.fst

├── ivector_extractor

│   ├── final.dubm

│   ├── final.ie

│   ├── final.mat

│   ├── global_cmvn.stats

│   ├── mfcc.conf

│   ├── online_cmvn.conf

│   └── splice.conf

└── words.txt

All files can be found in kaldi directory after training and decoding,
except `final.pb`, the tensorflow format model file.

This can be converted via [kaldi-onnx-tf](https://github.com/tz301/kaldi-onnx-tf).

It's more common to use and can utilize multi-thread for faster
inference. Also it's convenient for GPU inference.

## Pre-trained Model

A pre-trained model is provided: [model](tests/model).

It's a TDNN-F model trained using kaldi's multi_cn project,
with ~1200h Mandarin open source data. Some CER below.

test_set|cer
----|----
aishell|5.65
aidatatang|4.43
magicdata|3.57
thchs|12.85

## Acknowledgement

* [Kaldi Speech Recognition Toolkit](https://github.com/kaldi-asr/kaldi)
* [Tensorflow](https://github.com/tensorflow/tensorflow)
