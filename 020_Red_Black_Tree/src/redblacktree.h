#ifndef STDALG_REDBLACKTREE_
#define STDALG_REDBLACKTREE_

#include <iostream>
#include <vector>
#include <functional>

/**
 * Simple Red Black Tree struct with basic operations
 */
template <class Key = int32_t, Key Min = INT32_MIN, Key Max = INT32_MAX,
          class Compare = std::less<Key>>
class RedBlackTree {
private:
  struct Node {
    Key key_;
    Node* parent_ = nullptr;
    Node* left_ = nullptr;
    Node* right_ = nullptr;
    bool red_;
    Node(Key key, Node* parent=nullptr, Node* left=nullptr,
         Node* right=nullptr, bool red=false)
      : key_(key)
      , parent_(parent)
      , left_(left)
      , right_(right)
      , red_(red) {}
    Node(const Node* node)
      : key_(node->key_)
      , parent_(node->parent_)
      , left_(node->left_)
      , right_(node->right_)
      , red_(node->red_) {}
  };

  Node* root_;
  Node* nil_;
  Compare cmp_;
private:

  void InorderTreeWalk(Node* x, std::ostream& os = std::cout) const {
    if ( x != nil_ ) {
      InorderTreeWalk(x->left_);
      os << x->key_ << " ";
      InorderTreeWalk(x->right_);
    }
  }

  Node* TreeSearch(Node* x, const Key& key) const {
    if ( x == nil_ ) return nil_;
    while ( x != nil_ && x->key_ != key ) {/*assignemnt*/
      if ( key < x->key_ ) { /* x->key > q */
        x = x->left_;
      } else {
        x = x->right_;
      }
      if ( x == nil_ ) return nil_;
    }
    return x;
  }

  Node* TreeMinimum(Node* x) const {
    while ( x->left_ != nil_ ) {
      x = x->left_;
    }
    return x;
  }

