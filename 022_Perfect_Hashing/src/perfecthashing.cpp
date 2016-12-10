#include <iostream>
#include <vector>
#include <cstdint>
#include <random>
#include <functional>

// Key must be some integer type
template <class Key = int32_t>
class HashFunction {
 private:
  Key a_, b_;
  Key p_, m_;

 public:
  HashFunction(Key a = 0, Key b = 0, Key p = 0, Key m = 0)
      : a_(a)
      , b_(b)
      , p_(p)
      , m_(m) {}

  template <class RandomGenerator>
  static HashFunction generate(RandomGenerator& generator, Key p, Key m) {
    std::uniform_int_distribution<Key> die_for_a(1, p - 1);
    std::uniform_int_distribution<Key> die_for_b(0, p - 1);
    return HashFunction(die_for_a(generator), die_for_b(generator), p, m);
  }

  Key operator()(Key key) const {
    Key tmp = (int64_t(a_) * key + b_) % p_;
    return tmp >= 0 ? tmp % m_ : (tmp + p_) % m_;
  }
};

template <class RandomGenerator, class Key = int32_t, Key EmptyKey = INT32_MAX,
          class Hash = HashFunction<Key>, class KeyEqual = std::equal_to<Key>,
          int32_t prime = 2000000011>
class FixedSet {
 private:
  struct HashTable {
    Hash inner_hf_;
    std::vector<Key> values_;
    std::vector<Key> keys_;
  };

  Hash outer_hf_;
  std::vector<HashTable> hash_tables_;
  KeyEqual equal_to_;

 private:
  const int32_t MEMORY_LIMIT_MULTIPLIER = 4;
  RandomGenerator generator_;

  void InitializeFirstLevel(const std::vector<Key>& numbers);
  void InitializeSecondLevel();
  void discardCollisions(HashTable& hash_table);
  int64_t static sqr(int32_t value) { return int64_t(value) * value; }

 public:
  explicit FixedSet(RandomGenerator& generator)
      : outer_hf_(Hash())
      , equal_to_(KeyEqual())
      , generator_(generator) {}

  void Initialize(const std::vector<Key>& numbers);

  bool Contains(const Key& number) const;
};

template <class RandomGenerator, class Key, Key EmptyKey,
          class Hash, class KeyEqual, int32_t prime>
void FixedSet<RandomGenerator, Key, EmptyKey, Hash, KeyEqual,
              prime>::InitializeFirstLevel(
    const std::vector<Key>& numbers) {
  int32_t size = static_cast<int32_t>(numbers.size());

  int64_t hash_tables_size = 0;
  do {
    hash_tables_.assign(size, HashTable());
    outer_hf_ = Hash::generate(generator_, prime, size);
    for (const auto& key : numbers) {
      hash_tables_[outer_hf_(key)].values_.push_back(key);
    }

    hash_tables_size = 0;
    for (const auto& hash_table : hash_tables_) {
      hash_tables_size += sqr(hash_table.values_.size());
    }
  } while (hash_tables_size > MEMORY_LIMIT_MULTIPLIER * size);
}

template <class RandomGenerator, class Key, Key EmptyKey,
          class Hash, class KeyEqual, int32_t prime>
void FixedSet<RandomGenerator, Key, EmptyKey, Hash, KeyEqual,
              prime>::discardCollisions(
    HashTable& hash_table) {
  bool collisions = false;
  do {
    hash_table.keys_.assign(sqr(hash_table.values_.size()), EmptyKey);
    hash_table.inner_hf_ =
        Hash::generate(generator_, prime, hash_table.keys_.size());

    collisions = false;
    for (const auto& key : hash_table.values_) {
      Key hash_code = hash_table.inner_hf_(key);
      if ( equal_to_(hash_table.keys_[hash_code], EmptyKey) ) {
        hash_table.keys_[hash_code] = key;
      } else if ( !equal_to_(hash_table.keys_[hash_code], key) ) {
        collisions = true;
      }
    }
  } while (collisions);
}

template <class RandomGenerator, class Key, Key EmptyKey,
          class Hash, class KeyEqual, int32_t prime>
void FixedSet<RandomGenerator, Key, EmptyKey, Hash, KeyEqual,
              prime>::InitializeSecondLevel() {
  for (auto& hash_table : hash_tables_) {
    discardCollisions(hash_table);
  }
}

template <class RandomGenerator, class Key, Key EmptyKey,
          class Hash, class KeyEqual, int32_t prime>
void FixedSet<RandomGenerator, Key, EmptyKey, Hash, KeyEqual,
              prime>::Initialize(
    const std::vector<Key>& numbers) {
  InitializeFirstLevel(numbers);
  InitializeSecondLevel();
}

template <class RandomGenerator, class Key, Key EmptyKey,
          class Hash, class KeyEqual, int32_t prime>
bool FixedSet<RandomGenerator, Key, EmptyKey, Hash, KeyEqual, prime>::Contains(
    const Key& number) const {
  Key hash_code = outer_hf_(number);
  const auto& cell = hash_tables_[hash_code];
  if ( cell.keys_.empty() ) return false;
  Key secondary_hash_code = cell.inner_hf_(number);
  Key key = cell.keys_[secondary_hash_code];
  return equal_to_(key, number);
}

std::vector<int32_t> readInput() {
  int32_t size;
  std::cin >> size;
  std::vector<int32_t> sequence(size);
  for (int32_t index = 0; index < size; ++index) {
    std::cin >> sequence[index];
  }
  return sequence;
}

int main() {
  // need when iostream input/output data is over 100000 element
  std::ios_base::sync_with_stdio(false);

  std::vector<int32_t> numbers = readInput();
  std::vector<int32_t> queries = readInput();

  std::minstd_rand0 generator;
  FixedSet<std::minstd_rand0> fixed_set(generator);
  fixed_set.Initialize(numbers);
  for (const auto& query : queries) {
    fixed_set.Contains(query) ? std::cout << "\nYes" : std::cout << "\nNo";
  }

  return 0;
}
