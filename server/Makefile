# Created by tz301 on 2020/07/03
LIB := -L. -lasr -lzmq -L/opt/intel/mkl/lib/intel64 -Wl,-rpath=.

server: server.cpp
	g++ $^ -std=c++11 -I. $(LIB) -o $@

.PHONY: clean
clean:
	-rm -rf server
