# Test so

1. build so: `bazel build asr:libasr.so.0.0.0`.
2. enter so_example: `cd so_example`.
3. cp so: `ln -s ../bazel-bin/asr/libasr.so.0.0.0 libasr.so`.
4. make: `make`
5. test: `./test`.
