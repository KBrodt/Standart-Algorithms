#include <gtest/gtest.h>

#include "prefix_function.h"

TEST(PrefixFunction, Simple){
  ASSERT_EQ(std::vector<int>({0}),
            calcPrefixFunction({"a"}));

  ASSERT_EQ(std::vector<int>({0, 1, 2, 3, 4, 5, 6, 7, 8, 9}),
            calcPrefixFunction({"zzzzzzzzzz"}));

  ASSERT_EQ(std::vector<int>({0, 1, 0, 1, 2, 2, 3}),
            calcPrefixFunction({"aabaaab"}));

  ASSERT_EQ(std::vector<int>({0, 0, 1, 0, 1, 2, 3}),
            calcPrefixFunction({"abacaba"}));

  ASSERT_EQ(std::vector<int>({0, 0, 0, 1, 2, 3, 0}),
            calcPrefixFunction({"abcabcd"}));

  ASSERT_EQ(std::vector<int>({0, 0, 0, 1, 0, 1, 0, 1, 2, 3, 4}),
            calcPrefixFunction({"abracadabra"}));
}

TEST(PrefixFunction, Stress){
  std::string big_pattern = "b";
  std::vector<int> pf(1000000u, 0);
  for ( auto i = 0u; i < 999999u; ++i ) {
    big_pattern += "b";
    pf[i+1] = i+1;
  }

  ASSERT_EQ(pf, calcPrefixFunction(big_pattern));
}
