#pragma once

#ifndef MAP_AND_SET_SET_H
#define MAP_AND_SET_SET_H

#include "Tree.h"
template<class K>
class Set: public RBTree<K,K>{
public:
    bool empty(){
        return RBTree<K,K>::size();
    }
    void clear(){
        RBTree<K, K>::root = nullptr;
        RBTree<K,K>::min_node = RBTree<K , K>::max_node = nullptr;
        RBTree<K, K>::sz = 0;
    }
    void insert(const K& key){
        K tmp = key;
        RBTree<K, K>::insert(tmp, tmp);
    }
    void erase(const K& key){
        RBTree<K,K>::remove(key);
    }
    size_t size(){
        return RBTree<K, K>::size();
    }
    typename RBTree<K, K>::Iterator find(const K& key){
        return RBTree<K, K>::Iterator(RBTree<K, K>::search(key));
    }



};

#endif //MAP_AND_SET_SET_H
