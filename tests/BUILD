cc_test(
    name = "tests",
    srcs = ["tests.cpp"],
    deps = ["@gtest//:gtest", "//asr:asr"],
    data = ["test.wav", "model"],
    linkopts = ["-ldl"]
)