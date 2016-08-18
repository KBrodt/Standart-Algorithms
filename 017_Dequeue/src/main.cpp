#include "dequeue.h"

i32 main() {
  Dequeue<> dequeue;
  std::cout << dequeue.empty() << "\n";
  std::cout << dequeue.full() << "\n";
  dequeue.push_back(1); std::cout << dequeue << "s: " << dequeue.size() << "\n";
  dequeue.push_back(2); std::cout << dequeue << "s: " << dequeue.size() << "\n";
  dequeue.push_back(3); std::cout << dequeue << "s: " << dequeue.size() << "\n";
  dequeue.push_back(4); std::cout << dequeue << "s: " << dequeue.size() << "\n";
  dequeue.pop_back(); std::cout << dequeue << "s: " << dequeue.size() << "\n";
  dequeue.pop_front(); std::cout << dequeue << "s: " << dequeue.size() << "\n";
  dequeue.pop_front(); std::cout << dequeue << "s: " << dequeue.size() << "\n";
  std::cout << dequeue.empty() << "\n";
  std::cout << dequeue.full() << "\n";
  dequeue.push_back(5); std::cout << dequeue << "s: " << dequeue.size() << "\n";
  dequeue.push_back(6); std::cout << dequeue << "s: " << dequeue.size() << "\n";
  dequeue.push_back(7); std::cout << dequeue << "s: " << dequeue.size() << "\n";
  dequeue.push_back(8); std::cout << dequeue << "s: " << dequeue.size() << "\n";
  dequeue.push_back(9); std::cout << dequeue << "s: " << dequeue.size() << "\n";
  dequeue.push_back(10); std::cout << dequeue << "s: " << dequeue.size() << "\n";
  dequeue.push_back(100); std::cout << dequeue << "s: " << dequeue.size() << "\n";
  std::cout << dequeue.empty() << "\n";
  std::cout << dequeue.full() << "\n";
  return 0;
}
