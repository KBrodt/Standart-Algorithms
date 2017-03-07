#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

std::vector<int> calcZFunction(const std::string& pattern) {
  int size = static_cast<int>(pattern.size());
  std::vector<int> z_function(size);
  z_function[0] = size;
  int left = 0, right = 0;
  for ( int i = 1; i < size; ++i ) {
    if ( i < right ) {
      z_function[i] = std::min(z_function[i-left], right-i);
    } else {
      z_function[i] = 0;
    }
    while ( pattern[i+z_function[i]] == pattern[z_function[i]] &&
            i + z_function[i] < size ) {
      ++z_function[i];
    }
    if ( right < i + z_function[i] ) {
      left = i;
      right = i + z_function[i];
    }
  }

  return z_function;
}
