project(b-z_func)

cmake_minimum_required(VERSION 2.8)
include(../common.cmake)

set(SRCS z_function.cpp)

add_library(z_function ${SRCS})

add_gtest(test_z_function test_z_function.cpp)
target_link_libraries(test_z_function z_function)

add_executable(zf z_function.cpp)
target_link_libraries(zf z_function)
