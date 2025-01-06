#pragma once
#include "entities/entities.hpp"
#include <iostream>
#include <tyra>
#include <vector>


template <class Key, class Type>
class ArrayKey {
 public:
  ArrayKey(enumComponents typeComponent);
  enumComponents type;
  std::vector<Key> first;
  std::vector<Type> second;
  Type& read(const Key key);
  void insert(const Key key, const Type value);
  void write(const Key key, const Type value);
  int count(const unsigned int& entityID);
  int countSafe(const Key key);
  void clear();
  void erase(const Key& key);
  Type& operator[](const unsigned int& entityID);
};

template <class Key, class Type>
ArrayKey<Key, Type>::ArrayKey(enumComponents typeComponent) {
  type = typeComponent;
}

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
  Entities::addComponent(key, type, first.size());
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

  TYRA_ASSERT(!(true == true), "ERROR SEARCHING KEY, KEY NOT FOUNDED:", key,
              "COMPONENT:", type);
}

template <class Key, class Type>
int ArrayKey<Key, Type>::countSafe(const Key key) {
  for (unsigned int i = 0; i < first.size(); i++) {
    if (first[i] == key) {
      return 1;
    }
  }
  return 0;
}

template <class Key, class Type>
int ArrayKey<Key, Type>::count(const unsigned int& entityID) {
  return Entities::componentIndex[entityID].count(type);
}

template <class Key, class Type>
Type& ArrayKey<Key, Type>::operator[](const unsigned int& entityID) {
  // for (unsigned int i = 0; i < first.size(); i++) {
  //   if (first[i] == key) {
  //     return second[i];
  //   }
  // }
  unsigned int pos = Entities::componentIndex[entityID][type];
  if (pos >= second.size()) {
    TYRA_ASSERT(!(true == true),
                "ERROR SEARCHING KEY, KEY NOT FOUNDED:", entityID,
                "COMPONENT:", type);
  }

  return second[pos];
}

template <class Key, class Type>
void ArrayKey<Key, Type>::clear() {
  Entities::clearComponent(type);
  first.clear();
  second.clear();
}

template <class Key, class Type>
void ArrayKey<Key, Type>::erase(const Key& key) {
  unsigned int index = first.size();
  for (unsigned int i = 0; i < first.size(); i++) {
    if (first[i] == key) {
      index = i;
      first.erase(first.begin() + index);
      second.erase(second.begin() + index);
      Entities::removeComponent(key, type);
      break;
    }
  }

  for (unsigned int i = index; i < first.size(); i++) {
    Entities::componentIndex[first[i]][type]--;
  }
}
