#include <iostream>
#include <vector>
#include <set>
//#include <chrono>
#include <random>     // better pseudo-random
#include <sys/time.h>
#include <stdlib.h> // rand
#include <limits>

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

// std::minstd_rand0 rnd(1);
//std::default_random_engine generator/*(seed)*/;
//std::uniform_int_distribution<u32> distribution(0, 100);

u32 getrand(u32 min, u32 max) {
  return (double)rand() / (RAND_MAX + 1.0) * (max - min) + min;
  //u32 seed = std::chrono::system_clock::now().time_since_epoch().count();
  //std::default_random_engine lgenerator(seed);
  //std::uniform_int_distribution<u32> ldistribution(min, max);
  //return ldistribution(lgenerator);
}

void generateRandomVector(u32 n, vectori32 &v) {
  v.resize(n);
  for ( auto &val : v)
    //val = rnd();
    val = getrand(-n, n);
   //val = distribution(generator);
}

void printVector(vectori32 &v) {
  for ( u32 i = 0; i < v.size(); i++ )
    std::cout << v[i] << " ";
  std::cout << std::endl;
}

u32 randomSearch(vectori32 &v, i32 trg) {
  std::set<u32> indexes;
  while ( indexes.size() != v.size() ) {
    srand(wtime());
    u32 i = getrand(0, v.size());
    if ( v[i] == trg )
      return i;
    else
      indexes.insert(i);
  }
  return v.size();
}

int main (int argc, char *argv[]) {

  double tis;
  u32 size = atoi(argv[1]);
  vectori32 v;
  generateRandomVector(size, v);
  i32 trg = getrand(-v.size(), v.size());

#ifdef DEBUG
  std::cout << "Initial array\n";
  printVector(v);
  std::cout << "Target value : " << trg << std::endl;
#endif

  tis = wtime();
  u32 index = randomSearch(v, trg);
  tis = wtime() - tis;

#ifdef DEBUG
  std::cout << "\nIndex : " << index << std::endl;
#endif
  printf("%lu %.6f\n", v.size(), tis);
  return 0;
}
