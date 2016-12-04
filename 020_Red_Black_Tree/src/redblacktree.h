#ifndef STDALG_REDBLACKTREE_
#define STDALG_REDBLACKTREE_

#include <iostream>
#include <functional>

const bool RED = false;
const bool BLACK = true;

/**
 * Simple Red Black Tree struct with basic operations
 */
template <class Key, class Compare = std::less<Key>>
class RedBlackTree {
private:
  struct Node {
    Key key_;
    Node* parent_ = nullptr;
    Node* left_ = nullptr;
    Node* right_ = nullptr;
    bool color_;
    Node(Key key, Node* parent=nullptr, Node* left=nullptr,
         Node* right=nullptr, bool color=BLACK)
      : key_(key)
      , parent_(parent)
      , left_(left)
      , right_(right)
      , color_(color) { std::cout << "default ctor with key\n"; }
    Node(const Node* node)
      : key_(node->key_)
      , parent_(node->parent_)
      , left_(node->left_)
      , right_(node->right_)
      , color_(node->color_) { std::cout << "copy ctor\n"; }
  };

  Node* root_;
  Node* nil_;
  Compare cmp_;
private:

  void InorderTreeWalk(Node* x) {
    if ( x != nullptr ) {
      InorderTreeWalk(x->left_);
      std::cout << x->key_ << " ";
      InorderTreeWalk(x->right_);
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

  void LeftRotate(Node* x) {
    Node* y = x->right_;
    x->right_ = y->left_;

    if ( y->left_ != nil_ ) {
      y->left_->parent_ = x;
    }
    y->parent_ = x->parent_;
    if ( x == x->parent_->left_ ) {
      x->parent_->left_ = y;
    } else {
      x->parent_->right_ = y;
    }
    y->left_ = x;
    x->parent_ = y;
  }

  void RightRotate(Node* y) {
    Node* x = y->left_;
    y->left_ = x->right_;

    if ( x->right_ != nil_ ) {
      x->right_->parent_ = y;
    }
    x->parent_ = y->parent_;
    if ( y == y->parent_->left_ ) {
      y->parent_->left_ = x;
    } else {
      y->parent_->right_ = x;
    }
    x->right_ = y;
    y->parent_ = x;
  }

  void TreeInsertHelp(Node* z) {
    Node* x;
    Node* y;

    z->left_ = z->right_ = nil_;
    y = root_;
    x = root_->left_;
    while ( x != nil_ ) {
      y = x;
      if ( cmp_(z->key_, x->key_) ) {
        x = x->left_;
      } else {
        x = x->right_;
      }
    }
    z->parent_ = y;
    if ( (y == root_) ||
         cmp_(z->key_, y->key_)) {
      y->left_ = z;
    } else {
      y->right_ = z;
    }
  }

  Node* RBInsert(Node* z) {
    Node* y;
    Node* x = new Node(z->key_);
    TreeInsertHelp(x);
    Node* newNode = x;
    x->color_ = RED;
    while ( x->parent_->color_ == RED ) {
      if ( x->parent_ == x->parent_->parent_->left_ ) {
        y=x->parent_->parent_->right_;
        if (y->color_ == RED) {
          x->parent_->color_= BLACK;
          y->color_ = BLACK;
          x->parent_->parent_->color_=RED;
          x=x->parent_->parent_;
        } else {
          if (x == x->parent_->right_) {
            x=x->parent_;
            LeftRotate(x);
          }
          x->parent_->color_ = BLACK;
          x->parent_->parent_->color_ = RED;
          RightRotate(x->parent_->parent_);
        }
      } else { /* case for x->parent == x->parent->parent->right */
        y = x->parent_->parent_->left_;
        if (y->color_ == RED) {
          x->parent_->color_= BLACK;
          y->color_ = BLACK;
          x->parent_->parent_->color_ = RED;
          x = x->parent_->parent_;
        } else {
          if ( x == x->parent_->left_ ) {
            x = x->parent_;
            RightRotate(x);
          }
          x->parent_->color_ = BLACK;
          x->parent_->parent_->color_ = RED;
          LeftRotate(x->parent_->parent_);
        }
      }
    }
    root_->left_->color_ = BLACK;
    return newNode;
  }

  void Clear(Node* tree) {
    if ( tree != nullptr ) {
      Clear(tree->left_);
      delete tree;
      Clear(tree->right_);
    }
  }

public:

  RedBlackTree()
      : cmp_(Compare())
        //, nil_(new Node(0, nil_, nil_, nil_, BLACK))
        //, root_(new Node(0, nil_, nil_, nil_, BLACK)) {
  {
    std::cout << "pizda";
    nil_ = new Node(0, nullptr, nullptr, nullptr, BLACK);
    nil_->parent_ = nil_->left_ = nil_->right_ = nil_;
    root_ = new Node(0, nil_, nil_, nil_, BLACK);
  }

  // ~RedBlackTree() { Clear(root_); }
  bool empty();
  int32_t size();

  void InorderTreeWalk() { InorderTreeWalk(root_); }
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
    RBInsert(new Node(key));
  }

  void Delete(int32_t key) {
    Node* node = TreeSearch(root_, key);
    if ( node != nullptr ) {
      root_ = TreeDelete(root_, node);
    }
  }
};

#endif // STDALG_REDBLACKTREE_
