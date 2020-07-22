#!/bin/sh
# $1: .i file.
# $2: module name.
# $3: generated file.
# $4: output directory.
swig -c++ -python -module $2 -o $3 -outdir $4 $1
