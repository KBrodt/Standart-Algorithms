#ifndef STDALG_DEQUEUE_H_
#define STDALG_DEQUEUE_H_

#include <iostream>
#include <algorithm>

using i32 = int;
using u32 = unsigned;

template <class Type>
class Dequeue;

template <class Type>
std::ostream& operator<<(std::ostream&, const Dequeue<Type>&);

/**
 * Simple Dequeue class with basic operations
 * push_back, push_front, pop_back and pop_front
 */
template <class Type=i32>
class Dequeue {
private:
  Type* d_;
  u32 capacity_;
  i32 head_, tail_;
public:
  Dequeue()
    : d_(new Type[8]),
      capacity_(8),
      head_(0),
      tail_(0) {}
  Dequeue(const u32 capacity)
    : d_(new Type[capacity]),
      capacity_(capacity),
      head_(0),
      tail_(0) {}
  Dequeue(const std::initializer_list<Type>& list);
  ~Dequeue() { delete [] d_; }

  bool empty() const { return head_ == tail_; }
  bool full() const;
  void resize(const u32 new_size);

  void push_back(const Type& value);
  void push_front(const Type& value);
  Type pop_back();
  Type pop_front();
  
  u32 size() const;
  u32 capacity() const { return capacity_; }

  friend std::ostream& operator<<<>(std::ostream& os, const Dequeue& dequeue);
};

template <class Type>
Dequeue<Type>::Dequeue(const std::initializer_list<Type>& list) {
  capacity_ = list.size() << 1;
  head_ = 0; tail_ = static_cast<i32>(list.size());
  d_ = new Type[capacity_];
  std::copy(list.begin(), list.end(), &d_[0]);
}

template <class Type>
bool Dequeue<Type>::full() const {
  if ( (head_ == 0 && tail_ + 1 == static_cast<i32>(capacity_)) ||
       head_ == tail_ + 1 ) return true;
  return false;
}

template <class Type>
void Dequeue<Type>::resize(const u32 new_size) {
  tail_ = this->size();
  Type* old_data = new Type[capacity_];
  for ( u32 index = 0; index < capacity_; ++index ) {
    old_data[index] = d_[index];
  }
  delete [] d_;
  d_ = new Type[new_size];
  for ( u32 index = 0; index < std::min(new_size, capacity_); ++index ) {
    d_[index] = old_data[(static_cast<i32>(index)+head_)%static_cast<i32>(capacity_)];
  }
  delete [] old_data;
  capacity_ = new_size;
  head_ = 0;
  std::cout << "resized\n";
}

template <class Type>
void Dequeue<Type>::push_back(const Type& value) {
  if ( this->full() ) {
    this->resize(capacity_ << 1);
  }
  d_[tail_] = value;
  tail_ = (tail_ + 1)%static_cast<i32>(capacity_);
}

template <class Type>
void Dequeue<Type>::push_front(const Type& value) {
  if ( this->full() ) {
    this->resize(capacity_ << 1);
  }
  head_ = (head_ - 1)%static_cast<i32>(capacity_);
  head_ = head_ < 0 ? head_ + static_cast<i32>(capacity_) : head_;
  d_[head_] = value;
}

template <class Type>
Type Dequeue<Type>::pop_back() {
  if ( this->empty() ) {
    throw std::runtime_error("Dequeue is empty");
  }
  if ( this->size() <= (capacity_ >> 2) + 1 ) {
    this->resize(capacity_ >> 1);
  }
  tail_ = (tail_ - 1)%static_cast<i32>(capacity_);
  tail_ = tail_ < 0 ? tail_ + static_cast<i32>(capacity_) : tail_;
  Type value = d_[tail_];
  d_[tail_] = 0;
  return value;
}

template <class Type>
Type Dequeue<Type>::pop_front() {
  if ( this->empty() ) {
    throw std::runtime_error("Dequeue is empty");
  }
  u32 previous_head = head_;
  head_ = (head_ + 1)%static_cast<i32>(capacity_);
  Type value = d_[previous_head];
  d_[previous_head] = 0;
  if ( this->size() <= (capacity_ >> 2) + 1) {
    this->resize(capacity_ >> 1);
  }
  return value;
}

template <class Type>
u32 Dequeue<Type>::size() const {
  return head_ <= tail_ ? tail_ - head_ : tail_ + capacity_ - head_;
}

template <class Type>
std::ostream& operator<<(std::ostream& os, const Dequeue<Type>& dequeue) {
  for ( u32 index = 0;
	index < dequeue.capacity_;
	++index ) {
    os << dequeue.d_[index] << " ";
  }
  os << " | ";
  if ( dequeue.head_ <= dequeue.tail_ ) {
    for ( i32 index = dequeue.head_;
	  index < dequeue.tail_; ++index ) {
      os << dequeue.d_[index] << " ";
    }
  } else {
    for ( i32 index = dequeue.head_;
	  index < static_cast<i32>(dequeue.capacity_); ++index ) {
      os << dequeue.d_[index] << " ";
    }
    for ( i32 index = 0;
	  index < dequeue.tail_; ++index ) {
      os << dequeue.d_[index] << " ";
    }
  }
  return os;
}

#endif // STDALG_DEQUEUE_H_
