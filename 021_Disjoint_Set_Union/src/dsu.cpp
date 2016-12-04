#include <iostream>
#include <vector>
#include <unordered_map>

/** Disjoint Set union using std::unordered_map
 */
template <class T>
class DSU {
 private:
  std::unordered_map<T, T> parent_;

 public:
  DSU() : parent_(0) {}

  void make(T element) { parent_.insert({element, element}); }

  T find(const T& element) {
    return parent_[element] == element ? element : parent_[element] =
                                                       find(parent_[element]);
  }

  void unite(T element_first, T element_second) {
    element_first = find(element_first);
    element_second = find(element_second);
    if (std::rand() & 1) {
      std::swap(element_first, element_second);
    }
    if (element_first != element_second) {
      parent_[element_first] = element_second;
    }
  }

  friend std::ostream& operator<<(std::ostream& os, const DSU<T>& dsu) {
    for (const auto& element : dsu.parent_) {
      os << element.first << ": " << element.second << "\n";
    }
    return os;
  }
};

/** Disjoint Set union using simple std::vector on ints
 */
class DSUi {
 private:
  std::vector<int32_t> parent_;

 public:
  explicit DSUi(int32_t size = 0) : parent_(size) {
    for (int32_t index = 0; index < size; ++index) {
      parent_[index] = index;
    }
  }

  void make(int32_t element) { parent_.push_back(element); }

  int32_t find(const int32_t& element) {
    return parent_[element] == element ? element : parent_[element] =
                                                       find(parent_[element]);
  }

  void unite(int32_t element_first, int32_t element_second) {
    element_first = find(element_first);
    element_second = find(element_second);
    if (std::rand() & 1) {
      std::swap(element_first, element_second);
    }
    parent_[element_first] = element_second;
  }

  friend std::ostream& operator<<(std::ostream& os, const DSUi& dsu) {
    int32_t size = static_cast<int32_t>(dsu.parent_.size());
    for (int32_t index = 0; index < size; ++index) {
      os << index << ": " << dsu.parent_[index] << "\n";
    }
    return os;
  }
};

int32_t main() {

  DSUi dsu(5);
  std::cout << dsu;
  dsu.unite(0,4);
  dsu.unite(0,3);
  std::cout << dsu;
  for ( int32_t i = 0; i < 5; ++i ) {
    std::cout << dsu.find(i) << "\n";
  }

  return 0;
}
