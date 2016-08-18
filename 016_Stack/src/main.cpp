#include "stack.h"

i32 main(i32 argc, char* argv[]) {
  Stack<> s{-1, -2, -3};
  std::cout << s << "\n";
  s.push(15);
  s.push(6);
  s.push(2);
  s.push(9);
  std::cout << s.top() << "\n";
  std::cout << s << "\n";
  s.push(17);
  s.push(3);
  s.push(3);
  s.push(3);
  s.push(3);
  //  s.push(3);
  std::cout << s.top() << "\n";
  std::cout << s << "\n";
  s.pop();  s.pop();  s.pop();  s.pop();  s.pop();  s.pop();  s.pop();
  std::cout << "CAP: " << s.capacity() << "\n";
  i32 a = s.pop();
  std::cout << "CAP: " << s.capacity() << "\n";
  std::cout << a << "\n" << s.top() << "\n";
  std::cout << s << "\n";
  return 0;
}
