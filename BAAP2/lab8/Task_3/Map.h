#pragma once

#ifndef MAP_AND_SET_MAP_H
#define MAP_AND_SET_MAP_H
#include "Tree.h"
template<class K, class V>
class Map : public RBTree<K, V> {
private:
    size_t my_sz = 0;
public:
    V& operator [](const K& key){
        Node<K, V> * ptr = RBTree<K,V>::search(key);

        if(ptr == nullptr){
            //std::cout << "constr\n";
            RBTree<K,V>::insert(key, V());
            ++my_sz;
        }
        Node<K, V> * ptr2 = RBTree<K, V>::search(key);
        return ptr2->my_pair.second;
    }
    V& at(const K& key){
        Node<K, V> * ptr = RBTree<K,V>::search(key);
        if(ptr == nullptr){
            throw std::out_of_range("out of range");
        }
        return ptr->my_pair.second;
    }
    const V& at(const K& key) const {
        Node<K, V> * ptr = RBTree<K,V>::search(key);
        if(ptr == nullptr){
            throw std::out_of_range("out of range");
        }
        return ptr->my_pair.second;

    }
    size_t size(){
        return my_sz;
    }
    bool empty(){
        bool ans;
         my_sz == 0? ans = true : ans = false;
        return ans;
    }
    void clear(){
        RBTree<K, V>::root = nullptr;
        RBTree<K,V>::min_node = RBTree<K , V>::max_node = nullptr;
        RBTree<K, V>::sz = 0;
        my_sz = 0;
    }
    void insert(const std::pair<K,V>& pair){
        RBTree<K, V>::insert(pair.first, pair.second);
        ++my_sz;
    }
    void insert(const K& key, const V& val){
        RBTree<K, V>::insert(key, val);
        ++my_sz;
    }
    void erase(const K& key){
        RBTree<K, V>::remove(key);
        --my_sz;
    }
    class my_iterator : public RBTree<K, V>::Iterator{};
    my_iterator beggin(){
        return my_iterator(RBTree<K,V>::min_node);
    }
    my_iterator endd(){
        return my_iterator(RBTree<K, V>::max_node);
    }


   /* class iterator*//* public RBTree<Key, Val>::Iterator*//*{
    private:
        RBTree<K, V>::Iterator iter;
    public:
        iterator(Node<K, V> * ptr = nullptr) : *//*RBTree<K, Val>::Iterator(ptr), *//*iter(ptr){}
        iterator(RBTree<K, V>::Iterator& it) : *//*RBTree<K, V>::Iterator(it),*//* iter(it){}
        bool operator==(const iterator& other){
            return this->iter == other.iter;
        }
        bool operator != (const iterator& other){
            return this->iter != other.iter;
        }
        iterator& operator ++(){
            ++iter;
            return *this;
        }
        iterator& operator --(){
            --iter;
            return *this;
        }

        V operator * (){
            return *iter;
        }

    };
    iterator mbegin() {
        return iterator(RBTree<K, V>::min_node);
    }
    iterator mend(){
        return iterator(RBTree<K, V>::max_node);
    }*/

};


#endif //MAP_AND_SET_MAP_H
