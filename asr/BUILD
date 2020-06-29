cc_library(
    name = "asr",
    hdrs = ["asr.h"],
    srcs = ["asr.cpp"],
    deps = ["online_feature", "model"],
    visibility = ["//visibility:public"]
)

cc_library(
    name = "online_feature",
    hdrs = ["online_feature.h"],
    srcs = ["online_feature.cpp"],
    deps = ["@kaldi//:feat", "@kaldi//:online2"],
    visibility = ["//visibility:public"]
)

cc_library(
    name = "wave_reader",
    hdrs = ["wave_reader.h"],
    srcs = ["wave_reader.cpp"],
    visibility = ["//visibility:public"]
)

cc_library(
    name = "model",
    hdrs = ["model.h"],
    srcs = ["model.cpp"],
    deps = [
        "@org_tensorflow//tensorflow/cc/saved_model:loader",
        "@kaldi//:feat",
    ],
    visibility = ["//visibility:public"]
)
