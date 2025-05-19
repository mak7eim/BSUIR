#pragma once

#ifndef MAP_AND_SET_UNORDERED_MAP_H
#define MAP_AND_SET_UNORDERED_MAP_H

#include <memory>
#include <forward_list>
template<class K>
struct h{
    size_t operator()(const K& key, size_t hashtablesize){
        size_t index =abs( ((key ^ 50 + 1337 -   key * key  +  key * key * key   + 13769 ) * 47 / 13) ) % hashtablesize;
        return index;
    }
};

template<class K, class V, class hasher = std::hash<K>>
class unord_map{
    using pair = std::pair<K, V>;
private:
    std::forward_list<pair> ** arr;
    size_t hashtablesize = 16;
    double rehashfactor = 0.75;
    size_t amount = 0;
    hasher hash;
private:
    size_t hashing(hasher& hash, const K& key){
        return hash(key, hashtablesize);
    }
public:
    unord_map(){

        arr = new  std::forward_list<pair> * [hashtablesize];
        for(int i = 0; i < hashtablesize; ++i){
            arr[i] = nullptr;
        }
    }
    explicit unord_map(size_t n){
        arr = new std::forward_list<pair> * [n];
        hashtablesize = n;
        for(int i = 0; i < n; ++i){
            arr[i] = nullptr;
        }
    }
    bool insert(const pair& tmp){
        if(tmp.first > hashtablesize){
            throw std::out_of_range("out of range");
        }
        size_t index = hashing(hash, tmp.first);
        if(!arr[index])
        {
            arr[index] = new std::forward_list<pair>();
            arr[index]->push_front(tmp);
            ++amount;
            rehash();
            return true;
        }
        else
        {
            for(auto it = arr[index]->begin(); it != arr[index]->end(); ++it){
                if(it->first == tmp.first){
                    return false;
                }
            }
            arr[index]->push_front(tmp);
            ++amount;
            rehash();
            return true;
        }
    }
    bool insert(const K& key, const V& val)
    {
        insert(std::make_pair(key, val));
    }

    void rehash()
    {
        if ((static_cast<double>(amount) / static_cast<double>(hashtablesize)) > rehashfactor) {
            std::forward_list<pair> **tmp = new std::forward_list<pair> *[hashtablesize * 2];
            for (int i = 0; i < hashtablesize * 2; ++i) {
                tmp[i] = nullptr;
            }
            size_t n = hashtablesize;
            hashtablesize *= 2;
            for (int i = 0; i < n; ++i) {
                if (arr[i] != nullptr) {
                    for (auto it = arr[i]->begin(); it != arr[i]->end(); ++ it) {
                        size_t new_index = hashing(hash, it->first);
                        if(!tmp[new_index]){
                            tmp[new_index] = new std::forward_list<pair>();
                            tmp[new_index]->push_front(*it);
                        }
                        else{
                            tmp[new_index]->push_front(*it);
                        }
                    }

                }
            }
            for(int i =0; i < n; ++i){
                delete arr[i];
            }
            arr = tmp;
        }
        else
        {
            return;
        }
    }

    V& operator [](const K& key){
        if(key > hashtablesize){
            throw std::out_of_range("out of range");
        }
        size_t index = hashing(hash, key);
        if(!arr[index]){
            arr[index] = new std::forward_list<pair>();
            arr[index]->push_front(std::make_pair(key, V()));
            ++amount;
            return arr[index]->begin()->second;
        }
        else
        {
            for(auto it = arr[index]->begin(); it != arr[index]->end(); ++it){
                if(it->first == key){
                    return it->second;
                }
            }
            arr[index]->push_front(std::make_pair(key, V()));
            ++amount;
            return arr[index]->begin()->second;

        }

    }

    bool contain(const K& key)
    {
        size_t index = hashing(hash, key);
        if(!arr[index]){
            return false;
        }
        else{
            for(auto it = arr[index]->begin(); it != arr[index]->end(); ++it){
                if(it->first == key){
                    return true;
                }
            }
        }
    }

    bool erase(const K& key)
    {
        if(!contain(key)){
            return false;
        }
        else{
            size_t index = hashing(hash, key);
            for(auto it = arr[index]->begin(); it != arr[index]->end(); ++it){
                if(it->first == key){
                    arr[index]->remove(*it);
                    --amount;
                    return true;
                }
            }

        }
    }
    size_t size(){
        return amount;
    }
    void clear(){
        std::forward_list<pair> **tmp = new std::forward_list<pair> *[hashtablesize * 2];
        for (int i = 0; i < hashtablesize; ++i) {
            tmp[i] = nullptr;
        }
        for(int i =0; i < hashtablesize; ++i){
            delete arr[i];
        }
        arr = tmp;
        amount = 0;
    }
};
#endif //MAP_AND_SET_UNORDERED_MAP_H
