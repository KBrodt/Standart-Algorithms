#include <iostream>
#include <vector>

using i32 = int;
using u32 = unsigned;
using vectori32 = std::vector<i32>;
using vectoru32 = std::vector<u32>;

class Stacki32{
private:
  i32* _s;
  u32 _capacity;
  i32 _top;
public:
  Stacki32(const u32 capacity) :
    _s(new i32[capacity]),
    _capacity(capacity),
    _top(-1) {}
  ~Stacki32() { delete [] _s; }
  bool empty() { if ( _top == -1 ) return true; return false; }
  bool full() { if ( _top + 1 == _capacity ) return true; return false; }
  void push(const i32 val) { _s[++_top] = val; }
  i32 pop() { if ( empty() ) return 777; return _s[_top--]; }
  i32 top() { return _top; }
  u32 capacity() { return _capacity; }
  void print() { for ( u32 i = 0; i <= _top; i++ ) std::cout << _s[i] << " "; std::cout << "\n"; }
};

i32 main(i32 argc, char* argv[]) {
  Stacki32 s(7);
  s.push(15);
  s.push(6);
  s.push(2);
  s.push(9);
  std::cout << s.top() << "\n";
  s.print();
  s.push(17);
  s.push(3);
  std::cout << s.top() << "\n";
  s.print();
  i32 a = s.pop();
  std::cout << a << "\n" << s.top() << "\n";
  s.print();
  return 0;
}
