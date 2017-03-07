#include <iostream>
#include <string>
#include <vector>

std::vector<int> calcPrefixFunction(const std::string& pattern) {
  const auto length = pattern.size();
  std::vector<int> prefix_function(length, 0);
  for ( auto i = 1u; i < length; ++i ) {
    auto k = prefix_function[i-1];
    while ( k > 0 && pattern[i] != pattern[k] ) {
      k = prefix_function[k-1];
    }
    if ( pattern[i] == pattern[k] ) {
      ++k;
    }
    prefix_function[i] = k;
  }

  return prefix_function;
}
