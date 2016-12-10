#!/bin/bash

mkdir -p ../bin/linux_debug
make compile_flags="-std=c++14 -Wall -Werror -O0 -g"     --directory=../bin/linux_debug     --makefile=../../project/Makefile
