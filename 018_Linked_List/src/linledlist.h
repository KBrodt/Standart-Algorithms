#ifndef STDALG_LINKEDLIST_H_
#define STDALG_LINKEDLIST_H_

#include <iostream>

using i32_t = int;
using u32_t = unsigned;

template <class Type>
class LinckedList;

template <class Type>
std::ostream operator<<(std::ostream&, const LinckedList<Type>&);

template <class Type=i32_t>
class LinckedList {
private:
  u32_t key_;
  LinckedList* previous_;
  LinckedList* next_;
public:
  LinckedList()
    : key_(0),
      previous_(nullptr),
      next_(nullptr) {}
  ~LinckedList() { delete [] previous_; delete [] next_; }

  friend std::ostream& operator<<<>(std::ostream& os, const LinckedList& list);
};

#endif // STDALG_LINKEDLIST_H_xs
