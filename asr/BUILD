ASR_SCRS = ["asr.cpp"]
ASR_DEPS = ["//asr/asr:online_asr"]

cc_library(
    name = "asr",
    hdrs = ["asr.h"],
    srcs = ASR_SCRS,
    deps = ASR_DEPS,
    visibility = ["//visibility:public"]
)

cc_binary(
    name = "libasr.so.0.0.0",
    srcs = ASR_SCRS + ["asr.h"],
    deps = ASR_DEPS,
    linkstatic = 1,
    linkshared = True,
)

py_library(
    name = "asr_py",
    srcs = ["__init__.py"],
    deps = ["//asr/pywrap:asr_wrap"],
    visibility = ["//visibility:public"]
)
