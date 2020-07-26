# Server

1. build so: `bazel build asr:libasr.so.0.0.0`.
2. enter server directory: `cd server`.
3. link so: `ln -s ../bazel-bin/asr/libasr.so.0.0.0 libasr.so`.
4. build c++ asr server: `make`.
5. start asr server in background: `nohup ./server <model_dir> <asr_port> 2>&1 >log_server &`.
6. test asr server: `python3 client.py <asr_port>`.
7. deploy server: `python3 server.py <asr_port> <server_port>`.

Then you can use url \<ip\>:\<server_port\> for asr.
