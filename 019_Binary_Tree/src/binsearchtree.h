#include <iostream>

/**
 * Simple Binary Tree struct with basic operations
 */
template <class Key = int32_t>
class Tree {
private:
  struct Node {
    Key key_;
    Node* parent_ = nullptr;
    Node* left_ = nullptr;
    Node* right_ = nullptr;
    Node(Key key)
      : key_(key)
      , parent_(nullptr)
      , left_(nullptr)
      , right_(nullptr) {}
    Node(const Node* node)
      : key_(node->key_)
      , parent_(node->parent_)
      , left_(node->left_)
      , right_(node->right_) {}

    // ~Node() { delete left_; delete right_; std::cout << "destr node\n";}
  };

  Node* root_;
private:

  void PreorderTreeWalk(Node* x, std::ostream& os = std::cout) const {
    if ( x != nullptr ) {
      os << x->key_ << " ";
      PreorderTreeWalk(x->left_);
      PreorderTreeWalk(x->right_);
    }
  }

  void InorderTreeWalk(Node* x, std::ostream& os = std::cout) const {
    if ( x != nullptr ) {
      InorderTreeWalk(x->left_);
      os << x->key_ << " ";
      InorderTreeWalk(x->right_);
    }
  }

  void PostorderTreeWalk(Node* x, std::ostream& os = std::cout) const {
    if ( x != nullptr ) {
      PostorderTreeWalk(x->left_);
      PostorderTreeWalk(x->right_);
      os << x->key_ << " ";
    }
  }

  Node* TreeSearch(Node* x, const Key& key, bool recurcive = false) const {
    if ( recurcive ) {
      if ( x == nullptr || key == x->key_ ) {
        return x;
      }
      if ( key < x->key_ ) {
        return TreeSearch(x->left_, key, recurcive);
      } else {
        return TreeSearch(x->right_, key, recurcive);
      }
    } else {
      while ( x != nullptr && x->key_ != key ) {
        if ( key < x->key_ ) {
          x = x->left_;
        } else {
          x = x->right_;
        }
      }
      return x;
    }
  }

  Node* TreeMinimum(Node* x) const {
    while ( x->left_ != nullptr ) {
      x = x->left_;
    }
    return x;
  }

  Node* TreeMaximum(Node* x) const {
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

  void clear(Node* tree) {
    if ( tree != nullptr ) {
      clear(tree->left_);
      clear(tree->right_);
      delete tree;
    }
  }

public:

  Tree() : root_(nullptr) {}
  ~Tree() { /*delete root_;*/ clear(root_); std::cout << "destr bst\n";}

  void PreorderTreeWalk(std::ostream& os = std::cout) const {
    PreorderTreeWalk(root_, os);
  }
  void InorderTreeWalk(std::ostream& os = std::cout) const {
    InorderTreeWalk(root_, os);
  }
  void PostorderTreeWalk(std::ostream& os = std::cout) const {
    PostorderTreeWalk(root_, os);
  }
  Key Search(const Key& key) const {
    Node* node = TreeSearch(root_, key);
    return node != nullptr ? node->key_ : Key();
  }
  Key Min() const { return TreeMinimum(root_)->key_; }
  Key Max() const { return TreeMaximum(root_)->key_; }

  Key Successor(Key key) {
    Node* node = TreeSearch(root_, key);
    if ( node != nullptr ) {
      Node* succ = TreeSuccessor(node);
      if ( succ != nullptr ) {
        return succ->key_;
      }
    }
    return TreeMaximum(root_)->key_;
  }

  void Insert(const Key& key) {
    root_ = TreeInsert(root_, new Node(key));
  }

  void Delete(const Key &key) {
    Node* node = TreeSearch(root_, key);
    if ( node != nullptr ) {
      root_ = TreeDelete(root_, node);
    }
  }

  friend std::ostream& operator<<(std::ostream& os, const Tree<Key>& tree) {
    tree.InorderTreeWalk(os);
    return os;
  }
};
