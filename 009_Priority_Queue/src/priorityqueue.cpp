#include <iostream>
#include <vector>
//#include <random>
#include <sys/time.h>
#include <stdlib.h>

#define DEBUG

double wtime() {
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

typedef int i32;
typedef unsigned int u32;
typedef std::vector<i32> vectori32;
typedef std::vector<u32> vectoru32;

//std::minstd_rand0 rnd(99);

u32 getrand(u32 min, u32 max) {
    return (double)rand() / (RAND_MAX + 1.0) * (max - min) + min;
}

void generateRandomVector(u32 n, vectoru32 &v) {
  v.resize(n);
  for ( u32 &val : v)
    //val = rnd();
    val = getrand(0, 1001); // [a, b[ = [a , b - 1]
}

void printVector(vectoru32 &v) {
  //  std::cout << "Vector of size " << v.size() << "\n\n";
  for (u32 &val : v)
    std::cout << val << " ";
  std::cout << "\n";
}

typedef struct heap {
  u32 heapsize;
  vectoru32 v;
public:
  inline u32 parent(u32 i) { return (i - 1) >> 1; }; // (i - 1) / 2;
  inline u32 left(u32 i) { return (i << 1) ^ (0x00000001); }; // 2*i + 1
  inline u32 right(u32 i) { return (i << 1) + (u32)2; }; // 2*i + 2;
} Heap;

void maxHeapify(Heap &h, u32 i) {
  u32 largest;
  u32 l = h.left(i);
  u32 r = h.right(i);
  if ( l < h.heapsize && h.v[l] > h.v[i] )
    largest = l;
  else
    largest = i;
  if ( r < h.heapsize && h.v[r] > h.v[largest] )
    largest = r;
  if ( i != largest ) {
    u32 tmp = h.v[i]; // std::swap(h.v[i], h.v[largest]);
    h.v[i] = h.v[largest];
    h.v[largest] = tmp;
    maxHeapify(h, largest);
  }
}

// O(lg(N))
void maxHeapifynr(Heap &h, u32 i) {
  u32 largest = 0;
  u32 l = h.left(i);
  u32 r = h.right(i);
  while ( largest < h.heapsize ) {
    l = h.left(i);
    r = h.right(i);
    if ( l < h.heapsize && h.v[l] > h.v[i] )
      largest = l;
    else
      largest = i;
    if ( r < h.heapsize && h.v[r] > h.v[largest] )
      largest = r;
    if ( largest == i )
      return;
    u32 tmp = h.v[i];
    h.v[i] = h.v[largest];
    h.v[largest] = tmp;
    i = largest;
  }
}

// O(N)
void buildMaxHeap(Heap &h) {
  h.heapsize = h.v.size();
  for ( u32 i = h.v.size() >> 1; i != (u32)-1; i-- ) {
    maxHeapify(h, i);
  }
}

void heapSort(Heap &h) {
  buildMaxHeap(h);
  for ( u32 i = h.v.size() - 1; i !=0; i-- ) {
    std::swap(h.v[0], h.v[i]);
    h.heapsize--;
    maxHeapify(h, 0);
  }
}

u32 heapMaximum(Heap& h) {
  return h.v[0];
}

u32 heapExtractMax(Heap& h) {
  if ( h.v.size() < 1 ) {
    std::cout << "Queue is empty!\n";
    return 0;
  }
  u32 max = h.v[0];
  h.v[0] = h.v[h.heapsize - 1];
  h.heapsize--;
  maxHeapify(h, 0);
  return max;
}

void heapIncreaseKey(Heap& h, u32 i, u32 key) {
  if ( key < h.v[i] ) {
    std::cout << "New key is less then the current!\n";
    return;
  }
  h.v[i] = key;
  while ( i > 0 && h.v[h.parent(i)] < h.v[i] ) {
    std::swap(h.v[i], h.v[h.parent(i)]);
    i = h.parent(i);
  }
}

void maxHeapInsert(Heap& h, u32 key) {
  h.heapsize++;
  h.v[h.heapsize - 1] = 0;
  heapIncreaseKey(h, h.heapsize - 1, key);
}

void maxHeapDelete(Heap& h, u32 i) {
  h.heapsize--;
  h.v[i] = h.v[h.heapsize];
  heapIncreaseKey(h, i, h.v[i]);
  maxHeapify(h, i);
}

int main (int argc, char *argv[]) {

  double tis;
  Heap h;
  h.v.resize(20, 0);
  h.heapsize = 0;

  tis = wtime();
  maxHeapInsert(h, 7);
  maxHeapInsert(h, 8);
  maxHeapInsert(h, 15);
  maxHeapInsert(h, 2);
  maxHeapInsert(h, 13);
  maxHeapInsert(h, 9);
  maxHeapInsert(h, 1);
  maxHeapInsert(h, 12);
  maxHeapInsert(h, 4);
  maxHeapInsert(h, 0);
  maxHeapInsert(h, 5);
  maxHeapInsert(h, 6);


  maxHeapInsert(h, 10);
  tis = wtime() - tis;

#ifdef DEBUG
  std::cout << "\nQueue\n";
  printVector(h.v);
#endif
  printf("%lu %.6f\n", h.v.size(), tis);  
  return 0;
}
