#ifndef STDALG_LINKEDLIST_H_
#define STDALG_LINKEDLIST_H_

#include <iostream>
#include <vector>

using i32_t = int;
using u32_t = unsigned;

template <class Type>
using vector = std::vector<Type>;

template <class Type>
class LinkedList;

template <class Type>
std::ostream& operator<<(std::ostream&, const LinkedList<Type>&);

/**
 * Simple Linked List class with basic operations
 * insert and delete.
 */
template <class Type=i32_t>
class LinkedList {
private:
  struct Node {
    Type key_;
    Node* next_;
    Node* previous_;
    Node()
      : key_((Type)0)
      , next_(nullptr)
      , previous_(nullptr) {}
    Node(const Type& key, Node* next=nullptr, Node* previous=nullptr)
      : key_((Type)key)
      , next_(next)
      , previous_(previous) {}
  };
  Node nil_;
  u32_t size_;
public:
  LinkedList()
    : size_(0) { nil_.key_ = (Type)0; nil_.next_ = &nil_; nil_.previous_ = &nil_; }
  explicit LinkedList(const Type& key);
  ~LinkedList();

  u32_t size() const { return size_; }

  void insert(const Type& key);
  void remove(const Type& key);
  
  void print(std::ostream& os) const;
  friend std::ostream& operator<<<>(std::ostream& os, const LinkedList& list);
};

template <class Type>
LinkedList<Type>::LinkedList(const Type& key) {
  nil_.key_ = (Type)0; nil_.next_ = &nil_; nil_.previous_ = &nil_;
  Node* node = new Node(key, &nil_, &nil_);
  nil_.next_ = node;
  size_ = 1;
}

template <class Type>
LinkedList<Type>::~LinkedList() {
  Node* node = nil_.next_;
  while ( node != &nil_ ) {
    Node* del_node = node;
    node = node->next_;
    delete del_node;
  }
}

template <class Type>
void LinkedList<Type>::insert(const Type& key) {
  Node* node = new Node(key, nil_.next_, &nil_);
  nil_.next_->previous_ = node;
  nil_.next_ = node;
  size_++;
}

template <class Type>
void LinkedList<Type>::remove(const Type& key) {
  Node* node = nil_.next_;
  while ( node != &nil_ && node->key_ != key ) {
    node = node->next_;
  }
  if ( node != &nil_ ) size_--;
  node->previous_->next_ = node->next_;
  node->next_->previous_ = node->previous_;
}

template <class Type>
void LinkedList<Type>::print(std::ostream& os) const {
  Node* node = nil_.next_;
  os << size_ << ": ";
  while ( node != &nil_ ) {
    os << node->key_  << " ";
    node = node->next_;
  }
}

template <class Type>
std::ostream& operator<<(std::ostream& os,
			 const LinkedList<Type>& list) {
  list.print(os);
  return os;
}

#endif // STDALG_LINKEDLIST_H_
