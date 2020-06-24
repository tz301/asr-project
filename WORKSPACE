workspace(name = "tz_asr")

load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "io_bazel_rules_closure",
    sha256 = "5b00383d08dd71f28503736db0500b6fb4dda47489ff5fc6bed42557c07c6ba9",
    strip_prefix = "rules_closure-308b05b2419edb5c8ee0471b67a40403df940149",
    urls = [
        "https://github.com/bazelbuild/rules_closure/archive/308b05b2419edb5c8ee0471b67a40403df940149.tar.gz",
    ],
)

http_archive(
    name = "gtest",
    strip_prefix = "googletest-release-1.10.0",
    urls = ["https://github.com/google/googletest/archive/release-1.10.0.tar.gz"],
    sha256 = "9dc9157a9a1551ec7a7e43daea9a694a0bb5fb8bec81235d8a1e6ef64c716dcb",
)

http_archive(
    name = "bazel_skylib",
    sha256 = "2ef429f5d7ce7111263289644d233707dba35e39696377ebab8b0bc701f7818e",
    urls = ["https://github.com/bazelbuild/bazel-skylib/releases/download/0.8.0/bazel-skylib.0.8.0.tar.gz"],
)

http_archive(
    name = "org_tensorflow",
    strip_prefix = "tensorflow-1.15.2",
    sha256 = "d95d75d26a298211b5e802842e87fda5b8b14f6ad83719377b391e5fb71b8746",
    urls = ["https://github.com/tensorflow/tensorflow/archive/v1.15.2.tar.gz"]
)

load("@org_tensorflow//tensorflow:workspace.bzl", "tf_workspace")
tf_workspace(tf_repo_name = "org_tensorflow")

# local mkl.
new_local_repository(
    name = "mkl",
    build_file = "//:mkl.BUILD",
    path = "/opt/intel/mkl"
)

# git clone https://github.com/kaldi-asr/kaldi.git to local.
new_local_repository(
    name = "kaldi",
    build_file = "//:kaldi.BUILD",
    path = "/home/ubuntu/github/kaldi"
)
