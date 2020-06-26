cc_library(
    name = "feat",
    hdrs = [
        "src/feat/feature-common.h",
        "src/feat/feature-common-inl.h",
        "src/feat/feature-fbank.h",
        "src/feat/feature-functions.h",
        "src/feat/feature-mfcc.h",
        "src/feat/feature-plp.h",
        "src/feat/feature-window.h",
        "src/feat/mel-computations.h",
        "src/feat/online-feature.h",
        "src/feat/resample.h"
    ],
    srcs = [
        "src/feat/feature-fbank.cc",
        "src/feat/feature-functions.cc",
        "src/feat/feature-mfcc.cc",
        "src/feat/feature-plp.cc",
        "src/feat/feature-window.cc",
        "src/feat/mel-computations.cc",
        "src/feat/online-feature.cc",
        "src/feat/resample.cc"
    ],
    deps = ["transform"],
    strip_include_prefix = "src",
    visibility = ["//visibility:public"]
)

cc_library(
    name = "online2",
    hdrs = ["src/online2/online-ivector-feature.h"],
    srcs = ["src/online2/online-ivector-feature.cc"],
    deps = ["decoder", "feat", "ivector"],
    strip_include_prefix = "src",
    visibility = ["//visibility:public"]
)


cc_library(
    name = "decoder",
    hdrs = [
        "src/decoder/grammar-fst.h",
        "src/decoder/lattice-faster-decoder.h",
        "src/decoder/lattice-faster-online-decoder.h",
        "src/decoder/lattice-incremental-decoder.h",
        "src/decoder/lattice-incremental-online-decoder.h"
    ],
    srcs = [
        "src/decoder/grammar-fst.cc",
        "src/decoder/lattice-faster-decoder.cc",
        "src/decoder/lattice-faster-online-decoder.cc",
        "src/decoder/lattice-incremental-decoder.cc",
        "src/decoder/lattice-incremental-online-decoder.cc"
    ],
    deps = ["lat"],
    strip_include_prefix = "src"
)

cc_library(
    name = "fstext",
    hdrs = glob(["src/fstext/*.h"]),
    srcs = glob(["src/fstext/*.cc"], exclude = ["src/fstext/*test.cc"]),
    deps = ["utils"],
    strip_include_prefix = "src"
)

cc_library(
    name = "gmm",
    hdrs = [
        "src/gmm/diag-gmm.h",
        "src/gmm/diag-gmm-inl.h",
        "src/gmm/diag-gmm-normal.h",
        "src/gmm/full-gmm.h",
        "src/gmm/full-gmm-inl.h",
        "src/gmm/full-gmm-normal.h",
        "src/gmm/model-common.h"
    ],
    srcs = [
        "src/gmm/diag-gmm.cc",
        "src/gmm/diag-gmm-normal.cc",
        "src/gmm/full-gmm.cc",
        "src/gmm/full-gmm-normal.cc",
        "src/gmm/model-common.cc"
    ],
    deps = ["tree"],
    strip_include_prefix = "src"
)

cc_library(
    name = "hmm",
    hdrs = [
        "src/hmm/hmm-topology.h",
        "src/hmm/hmm-utils.h",
        "src/hmm/posterior.h",
        "src/hmm/transition-model.h"
    ],
    srcs = [
        "src/hmm/hmm-topology.cc",
        "src/hmm/hmm-utils.cc",
        "src/hmm/posterior.cc",
        "src/hmm/transition-model.cc"
    ],
    deps = ["lattice", "tree"],
    strip_include_prefix = "src"
)

cc_library(
    name = "ivector",
    hdrs = ["src/ivector/ivector-extractor.h"],
    srcs = ["src/ivector/ivector-extractor.cc"],
    deps = ["hmm", "gmm"],
    strip_include_prefix = "src"
)

cc_library(
    name = "lat",
    hdrs = [
        "src/lat/determinize-lattice-pruned.h",
        "src/lat/lattice-functions.h",
        "src/lat/minimize-lattice.h",
        "src/lat/push-lattice.h"
    ],
    srcs = [
        "src/lat/determinize-lattice-pruned.cc",
        "src/lat/lattice-functions.cc",
        "src/lat/minimize-lattice.cc",
        "src/lat/push-lattice.cc"
    ],
    deps = ["hmm"],
    strip_include_prefix = "src"
)

cc_library(
    name = "lattice",
    hdrs = ["src/lat/kaldi-lattice.h"],
    srcs = ["src/lat/kaldi-lattice.h"],
    deps = ["fstext"],
    strip_include_prefix = "src"
)

cc_library(
    name = "openfst",
    srcs  = glob(
        [
            "tools/openfst/src/lib/*.cc",
            "tools/openfst/src/script/*.cc"
        ]
    ),
    hdrs = glob(
        [
            "tools/openfst/include/fst/*.h",
            "tools/openfst/include/fst/script/*.h"
        ]
    ),
    strip_include_prefix = "tools/openfst/include"
)

cc_library(
    name = "transform",
    hdrs = ["src/transform/cmvn.h"],
    srcs = ["src/transform/cmvn.cc"],
    deps = ["utils"],
    strip_include_prefix = "src",
)

cc_library(
    name = "tree",
    hdrs = [
        "src/tree/build-tree.h",
        "src/tree/build-tree-questions.h",
        "src/tree/build-tree-utils.h",
        "src/tree/clusterable-classes.h",
        "src/tree/cluster-utils.h",
        "src/tree/context-dep.h",
        "src/tree/event-map.h"
    ],
    srcs = [
        "src/tree/build-tree.cc",
        "src/tree/build-tree-questions.cc",
        "src/tree/build-tree-utils.cc",
        "src/tree/clusterable-classes.cc",
        "src/tree/cluster-utils.cc",
        "src/tree/context-dep.cc",
        "src/tree/event-map.cc"
    ],
    deps = ["utils"],
    strip_include_prefix = "src"
)

cc_library(
    name = "utils",
    hdrs = glob(
        [
            "src/base/*.h",
            "src/itf/*.h",
            "src/matrix/*.h",
            "src/util/*.h"
        ]
    ),
    srcs = glob(
        [
            "src/base/*.cc",
            "src/matrix/*.cc",
            "src/util/*.cc"
        ],
        exclude = [
            "src/base/*test.cc",
            "src/matrix/*test.cc",
            "src/util/*test.cc"
        ]
    ),
    deps = ["@mkl//:mkl", "openfst"],
    copts = [
        "-DHAVE_CXXABI_H",
        "-DHAVE_EXECINFO_H=1",
        "-DHAVE_MKL",
        "-DKALDI_DOUBLEPRECISION=0",
    ],
    strip_include_prefix = "src"
)
