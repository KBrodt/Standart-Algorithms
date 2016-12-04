#!/bin/bash

mkdir -p ../bin/linux_debug
make compile_flags="-std=c++11 -Wall -O0 -g"     --directory=../bin/linux_debug     --makefile=../../project/Makefile
