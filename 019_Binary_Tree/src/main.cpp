#include "binsearchtree.h"

int32_t main() {

  Tree<> tree;
  tree.Insert(1);
  tree.InorderTreeWalk(); std::cout << "\n";
  tree.Insert(5);
  tree.Insert(5);
  tree.Insert(3);
  tree.InorderTreeWalk(); std::cout << "\n";
  tree.Insert(2);
  tree.InorderTreeWalk(); std::cout << "\n";
  std::cout << std::boolalpha;
  std::cout << "element 5 is found: " << tree.Search(5) << "\n";
  std::cout << "element 4 is found: " << tree.Search(4) << "\n";
  std::cout << "max: "<< tree.Max() << "\n";
  tree.InorderTreeWalk(); std::cout << "\n";
  tree.Insert(7);
  std::cout << "max: "<< tree.Max() << "\n";
  tree.InorderTreeWalk(); std::cout << "\n";
  std::cout << "min: "<< tree.Min() << "\n";
  std::cout << "successor of 5: "<< tree.Successor(5) << "\n";
  tree.InorderTreeWalk(); std::cout << "\n";
  std::cout << "max: "<< tree.Max() << "\n";
  std::cout << "successor of 7: "<< tree.Successor(7) << "\n";
  tree.InorderTreeWalk(); std::cout << "\n";
  tree.Delete(5);
  tree.Delete(5);
  tree.Delete(5);
  tree.InorderTreeWalk(); std::cout << "\n";

  return 0;
}
