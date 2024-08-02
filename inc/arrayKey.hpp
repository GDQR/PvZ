#pragma once
#include <iostream>
#include <iterator>
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
  int count(const Key key);
  void clear();
  void erase(const Key& key);
  Type& operator[](const Key& key);
};

template <class Key, class Type>
Type& ArrayKey<Key, Type>::read(const Key key) {
  for (unsigned int i = 0; i < first.size(); i++) {
    if (first[i] == key) {
      return second[i];
    }
  }
  TYRA_ASSERT(!(true == true), "ERROR SEARCHING KEY, KEY NOT FOUNDED:", key);
  return *second.end();
}

template <class Key, class Type>
void ArrayKey<Key, Type>::insert(const Key key, const Type value) {
  first.push_back(key);
  second.push_back(value);
}

template <class Key, class Type>
void ArrayKey<Key, Type>::write(const Key key, const Type value) {
  for (unsigned int i = 0; i < first.size(); i++) {
    if (first[i] == key) {
      second[i] = value;
    }
  }

  TYRA_ASSERT(!(true == true), "ERROR SEARCHING KEY, KEY NOT FOUNDED", key);
}

template <class Key, class Type>
int ArrayKey<Key, Type>::count(const Key key) {
  for (unsigned int i = 0; i < first.size(); i++) {
    if (first[i] == key) {
      return 1;
    }
  }
  return 0;
}

template <class Key, class Type>
Type& ArrayKey<Key, Type>::operator[](const Key& key) {
  for (unsigned int i = 0; i < first.size(); i++) {
    if (first[i] == key) {
      return second[i];
    }
  }
  TYRA_ASSERT(!(true == true), "ERROR SEARCHING KEY, KEY NOT FOUNDED:", key);
  return *second.end();
}

template <class Key, class Type>
void ArrayKey<Key, Type>::clear() {
  first.clear();
  second.clear();
}

template <class Key, class Type>
void ArrayKey<Key, Type>::erase(const Key& key) {
  for (unsigned int i = 0; i < first.size(); i++) {
    if (first[i] == key) {
      first.erase(first.begin() + i);
      second.erase(second.begin() + i);
      break;
    }
  }
}
