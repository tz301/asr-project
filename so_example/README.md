# Test so

1. build so: `bazel build asr:libasr.so.0.0.0`.
2. cp so: `cp bazel-bin/asr/libasr.so.0.0.0 so_example/libasr.so`.
3. make: `cd so_example; make`
4. test: `./test`.
