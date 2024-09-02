#pragma once
#include <iostream>
#include <vector>
#include <tyra>

template <class Key, class Type>
class LinearArrayKey {
 public:
  std::vector<Key> first;
  std::vector<Type> second;
  Type& read(const Key key);
  void insert(const Key key, const Type value);
  void write(const Key key, const Type value);
  int count(const Key key);
  int getIndex(const Key key);
  void clear();
  void erase(const Key& key);
  Type& operator[](const Key key);
};

template <class Key, class Type>
Type& LinearArrayKey<Key, Type>::read(const Key key) {
  for (unsigned int i = 0; i < first.size(); i++) {
    if (first[i] == key) {
      return second[i];
    }
  }
  TYRA_ASSERT(!(true == true), "ERROR SEARCHING KEY, KEY NOT FOUNDED:", key);
  return *second.end();
}

template <class Key, class Type>
void LinearArrayKey<Key, Type>::insert(const Key key, const Type value) {
  first.push_back(key);
  second.push_back(value);
}

template <class Key, class Type>
void LinearArrayKey<Key, Type>::write(const Key key, const Type value) {
  for (unsigned int i = 0; i < first.size(); i++) {
    if (first[i] == key) {
      second[i] = value;
    }
  }

  TYRA_ASSERT(!(true == true), "ERROR SEARCHING KEY, KEY NOT FOUNDED:", key);
}

template <class Key, class Type>
int LinearArrayKey<Key, Type>::count(const Key key) {
  for (unsigned int i = 0; i < first.size(); i++) {
    if (first[i] == key) {
      return 1;
    }
  }
  return 0;
}

template <class Key, class Type>
int LinearArrayKey<Key, Type>::getIndex(const Key key){
  for (unsigned int i = 0; i < first.size(); i++) {
    if (first[i] == key) {
      return i;
    }
  }
  return -1;
}

template <class Key, class Type>
Type& LinearArrayKey<Key, Type>::operator[](const Key key) {
  for (unsigned int i = 0; i < first.size(); i++) {
    if (first[i] == key) {
      return second[i];
    }
  }

  return *second.end();
}

template <class Key, class Type>
void LinearArrayKey<Key, Type>::clear() {
  first.clear();
  second.clear();
}

template <class Key, class Type>
void LinearArrayKey<Key, Type>::erase(const Key& key) {
  unsigned int index;
  for (unsigned int i = 0; i < first.size(); i++) {
    if (first[i] == key) {
      index = i;
      first.erase(first.begin() + index);
      second.erase(second.begin() + index);
      break;
    }
  }
}
