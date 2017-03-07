#include "prefix_function.h"

template <class T>
std::ostream& operator<<(std::ostream& os,
                         const std::vector<T>& v ) {
  for ( const auto& value : v ) {
    os << value << " ";
  }

  return os;
}

std::string readInput(std::istream& is = std::cin) {
  std::string pattern;
  is >> pattern;

  return pattern;
}

int main() {
  // need when iostream input/output data is over 100000 elements
  std::ios_base::sync_with_stdio(false);

  std::cout << calcPrefixFunction(readInput());
  return 0;
}
