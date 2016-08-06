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

typedef int i32;
typedef unsigned int u32;
typedef std::vector<i32> vectori32;
typedef std::vector<u32> vectoru32;

//std::minstd_rand0 rnd(99);

// get pseudo-random number in [min, max[
u32 getrand(u32 min, u32 max) {
    return (double)rand() / (RAND_MAX + 1.0) * (max - min) + min;
}

void generateRandomVector(u32 n, vectoru32 &v) {
  v.resize(n);
  for ( u32 &val : v)
    //val = rnd();
    val = getrand(0, n + 1); // [a, b[ = [a, b - 1]
}

void printVector(vectoru32 &v) {
  //  std::cout << "Vector of size " << v.size() << "\n\n";
  for (u32 &val : v)
    std::cout << val << " ";
  std::cout << "\n";
}

void countingSort(vectoru32& v) {
  vectoru32 c(v.size() + 1, 0);
  for ( u32 i = 0; i < v.size(); i++ )
    c[v[i]]++;
  for ( u32 i = 1; i < c.size(); i++ )
    c[i] = c[i] + c[i - 1];
  vectoru32 b(v.size());
  for ( u32 i = v.size() - 1; i != (u32)-1; i-- ) {
    b[c[v[i]] - 1] = v[i]; // - 1 ?
    c[v[i]]--;
  }
  for ( u32 i = 0; i < v.size(); i++ ) {
    v[i] = b[i];
  }
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
  countingSort(v);
  tis = wtime() - tis;

#ifdef DEBUG
  std::cout << "\nSorted vector\n";
  printVector(v);
#endif
  printf("%lu %.6f\n", v.size(), tis);  
  return 0;
}
