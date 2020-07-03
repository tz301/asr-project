# Created by tz301 on 2020/07/03
LIB := -L. -lasr -L/opt/intel/mkl/lib/intel64 -Wl,-rpath=.

test: test.cpp
	g++ $^ -std=c++11 -I. $(LIB) -o $@

.PHONY: clean
clean:
	-rm -rf test
