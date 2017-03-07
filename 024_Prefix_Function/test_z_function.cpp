#include <gtest/gtest.h>

#include "z_function.h"

TEST(ZFunction, Simple) {
  ASSERT_EQ(std::vector<int>({1}),
            calcZFunction("a"));

  ASSERT_EQ(std::vector<int>({5, 4, 3, 2, 1}),
            calcZFunction("aaaaa"));

  ASSERT_EQ(std::vector<int>({7, 2, 1, 0, 2, 1, 0}),
            calcZFunction("aaabaab"));

  ASSERT_EQ(std::vector<int>({7, 0, 1, 0, 3, 0, 1}),
            calcZFunction("abacaba"));

  ASSERT_EQ(std::vector<int>({11, 0, 0, 1, 0, 1, 0, 4, 0, 0, 1}),
            calcZFunction("abracadabra"));
}

TEST(ZFunction, Stress) {
  std::vector<int> zf(1000000,1000000);
  std::string big_pattern = "b";
  for ( auto i = 0u; i < 999999u; ++i ) {
    big_pattern += "b";
    zf[i+1] -= i + 1;
  }
  ASSERT_EQ(zf, calcZFunction(big_pattern));
}
