project(a-prefix-func)

cmake_minimum_required(VERSION 2.8)
include(../common.cmake)

set(SRCS prefix_function.cpp)

add_library(prefix_function ${SRCS})

add_gtest(test_prefix_function test_prefix_function.cpp)
target_link_libraries(test_prefix_function prefix_function)

add_executable(pf prefix_function.cpp)
target_link_libraries(pf prefix_function)
