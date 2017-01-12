#include "redblacktree.h"

int32_t main() {
  RedBlackTree<int32_t> rbtree;
  rbtree.InorderTreeWalk();
  rbtree.Insert(2);
  rbtree.Insert(2);
  rbtree.Insert(2);
  rbtree.Insert(3);
  rbtree.InorderTreeWalk(); std::cout << "\n";
  std::cout << rbtree.Search(2) << "\n";
  rbtree.Delete(2);
  rbtree.InorderTreeWalk(); std::cout << "\n";
  rbtree.Delete(2);
  rbtree.InorderTreeWalk(); std::cout << "\n";
  rbtree.Delete(2);
  rbtree.InorderTreeWalk(); std::cout << "\n";
  rbtree.Delete(2);
  rbtree.InorderTreeWalk(); std::cout << "\n";

  return 0;
}
