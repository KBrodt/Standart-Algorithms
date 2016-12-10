#!/bin/bash

mkdir -p ../bin/linux_release
make compile_flags="-std=c++14 -O3 -funroll-loops -fomit-frame-pointer"     --directory=../bin/linux_release     --makefile=../../project/Makefile
