#include "linkedlist.h"

i32_t main() {
  LinkedList<i32_t> list(1);
  std::cout << list << "\n";
  list.insert(2);
  list.insert(3);
  list.insert(4);
  list.insert(5);
  std::cout << list << "\n";
  list.remove(3);
  std::cout << list << "\n";
  return 0;
}
