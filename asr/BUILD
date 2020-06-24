cc_library(
    name = "wave_reader",
    hdrs = ["wave_reader.h"],
    srcs = ["wave_reader.cpp"],
    visibility = ["//visibility:public"]
)

cc_library(
    name = "online_feature",
    hdrs = ["online_feature.h"],
    srcs = ["online_feature.cpp"],
    deps = ["@kaldi//:feat", "@kaldi//:online2"],
    visibility = ["//visibility:public"]
)