cc_library(
    name = "mkl",
    hdrs = glob(["include/*.h"]),
    srcs = [
        "lib/intel64/libmkl_avx2.so",
        "lib/intel64/libmkl_core.so",
        "lib/intel64/libmkl_def.so",
        "lib/intel64/libmkl_intel_lp64.so",
        "lib/intel64/libmkl_sequential.so",
        "lib/intel64/libmkl_vml_avx2.so",
    ],
    strip_include_prefix = "include",
    visibility = ["//visibility:public"]
)
