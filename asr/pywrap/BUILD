load("//third_party:pywrap.bzl", "pywrap_library")

py_library(
    name = "asr_wrap",
    srcs = ["__init__.py", "asr.py"],
    deps = ["asr_py"],
    visibility = ["//visibility:public"]
)

pywrap_library(
    name = "asr_py",
    srcs = ["asr.i"],
    deps = [
        "//third_party/swig:python_lib",
        "//third_party/swig:numpy_lib",
        "asr_cpp",
    ],
    swig_includes = ["numpy.i"],
)

cc_library(
    name = "asr_cpp",
    hdrs = ["asr.h"],
    srcs = ["asr.cpp"],
    deps = ["//third_party:version_script.lds", "//asr:asr"],
    linkopts = ["-Wl,--version-script,$(location //third_party:version_script.lds)"]
)
