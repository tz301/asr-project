cc_test(
    name = "tests",
    srcs = ["tests.cpp"],
    deps = [
        "@gtest//:gtest",
        "//asr:online_feature"],
        "//asr:wave_reader"
    data = ["test.wav", "mfcc.conf"],
    linkopts = ["-ldl"]
)