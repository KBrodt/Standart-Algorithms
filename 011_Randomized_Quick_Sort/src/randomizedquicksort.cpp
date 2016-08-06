#include <iostream>
#include <vector>
#include <random>
#include <sys/time.h>
#include <stdlib.h>

#define DEBUG

double wtime() {
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

typedef unsigned int u32;
typedef std::vector<u32> vectoru32;

//std::minstd_rand0 rnd(99);
//u32 seed = std::chrono::system_clock::now().time_since_epoch().count();
//std::default_random_engine generator(seed);
//std::uniform_int_distribution<u32> distribution(0, 1000);

u32 getrand(u32 min, u32 max) {
    return (double)rand() / (RAND_MAX + 1.0) * (max - min) + min;
}

void generateRandomVector(u32 n, vectoru32 &v) {
  v.resize(n);
  for ( u32 &val : v)
    //val = rnd();
    val = getrand(1, 1001); //[a, b[
  //val = distribution(generator);
}

void printVector(vectoru32 &v) {
  //  std::cout << "Vector of size " << v.size() << "\n\n";
  for (u32 &val : v)
    std::cout << val << " ";
  std::cout << "\n";
}

u32 partition(vectoru32& v, u32 p, u32 r) {
  u32 pivot = v[r];
  u32 i = p - 1;
  for ( u32 j = p; j < r; j++ ) {
    if ( v[j] <= pivot ) {
      i++;
      u32 tmp = v[j];
      v[j] = v[i];
      v[i] = tmp;
    }
  }
  i++;
  v[r] = v[i];
  v[i] = pivot;
  return i;
}

u32 randomizedPartition(vectoru32& v, u32 p, u32 r){
  //srand(wtime());
  u32 i = getrand(p, r + 1);
  //srand(wtime());
  //u32 j = getrand(p, r + 1);
  //srand(wtime());
  //u32 k = getrand(p, r + 1);
  //u32 median = (i + j + k)/3;
  u32 tmp = v[i];
  v[i] = v[r];
  v[r] = tmp;
  return partition(v, p, r);
}

void randomizedQuickSort(vectoru32& v, u32 p, u32 r) {
  if ( p < r ) {
    u32 q = randomizedPartition(v, p, r);
    if (q != 0)
      randomizedQuickSort(v, p, q - 1);
    randomizedQuickSort(v, q + 1, r);
  }
}

int main (int argc, char *argv[]) {

  double tis;
  u32 size = atoi(argv[1]);
  vectoru32 v;
  //srand(wtime());
  generateRandomVector(size, v);

#ifdef DEBUG
  std::cout << "Unsorted vector\n";
  printVector(v);
#endif

  tis = wtime();
  randomizedQuickSort(v, 0, v.size() - 1);
  tis = wtime() - tis;

#ifdef DEBUG
  std::cout << "\nSorted vector\n";
  printVector(v);
#endif

  printf("%lu %.6f\n", v.size(), tis);  
  return 0;
}
