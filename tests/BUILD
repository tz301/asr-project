DATA = ["test.wav", "model"]

cc_test(
    name = "tests",
    srcs = ["tests.cpp"],
    deps = ["@gtest//:gtest", "//asr:asr"],
    data = DATA,
    linkopts = ["-ldl"]
)

py_test(
    name = "tests_py",
    srcs = ["tests.py"],
    deps = ["//asr:asr_py"],
    data = DATA,
    default_python_version = "PY3",
)