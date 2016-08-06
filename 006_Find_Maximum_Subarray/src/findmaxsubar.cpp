#include <iostream>
#include <vector>
//#include <chrono>
#include <random>     // better pseudo-random
#include <sys/time.h>
#include <stdlib.h>
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

//std::minstd_rand0 rnd(1);
//u32 seed = std::chrono::system_clock::now().time_since_epoch().count();
std::default_random_engine generator/*(seed)*/;
std::uniform_int_distribution<i32> distribution(-100,100);

u32 getrand(i32 min, i32 max) {
    return (double)rand() / (RAND_MAX + 1.0) * (max - min) + min;
}

void generateRandomVector(u32 n, vectori32 &v) {
  v.resize(n);
  for ( i32 &val : v)
    //  val = rnd();
  //val = getrand(-201, 101);
    val = distribution(generator);
}

void printVector(vectori32 &v) {
  for ( u32 i = 0; i < v.size(); i++ )
    std::cout << v[i] << " ";
  std::cout << std::endl;
}

typedef struct {
  u32 low;
  u32 high;
  i32 sum;
} array;

// "brut force" O(N^2)
array findMaximumSubArray(vectori32 &v) {
  array res = {0, 0, std::numeric_limits<i32>::min()};
  i32 sum;
  for ( u32 i = 0; i < v.size(); i++ ) {
    sum = 0;
    for ( u32 j = i; j < v.size(); j++ ) {
      sum += v[j];
      if ( sum > res.sum ) {
	res.sum = sum;
	res.low = i;
	res.high = j;
      }
    }
  }
  return res;
}

// Recursive version O(N*lgN)
array findMaxCrossingSubArray(vectori32 &v, u32 low, u32 mid, u32 high) {

  array res = {mid + 1, mid, 0};
  i32 leftsum = std::numeric_limits<i32>::min();
  i32 sum = 0;

  for ( u32 i = mid; i != low - 1; i--) {
    sum += v[i];
    if ( sum > leftsum ) {
      leftsum = sum;
      res.low = i;
    }
  }

  i32 rightsum = std::numeric_limits<i32>::min();
  sum = 0;
  for ( u32 j = mid + 1; j <= high; j++ ) {
    sum += v[j];
    if ( sum > rightsum ) {
      rightsum = sum;
      res.high = j;
    }
  }

  res.sum = leftsum + rightsum;
  if ( res.sum < 0 ) {
    res.low = mid;
    res.high = mid;
    res.sum = 0;
    return res;
  } else
    return res;
}

array findMaximumSubArrayRec(vectori32 &v, u32 low, u32 high) {

  if ( low == high ) {
    array res = {low, high, v[low]};
    if ( v[low] < 0 ) {
      res = {low, high, 0};
      return res;
    } else
      return res;
  }
  else {
    u32 mid = low + (( high - low ) >> 1);
    array left = findMaximumSubArrayRec(v, low, mid);
    array right = findMaximumSubArrayRec(v, mid + 1, high);
    array cross = findMaxCrossingSubArray(v, low, mid, high);
    if ( left.sum >= right.sum && left.sum >= cross.sum )
      return left;
    else if ( right.sum >= left.sum && right.sum >= cross.sum )
      return right;
    else
      return cross;
  }
}

// O(N)
array findMaximumSubArrayLin(vectori32 &v) {
  u32 maxi = 0;
  u32 i = 0;
  u32 maxj = 0;
  i32 maxsum = std::numeric_limits<i32>::min();
  i32 newsum;
  i32 sum = 0;
  bool ft = true;
  for ( u32 k = 0; k < v.size(); k++ ) {
    sum += v[k];
    if ( sum > maxsum ) {
      maxj = k;
      maxsum = sum;
    }
    if ( v[k] > 0 ) {
      if ( ft ) {
	ft= false;
	i = k;
      }
      newsum += v[k];
    } else {
      ft = true;
      i = 0;
      newsum = 0;
    }
    if ( newsum > maxsum ) {
      maxi = i;
      maxj = k;
      maxsum = newsum;
    }
  }
  array res = {maxi, maxj, maxsum};
  return res;
}

int main (int argc, char *argv[]) {

  double tis;
  u32 size = atoi(argv[1]);
  vectori32 v;
  generateRandomVector(size, v);

#ifdef DEBUG
  std::cout << "Array\n";
  printVector(v);
#endif

  array res;
  tis = wtime();
  //res = findMaximumSubArray(v);
  //res = findMaximumSubArrayRec(v, 0, v.size() - 1);
  res = findMaximumSubArrayLin(v);
  tis = wtime() - tis;

#ifdef DEBUG
  std::cout << "\nMaximum subarray\n";
  printf("Low %u, high %u and sum %d\n", res.low, res.high, res.sum);
#endif
  //printf("[insertion sort] Size of vector : %lu. Elapsed time: %.6f sec.\n", v.size(), tis);
  printf("%lu %.6f\n", v.size(), tis);  
  return 0;
}
