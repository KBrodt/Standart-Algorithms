#ifndef STDALG_STACK_H_
#define STDALG_STACK_H_

#include <iostream>

using i32 = int;
using u32 = unsigned;

template<class Type>
class Stack;

template<class Type>
std::ostream& operator<<(std::ostream&, const Stack<Type>&);

/**
 * Simple Stack class with default operation push and pop
 */
template <class Type=i32> 
class Stack{
private:
  Type* s_;
  u32 capacity_;
  i32 top_;
public:
  Stack()
    : s_(new Type[8]),
      capacity_(8),
      top_(-1) {}
  Stack(const u32 capacity)
    : s_(new Type[capacity]),
      capacity_(capacity),
      top_(-1) {}
  ~Stack() { delete [] s_; }

  bool empty() const;
  bool full() const;
  
  void resize(const u32 news_ize);
  void push(const Type& value);
  Type pop();
  
  i32 top() const { return top_; }

  u32 size() const { return top_+1; }
  u32 capacity() const { return capacity_; }

  friend std::ostream& operator<<<>(std::ostream& os, const Stack& stack);
};

template <class Type>
bool Stack<Type>::empty() const {
  if ( top_ == -1 ) {
    return true;
  }
  return false;
}

template <class Type>
bool Stack<Type>::full() const {
  if ( top_ + 1 == static_cast<i32>(capacity_) ) {
    return true;
  }
  return false;
}

template <class Type>
void Stack<Type>::resize(const u32 new_size) {
  Type* old_data = new Type[this->size()];
  for ( u32 index = 0; index < this->size(); ++index ) {
    old_data[index] = s_[index];
  }
  
  delete [] s_;
  capacity_ = new_size;
  s_ = new Type[capacity_]; // may throw exception
  for ( u32 index = 0; index < this->size(); ++index ) {
    s_[index] = old_data[index];
  }
  delete [] old_data;
  
  // std::cout << "resized\n";
}

template <class Type>
void Stack<Type>::push(const Type& value) {
  if ( this->full() ) {
    this->resize(capacity_ << 1);
  }
  s_[++top_] = value;
}

template <class Type>
Type Stack<Type>::pop() {
  if ( empty() ) throw std::runtime_error("Stack is empty");
  if ( this->size() <= (capacity_ >> 2) ) {
    this->resize(capacity_ >> 1);
  }
  return s_[top_--];
}

template <class Type>
std::ostream& operator<<(std::ostream& os, const Stack<Type>& stack) {
  for ( u32 i = 0; i <= static_cast<u32>(stack.top_); ++i ) {
    os << stack.s_[i] << " ";
  }
  return os;
}

#endif // STDALG_STACK_H_
