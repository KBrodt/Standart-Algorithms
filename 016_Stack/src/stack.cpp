#include <iostream>
#include <vector>

using i32 = int;
using u32 = unsigned;
using vectori32 = std::vector<i32>;
using vectoru32 = std::vector<u32>;

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

  bool empty() const { if ( top_ == -1 ) return true; return false; }
  bool full() const { if ( top_ + 1 == static_cast<i32>(capacity_) ) return true; return false; }

  void resize(const u32 news_ize) {
    Type* old_data = new Type[this->size()];
    for ( u32 i = 0; i < this->size(); ++i )
      old_data[i] = s_[i];
    delete [] s_;
    capacity_ = news_ize;
    s_ = new Type[capacity_];
    for ( u32 i = 0; i < this->size(); ++i )
      s_[i] = old_data[i];
    delete [] old_data;
    std::cout << "resized\n";
  }
  void push(const Type& val) {
    if ( this->full() ) {
      this->resize(2*capacity_);
    }
    s_[++top_] = val;
  }
  Type pop() {
    if ( empty() ) throw("Stack is empty");
    if ( this->size() <= capacity_ >> 2 )
      this->resize(capacity_ >> 1);
    return s_[top_--];
  }
  i32 top() const { return top_; }

  u32 size() const { return top_+1; }
  u32 capacity() const { return capacity_; }

  void print() const {
    for ( u32 i = 0; i <= static_cast<u32>(top_); i++ ) {
      std::cout << s_[i] << " ";
    }
    std::cout << "\n";
  }
};

i32 main(i32 argc, char* argv[]) {
  Stack<double> s;
  s.push(15);
  s.push(6);
  s.push(2);
  s.push(9);
  std::cout << s.top() << "\n";
  s.print();
  s.push(17);
  s.push(3);
  s.push(3);
  s.push(3);
  s.push(3);
  //  s.push(3);
  std::cout << s.top() << "\n";
  s.print();
  s.pop();  s.pop();  s.pop();  s.pop();  s.pop();  s.pop();  s.pop();
  std::cout << "CAP: " << s.capacity() << "\n";
  i32 a = s.pop();
  std::cout << "CAP: " << s.capacity() << "\n";
  std::cout << a << "\n" << s.top() << "\n";
  s.print();
  return 0;
}
