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

void bubbleSort(vectoru32 &v) {
  for ( u32 i = 0; i < v.size() - 1; i++ )
    for ( u32 j = v.size() - 1; j != i; j-- )
      if ( v[j - 1] >  v[j] ) {
	u32 tmp = v[j - 1];
	v[j - 1] = v[j];
	v[j] = tmp;
      }
}

void printVector(vectoru32 &v) {
  //  std::cout << "Vector of size " << v.size() << "\n\n";
  for (u32 &val : v)
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
  bubbleSort(v);
  tis = wtime() - tis;

#ifdef DEBUG
  std::cout << "\nSorted vector\n";
  printVector(v);
#endif

  //printf("[insertion sort] Size of vector : %lu. Elapsed time: %.6f sec.\n", v.size(), tis);
  printf("%lu %.6f\n", v.size(), tis);  
  return 0;
}