  Node* TreeMaximum(Node* x) const {
    while ( x->right_ != nil_ ) {
      x = x->right_;
    }
    return x;
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

  Node* TreeInsert(Node* z) {
    Node* y;
    Node* x = new Node(z->key_);
    TreeInsertHelp(x);
    Node* newNode = x;
    x->red_ = true;
    while ( x->parent_->red_ ) {
      if ( x->parent_ == x->parent_->parent_->left_ ) {
        y = x->parent_->parent_->right_;
        if ( y->red_ ) {
          x->parent_->red_= false;
          y->red_ = false;
          x->parent_->parent_->red_=true;
          x = x->parent_->parent_;
        } else {
          if ( x == x->parent_->right_ ) {
            x = x->parent_;
            LeftRotate(x);
          }
          x->parent_->red_ = false;
          x->parent_->parent_->red_ = true;
          RightRotate(x->parent_->parent_);
        }
      } else { /* case for x->parent == x->parent->parent->right */
        y = x->parent_->parent_->left_;
        if ( y->red_ ) {
          x->parent_->red_= false;
          y->red_ = false;
          x->parent_->parent_->red_ = true;
          x = x->parent_->parent_;
        } else {
          if ( x == x->parent_->left_ ) {
            x = x->parent_;
            RightRotate(x);
          }
          x->parent_->red_ = false;
          x->parent_->parent_->red_ = true;
          LeftRotate(x->parent_->parent_);
        }
      }
    }
    root_->left_->red_ = false;
    return newNode;
  }

  Node* GetSuccessorOf(Node* x) const {
    Node* y;

    if ( nil_ != (y = x->right_) ) {
      /* assignment to y is intentional */
      while( y->left_ != nil_ ) {
        /* returns the minium of the right subtree of x */
        y = y->left_;
      }
      return y;
    } else {
      y = x->parent_;
      while( x == y->right_ ) { /* sentinel used instead of checking for nil */
        x = y;
        y = y->parent_;
      }
      if ( y == root_ ) return nil_;
      return y;
    }
  }

  Node* GetPredecessorOf(Node* x) const {
    Node* y;

    if ( nil_ != (y = x->left_) ) { /* assignment to y is intentional */
      while( y->right_ != nil_ ) {
        /* returns the maximum of the left subtree of x */
        y = y->right_;
      }
      return y;
    } else {
      y = x->parent_;
      while( x == y->left_ ) {
        if ( y == root_ ) return nil_;
        x = y;
        y = y->parent_;
      }
      return y;
    }
  }


  void DeleteFixUp(Node* x) {
    Node * w;
    Node * rootLeft = root_->left_;

    while( (!x->red_) && (rootLeft != x) ) {
      if ( x == x->parent_->left_ ) {
        w = x->parent_->right_;
        if ( w->red_ ) {
          w->red_ = false;
          x->parent_->red_ = true;
          LeftRotate(x->parent_);
          w = x->parent_->right_;
        }
        if ( (!w->right_->red_) && (!w->left_->red_) ) {
          w->red_ = true;
          x = x->parent_;
        } else {
          if ( !w->right_->red_ ) {
            w->left_->red_ = false;
            w->red_ = true;
            RightRotate(w);
            w = x->parent_->right_;
          }
          w->red_ = x->parent_->red_;
          x->parent_->red_ = false;
          w->right_->red_ = false;
          LeftRotate(x->parent_);
          x = rootLeft; /* this is to exit while loop */
        }
      } else { /* the code below is has left and right switched from above */
        w = x->parent_->left_;
        if ( w->red_ ) {
          w->red_ = false;
          x->parent_->red_ = true;
          RightRotate(x->parent_);
          w = x->parent_->left_;
        }
        if ( (!w->right_->red_) && (!w->left_->red_) ) {
          w->red_ = true;
          x = x->parent_;
        } else {
          if ( !w->left_->red_ ) {
            w->right_->red_ = false;
            w->red_ = true;
            LeftRotate(w);
            w = x->parent_->left_;
          }
          w->red_ = x->parent_->red_;
          x->parent_->red_ = false;
          w->left_->red_ = false;
          RightRotate(x->parent_);
          x = rootLeft; /* this is to exit while loop */
        }
      }
    }
    x->red_ = false;
  }

  void TreeDelete(Node* z) {
    Node* y;
    Node* x;
    // Node* returnValue = z->storedEntry;

    y = ((z->left_ == nil_) || (z->right_ == nil_)) ? z : GetSuccessorOf(z);
    x = (y->left_ == nil_) ? y->right_ : y->left_;
    if ( root_ == (x->parent_ = y->parent_) ) {
      /* assignment of y->p to x->p is intentional */
      root_->left_ = x;
    } else {
      if ( y == y->parent_->left_ ) {
        y->parent_->left_ = x;
      } else {
        y->parent_->right_ = x;
      }
    }
    if ( y != z ) { /* y should not be nil in this case */
      /* y is the node to splice out and x is its child */
      y->left_ = z->left_;
      y->right_ = z->right_;
      y->parent_ = z->parent_;
      z->left_->parent_ = z->right_->parent_ = y;
      if ( z == z->parent_->left_ ) {
        z->parent_->left_ = y;
      } else {
        z->parent_->right_ = y;
      }
      if ( !(y->red_) ) {
        y->red_ = z->red_;
        DeleteFixUp(x);
      } else {
        y->red_ = z->red_;
      }
      delete z;
    } else {
      if ( !(y->red_)) DeleteFixUp(x);
      delete y;
    }
  }

public:

  RedBlackTree()
      : cmp_(Compare()) {
    nil_ = new Node(Min, nullptr, nullptr, nullptr, false);
    nil_->parent_ = nil_->left_ = nil_->right_ = nil_;
    root_ = new Node(Max, nil_, nil_, nil_, false);
  }

  ~RedBlackTree() {
    Node* x = root_->left_;
    std::vector<Node*> stuffToFree;

    if ( x != nil_ ) {
      if ( x->left_ != nil_ ) {
        stuffToFree.push_back(x->left_);
      }
      if ( x->right_ != nil_ ) {
        stuffToFree.push_back(x->right_);
      }
      // delete x->storedEntry;
      delete x;
      while ( !stuffToFree.empty() ) {
        x = stuffToFree.back();
        stuffToFree.pop_back();
        if ( x->left_ != nil_ ) {
          stuffToFree.push_back(x->left_);
        }
        if ( x->right_ != nil_ ) {
          stuffToFree.push_back(x->right_);
        }
        // delete x->storedEntry;
        delete x;
      }
    }

    delete nil_;
    delete root_;
  }

  void InorderTreeWalk(std::ostream& os = std::cout) const {
    InorderTreeWalk(root_->left_, os);
  }
  Key Search(const Key& key) const {
    Node* node = TreeSearch(root_->left_, key);
    return node != nil_ ? node->key_ : Key();
  }

  void Insert(const Key& key) {
    TreeInsert(new Node(key));
  }

  void Delete(const Key& key) {
    Node* node = TreeSearch(root_, key);
    if ( node != nil_ ) {
      TreeDelete(node);
    }
  }
};

#endif // STDALG_REDBLACKTREE_
