#ifndef STDALG_BINARYTREE_H_
#define STDALG_BINARYTREE_H_

#include <iostream>
#include <cstdint>

/**
 * Simple Binary Tree struct with basic operations
 */
class Tree {
private:
  struct Node {
    int32_t key_;
    Node* parent_ = nullptr;
    Node* left_ = nullptr;
    Node* right_ = nullptr;
    Node(int32_t key)
      : key_(key)
      , parent_(nullptr)
      , left_(nullptr)
      , right_(nullptr) {}
    Node(const Node* node)
      : key_(node->key_)
      , parent_(node->parent_)
      , left_(node->left_)
      , right_(node->right_) {}
  };

  Node* root_;
private:

  void PreorderTreeWalk(Node* x) {
    if ( x != nullptr ) {
      std::cout << x->key_ << " ";
      PreorderTreeWalk(x->left_);
      PreorderTreeWalk(x->right_);
    }
  }

  void InorderTreeWalk(Node* x) {
    if ( x != nullptr ) {
      InorderTreeWalk(x->left_);
      std::cout << x->key_ << " ";
      InorderTreeWalk(x->right_);
    }
  }

  void PostorderTreeWalk(Node* x) {
    if ( x != nullptr ) {
      PostorderTreeWalk(x->left_);
      PostorderTreeWalk(x->right_);
      std::cout << x->key_ << " ";
    }
  }

  Node* TreeSearch(Node* x, int32_t key) {
    if ( x == nullptr || key == x->key_ ) {
      return x;
    }
    if ( key < x->key_ ) {
      return TreeSearch(x->left_, key);
    } else {
      return TreeSearch(x->right_, key);
    }
  }

  Node* TreeMinimum(Node* x) {
    while ( x->left_ != nullptr ) {
      x = x->left_;
    }
    return x;
  }

  Node* TreeMaximum(Node* x) {
    while ( x->right_ != nullptr ) {
      x = x->right_;
    }
    return x;
  }

  Node* TreeSuccessor(Node* x) {
    if ( x->right_ != nullptr ) {
      return TreeMinimum(x->right_);
    }
    Node* y = x->parent_;
    while ( y != nullptr && x == y->right_ ) {
      x = y;
      y = y->parent_;
    }
    return y;
  }

  Node* TreeInsert(Node* tree, Node* z) {
    Node* y = nullptr;
    Node* x = tree;
    while ( x != nullptr ) {
      y = x;
      if ( z->key_ < x->key_ ) {
	x = x->left_;
      } else {
	x = x->right_;
      }
    }
    z->parent_ = y;
    if ( y == nullptr ) {
      tree = z;
    } else if ( z->key_< y->key_ ) {
      y->left_ = z;
    } else {
      y->right_ = z;
    }
    return tree;
  }

  Node* Transplant(Node* tree, Node* u, Node* v) {
    if ( u->parent_ == nullptr ) {
      tree = v;
    } else if ( u == u->parent_->left_ ) {
      u->parent_->left_ = v;
    } else {
      u->parent_->right_ = v;
    }
    if ( v != nullptr ) {
      v->parent_ = u->parent_;
    }
    return tree;
  }

  Node* TreeDelete(Node* tree, Node* z) {
    if ( z->left_ == nullptr ) {
      tree = Transplant(tree, z, z->right_);
    } else if ( z->right_ == nullptr ) {
      tree = Transplant(tree, z, z->left_);
    } else {
      Node* y = TreeMinimum(z->right_);
      if ( y->parent_ != z ) {
	tree = Transplant(tree, y, y->right_);
	y->right_ = z->right_;
	y->right_->parent_ = y;
      }
      tree = Transplant(tree, z, y);
      y->left_ = z->left_;
      y->left_->parent_ = y;
    }
    delete z;
    return tree;
  }

  void Clear(Node* tree) {
    if ( tree != nullptr ) {
      Clear(tree->left_);
      delete tree;
      Clear(tree->right_);
    }
  }

public:

  Tree() : root_(nullptr) {}
  ~Tree() { Clear(root_); }

  void PreorderTreeWalk() { PreorderTreeWalk(root_); }
  void InorderTreeWalk() { InorderTreeWalk(root_); }
  void PostorderTreeWalk() { PostorderTreeWalk(root_); }
  bool Search(int32_t key) { return TreeSearch(root_, key) != nullptr; }
  int32_t Min() { return TreeMinimum(root_)->key_; }
  int32_t Max() { return TreeMaximum(root_)->key_; }

  int32_t Successor(int32_t key) {
    Node* node = TreeSearch(root_, key);
    if ( node != nullptr ) {
      Node* succ = TreeSuccessor(node);
      if ( succ != nullptr ) {
        return succ->key_;
      }
    }
    return TreeMaximum(root_)->key_;
  }

  void Insert(int32_t key) {
    root_ = TreeInsert(root_, new Node(key));
  }

  void Delete(int32_t key) {
    Node* node = TreeSearch(root_, key);
    if ( node != nullptr ) {
      root_ = TreeDelete(root_, node);
    }
  }
};

#endif // STDALG_BINARYTREE_H_
