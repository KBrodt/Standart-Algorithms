#include <iostream>
#include <vector>
//#include <random>
#include <sys/time.h>
#include <stdlib.h>

//#define DEBUG


double wtime() {
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

typedef unsigned int u32;
typedef std::vector<u32> vectoru32;

//std::minstd_rand0 rnd(99);

u32 getrand(u32 min, u32 max) {
    return (double)rand() / (RAND_MAX + 1.0) * (max - min) + min;
}

void generateRandomVector(u32 n, vectoru32 &v) {
  v.resize(n);
  for ( u32 &val : v)
    //val = rnd();
    val = getrand(1, 1001);
}

void insertionSort(vectoru32 &v) {
  for ( u32 j = 1; j < v.size(); j++ ) {
    // Put v[j] into sorted array v[0..j - 1]
    u32 key = v[j];
    u32 i = j - 1;
    while ( i != (u32)-1 && v[i] > key ) {
      v[i + 1] = v[i];
      i--;
    }
    v[i + 1] = key;
  }
}

void put(u32 key, vectoru32 &v, u32 n) {
    u32 i = n - 1;
	while ( i != (u32)-1 && v[i] > key ) {
      v[i + 1] = v[i];
      i--;
    }
	v[i + 1] = key;
}

void insertionSortRec(vectoru32 &v, u32 n) {
  if ( n > 1 ) {
    insertionSortRec(v, n - 1);
    // Put v[n] into sorted array v[0..n - 1]
    u32 key = v[n - 1];
    put(key, v, n - 1);
  }
}

void printVector(vectoru32 &v) {
  //  std::cout << "Vector of size " << v.size() << "\n\n";
  for ( u32 &val : v )
    std::cout << val << " ";
  std::cout << "\n";
}

int main (int argc, char *argv[]) {

  double tis;
  u32 size = atoi(argv[1]);
  vectoru32 v;
  generateRandomVector(size, v);
  
#ifdef DEBUG
  std::cout << "Unsorted vector\n";
  printVector(v);
#endif

  tis = wtime();
  insertionSort(v);
  //insertionSortRec(v, v.size());
  tis = wtime() - tis;

#ifdef DEBUG
  std::cout << "\nSorted vector\n";
  printVector(v);
#endif

  //printf("[insertion sort] Size of vector : %lu. Elapsed time: %.6f sec.\n", v.size(), tis);
  printf("%lu %.6f\n", v.size(), tis);  
  return 0;
}
