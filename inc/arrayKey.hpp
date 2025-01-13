#pragma once
#include "entities/entities.hpp"
#include <iostream>
#include <tyra>
#include <vector>
#include <unordered_map>

template <class Key, class Type>
class ArrayKey {
 public:
  ArrayKey(enumComponents typeComponent);
  enumComponents type;
  std::vector<Key> first;
  std::vector<Type> second;
  std::unordered_map<unsigned int, Key> fastKey;
  void insert(const Key key, const Type value);
  int count(const Key key);
  void clear();
  void erase(const Key& key);
  Type& operator[](const Key key);
};

template <class Key, class Type>
ArrayKey<Key, Type>::ArrayKey(enumComponents typeComponent) {
  type = typeComponent;
}

template <class Key, class Type>
void ArrayKey<Key, Type>::insert(const Key key, const Type value) {
  fastKey[key] = first.size();
  first.push_back(key);
  second.push_back(value);
}

template <class Key, class Type>
int ArrayKey<Key, Type>::count(const Key key) {
  for (auto& id : first) {
    if (id == key) {
      return 1;
    }
  }
  return 0;
}

template <class Key, class Type>
Type& ArrayKey<Key, Type>::operator[](const Key entityID) {
  unsigned int pos = fastKey[entityID];
  if (pos >= second.size()) {
    TYRA_ASSERT(!(true == true),
                "ERROR SEARCHING KEY, KEY NOT FOUNDED:", entityID,
                "COMPONENT:", type);
  }
  return second[pos];
}

template <class Key, class Type>
void ArrayKey<Key, Type>::clear() {
  first.clear();
  second.clear();
  fastKey.clear();
}

template <class Key, class Type>
void ArrayKey<Key, Type>::erase(const Key& key) {
  unsigned int size = first.size();
  for (unsigned int i = 0; i < size; i++) {
    if (first[i] == key) {
      first.erase(first.begin() + i);
      second.erase(second.begin() + i);
      fastKey.erase(key);
      size--;
      for(unsigned int j = i; j< size; j++){
        fastKey[first[j]] = j;
      }
      break;
    }
  }
}
