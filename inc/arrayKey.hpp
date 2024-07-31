#pragma once
// #include <iostream>
#include <vector>
#include <tyra>

template <class Key, class Type>
class ArrayKey {
 public:
  std::vector<Key> first;
  std::vector<Type> second;
  Type& read(const Key key);
  void insert(const Key key, const Type value);
  void write(const Key key, const Type value);
};

template <class Key, class Type>
Type& ArrayKey<Key, Type>::read(const Key key) {
  int index = -1;
  for (unsigned int i = 0; i < first.size(); i++) {
    if (first[i] == key) {
      index = i;
    }
  }
  TYRA_ASSERT(index != -1, "ERROR SEARCHING KEY, KEY NOT FOUNDED:", key);
  return second[index];
}

template <class Key, class Type>
void ArrayKey<Key, Type>::insert(const Key key, const Type value) {
  first.push_back(key);
  second.push_back(value);
  // std::cout << "key: " << key << " value: " << value << std::endl;
  // std::cout << "value ptr: " << &second[0] << std::endl;
}

template <class Key, class Type>
void ArrayKey<Key, Type>::write(const Key key, const Type value) {
  int index = -1;
  for (unsigned int i = 0; i < first.size(); i++) {
    if (first[i] == key) {
      index = i;
    }
  }

  TYRA_ASSERT(index != -1, "ERROR SEARCHING KEY, KEY NOT FOUNDED", key);
  second[index] = value;
}