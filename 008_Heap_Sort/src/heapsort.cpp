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
    val = getrand(1, 1001); // ]a, b[ = [a + 1, b - 1]
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

void buildMaxHeap(Heap &h) {
  h.heapsize = h.v.size();
  for ( u32 i = h.v.size() >> 1; i != (u32)-1; i-- ) {
    maxHeapify(h, i);
  }
}

void heapSort(Heap &h) {
  buildMaxHeap(h);
  for ( u32 i = h.v.size() - 1; i !=0; i-- ) {
    u32 tmp = h.v[0]; // std::swap(h.v[0], h.v[i]);
    h.v[0] = h.v[i];
    h.v[i] = tmp;
    h.heapsize--;
    maxHeapify(h, 0);
  }
}

int main (int argc, char *argv[]) {

  double tis;
  u32 size = atoi(argv[1]);
  //vectoru32 v;
  Heap h;
  generateRandomVector(size, h.v);

#ifdef DEBUG
  std::cout << "Unsorted vector\n";
  printVector(h.v);
#endif

  tis = wtime();
  heapSort(h);
  tis = wtime() - tis;

#ifdef DEBUG
  //printf("\nIndex %u (%u) : parent %u (%u), left %u (%u), right %u (%u)\n", i, h.v[i], p, h.v[p], l, h.v[l], r, h.v[r]);
  std::cout << "\nSorted vector\n";
  printVector(h.v);
#endif
  printf("%lu %.6f\n", h.v.size(), tis);  
  return 0;
}
