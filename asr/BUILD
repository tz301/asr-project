cc_library(
    name = "online_asr",
    hdrs = ["online_asr.h"],
    srcs = ["online_asr.cpp"],
    deps = ["online_feature", "model", "online_decoder"],
    visibility = ["//visibility:public"]
)

cc_library(
    name = "wave_reader",
    hdrs = ["wave_reader.h"],
    srcs = ["wave_reader.cpp"],
    visibility = ["//visibility:public"]
)

cc_library(
    name = "online_decoder",
    hdrs = ["online_decoder.h"],
    srcs = ["online_decoder.cpp"],
    deps = ["@boost//:locale", "@kaldi//:online2"],
)

cc_library(
    name = "online_feature",
    hdrs = ["online_feature.h"],
    srcs = ["online_feature.cpp"],
    deps = ["@kaldi//:feat", "@kaldi//:online2"],
)

cc_library(
    name = "model",
    hdrs = ["model.h"],
    srcs = ["model.cpp"],
    deps = [
        "@org_tensorflow//tensorflow/cc/saved_model:loader",
        "@kaldi//:feat",
    ],
)
