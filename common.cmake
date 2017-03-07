include_directories(.)
include_directories(/usr/src/gtest)

# add_gtest: common boilerplate for creation gtest executable
# Uses gtest library from libgtest-dev package
function(add_gtest BINARY_NAME)
  list(REMOVE_AT ARGV 0)

  add_executable(${BINARY_NAME}
    /usr/src/gtest/src/gtest_main.cc
    ${ARGV}
  )
  target_link_libraries(${BINARY_NAME} shad-gtest pthread dl)
endfunction(add_gtest)

set(CXX_STANDARD 14)
if (CMAKE_COMPILER_IS_GNUCC AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 5.0)
    set(CXX_STANDARD 11)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++${CXX_STANDARD} -Wall")

set(CMAKE_CXX_FLAGS_ASAN "-g -O3 -fsanitize=address,undefined"
    CACHE STRING "Compiler flags in asan build"
    FORCE)

set(CMAKE_CXX_FLAGS_TSAN "-g -O3 -fsanitize=thread"
    CACHE STRING "Compiler flags in tsan build"
    FORCE)
# Work around broker ThreadSanitizer on 16.10
set(CMAKE_EXE_LINKER_FLAGS_TSAN "-no-pie"
    CACHE STRING "Linker flags in tsan build"
    FORCE)
