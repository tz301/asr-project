cc_test(
    name = "tests",
    srcs = ["tests.cpp"],
    deps = [
        "@gtest//:gtest",
        "//asr:asr",
        "//asr:wave_reader"
    ],
    data = ["test.wav", "model"],
    linkopts = ["-ldl"]
)