#pragma once

#ifndef MAP_AND_SET_TREE_H
#define MAP_AND_SET_TREE_H

#include <iostream>
#include <cstddef>
#include <memory>
#include <list>

template <typename KeyType, typename ValueType>
struct Node {
    std::pair<KeyType, ValueType> my_pair;

    bool color;
    Node* parent;
    Node* left;
    Node* right;
    Node(Node * pt) : my_pair(pt->my_pair), color(pt->color), parent(pt->parent), left(pt->left), right(pt->right){}
    Node(const KeyType& key, const ValueType& value, bool isRed, Node* parent, Node* left, Node* right) :
            my_pair(key, value), color(isRed), parent(parent), left(left), right(right) {}
};
template<class K, class V>
class Map;
template<class K>
class Set;
template <typename Key, typename Val>
class RBTree {

    friend class Map<Key, Val>;
    friend class Set<Key>;
    using node_ptr = Node<Key, Val>*;
    std::list<node_ptr> my_list;
public:
    std::list<node_ptr> get_list(){
        return my_list;
    }

private:
    void make_list(){
        my_list.clear();
        for(auto it = this->begin(); it != this->end(); ++it){
            this->my_list.push_back(it.get_node());
        }

    }

    node_ptr root;

    size_t sz;

    node_ptr min_node;

    node_ptr max_node;

private:
    node_ptr get_parent(node_ptr node);
    node_ptr get_uncle(node_ptr node);
    node_ptr get_grand_parent(node_ptr node);

    void left_rotate(node_ptr node);
    void right_rotate(node_ptr node);
    void swap_colors(node_ptr node);

    void inner_fix(node_ptr node);
    void inner_search(node_ptr &root, node_ptr node);

    node_ptr inner_search(node_ptr node, const Key key);

    node_ptr successor(node_ptr node);
    void remove_fix(node_ptr node);
    void inner_remove(node_ptr node);

    node_ptr find_min_node(node_ptr);
    node_ptr find_max_node(node_ptr);
    void min_max_nodes(node_ptr);

public:
    class Iterator {
    private:
        node_ptr ptr;

    public:
        node_ptr get_node(){
            return ptr;
        }
        Iterator(node_ptr ptr = nullptr) : ptr(ptr) {}
        Iterator(Iterator& it) : ptr(it.ptr){}
        bool operator==(const Iterator&);
        bool operator!=(const Iterator&);
        Iterator& operator++();
        Iterator operator++(int);
        Iterator& operator--();
        Iterator operator--(int);
        Val operator*();
    };

public:
    RBTree() : root(nullptr), min_node(nullptr), max_node(nullptr) {}
    void insert(const Key& key, const Val& value);
    node_ptr search(const Key& key);
    void remove(const Key& key);
    Iterator begin();
    Iterator end();
    size_t size();
};

template <typename KeyType, typename ValueType>
void RBTree<KeyType, ValueType>::insert(const KeyType& key, const ValueType& value){
    auto deletedNode = search(key);
    if(deletedNode){
        return;
    }
    auto node = new Node<KeyType, ValueType>(key, value, true, nullptr, nullptr, nullptr);
    inner_search(root, node);
    ++sz;
    min_max_nodes(root);
}

template <typename KeyType, typename ValueType>
typename RBTree<KeyType, ValueType>::node_ptr RBTree<KeyType, ValueType>::search(const KeyType& key) {
    return inner_search(root, key);

}

template <typename KeyType, typename ValueType>
void RBTree<KeyType, ValueType>::remove(const KeyType& key) {
    auto deletedNode = search(key);

    if (deletedNode) {
        inner_remove(deletedNode);
        --sz;
    }

    min_max_nodes(root);
}

template<typename KeyType, typename ValueType>
typename RBTree<KeyType, ValueType>::Iterator RBTree<KeyType, ValueType>::begin() {
    return Iterator(min_node);
}

template<typename KeyType, typename ValueType>
typename RBTree<KeyType, ValueType>::Iterator RBTree<KeyType, ValueType>::end() {
    return Iterator(nullptr);
}

template<typename KeyType, typename ValueType>
size_t RBTree<KeyType, ValueType>::size() {
    return sz;
}



template <typename KeyType, typename ValueType>
bool RBTree<KeyType, ValueType>::Iterator::operator==(const Iterator& other) {
    return ptr == other.ptr;
}

template <typename KeyType, typename ValueType>
bool RBTree<KeyType, ValueType>::Iterator::operator!=(const Iterator& other) {
    return !(*this == other);
}

template <typename KeyType, typename ValueType>
typename RBTree<KeyType, ValueType>::Iterator& RBTree<KeyType, ValueType>::Iterator::operator++() {
    if (ptr) {
        if (ptr->right) {
            ptr = ptr->right;

            while (ptr->left)
                ptr = ptr->left;

        } else {
            node_ptr parent = ptr->parent;

            while (parent && ptr == parent->right) {
                ptr = parent;
                parent = parent->parent;
            }

            ptr = parent;
        }
    }

    return *this;
}

template <typename KeyType, typename ValueType>
typename RBTree<KeyType, ValueType>::Iterator RBTree<KeyType, ValueType>::Iterator::operator++(int) {
    Iterator temp = *this;
    ++(*this);
    return temp;
}

template <typename KeyType, typename ValueType>
typename RBTree<KeyType, ValueType>::Iterator& RBTree<KeyType, ValueType>::Iterator::operator--() {
    if (ptr) {
        if (ptr->left) {
            ptr = ptr->left;

            while (ptr->right)
                ptr = ptr->right;

        } else {
            node_ptr parent = ptr->parent;

            while (parent && ptr == parent->left) {
                ptr = parent;
                parent = parent->parent;
            }

            ptr = parent;
        }
    }

    return *this;
}

template <typename KeyType, typename ValueType>
typename RBTree<KeyType, ValueType>::Iterator RBTree<KeyType, ValueType>::Iterator::operator--(int) {
    Iterator temp = *this;
    --(*this);
    return temp;
}

template<typename KeyType, typename ValueType>
ValueType RBTree<KeyType, ValueType>::Iterator::operator*() {
    return ptr->my_pair.second;
}

/*------/Iterator------*/



template <typename KeyType, typename ValueType>
typename RBTree<KeyType, ValueType>::node_ptr RBTree<KeyType, ValueType>::get_parent(node_ptr node) {
    if (node && node->parent)
        return node->parent;

    return nullptr;
}

template <typename KeyType, typename ValueType>
typename RBTree<KeyType, ValueType>::node_ptr RBTree<KeyType, ValueType>::get_uncle(node_ptr node) {
    node_ptr parent = get_parent(node);
    node_ptr grandParent = get_grand_parent(node);
    if (!grandParent)
        return nullptr;

    return grandParent->left == parent ? grandParent->right : grandParent->left;
}

template <typename KeyType, typename ValueType>
typename RBTree<KeyType, ValueType>::node_ptr RBTree<KeyType, ValueType>::get_grand_parent(node_ptr node) {
    if (node && node->parent && node->parent->parent)
        return node->parent->parent;

    return nullptr;
}

template <typename KeyType, typename ValueType>
void RBTree<KeyType, ValueType>::left_rotate(node_ptr node) {
    if (!node)
        return;

    node_ptr left = node->left;
    node_ptr parent = get_parent(node);
    node_ptr grandParent = get_grand_parent(node);

    if (!parent)
        return;

    if (!grandParent)
        root = node;

    node->parent = grandParent;
    node->left = parent;
    parent->parent = node;
    parent->right = left;

    if (grandParent)
        grandParent->right = node;

    if (left)
        left->parent = parent;
}

template <typename KeyType, typename ValueType>
void RBTree<KeyType, ValueType>::swap_colors(node_ptr node) {
    if (!node)
        return;

    node->color = !node->color;
    if (node == root)
        node->color = false;

    if (node->left)
        node->left->color = !node->left->color;

    if (node->right)
        node->right->color = !node->right->color;
}

template <typename KeyType, typename ValueType>
void RBTree<KeyType, ValueType>::right_rotate(node_ptr node) {
    if (!node)
        return;

    node_ptr right = node->right;
    node_ptr parent = get_parent(node);
    node_ptr grandParent = get_grand_parent(node);

    if (!parent)
        return;

    if (!grandParent)
        root = node;

    node->parent = grandParent;
    node->right = parent;
    parent->parent = node;
    parent->left = right;

    if (grandParent)
        grandParent->left = node;

    if (right)
        right->parent = parent;
}

template <typename KeyType, typename ValueType>
void RBTree<KeyType, ValueType>::inner_fix(node_ptr node) {
    make_list();
    node_ptr parent = get_parent(node);
    node_ptr grandParent = get_grand_parent(node);

    if (!parent || !grandParent) {
        if (!parent)
            node->color = false;

        return;
    }

    node_ptr uncle = get_uncle(node);

    if (!parent->color) {
        return;
    }
    else {
        if (grandParent->left == node->parent) {
            if (!uncle || !uncle->color) {
                if (parent->right == node) {
                    left_rotate(node);
                    swap_colors(node);
                }
                right_rotate(parent);
                parent->color = !parent->color;
                grandParent->color = !grandParent->color;
            } else {
                swap_colors(grandParent);
                if (grandParent->color && get_parent(grandParent) && get_parent(grandParent)->color)
                    inner_fix(grandParent);
            }
        } else {
            if (!uncle || !uncle->color) {
                if (parent->left == node) {
                    right_rotate(node);
                    swap_colors(node);
                }
                left_rotate(parent);
                parent->color = !parent->color;
                grandParent->color = !grandParent->color;
            } else {
                swap_colors(grandParent);
                if (grandParent->color && get_parent(grandParent) && get_parent(grandParent)->color)
                    inner_fix(grandParent);
            }
        }
    }
}

template <typename KeyType, typename ValueType>
void RBTree<KeyType, ValueType>::inner_search(node_ptr& root, node_ptr node) {
    node_ptr x = root;
    node_ptr y = nullptr;

    while (x) {
        y = x;
        x = x->my_pair.first > node->my_pair.first ? x->left : x->right;
    }

    node->parent = y;

    if (y) {
        if (y->my_pair.first > node->my_pair.first)
            y->left = node;
        else
            y->right = node;
    } else {
        root = node;
    }

    inner_fix(node);
}

template <typename KeyType, typename ValueType>
typename RBTree<KeyType, ValueType>::node_ptr RBTree<KeyType, ValueType>::inner_search(node_ptr node, const KeyType key) {
    if (!node || node->my_pair.first == key)
        return node;

    return node->my_pair.first > key ? inner_search(node->left, key) : inner_search(node->right, key);
}

template <typename KeyType, typename ValueType>
typename RBTree<KeyType, ValueType>::node_ptr RBTree<KeyType, ValueType>::successor(node_ptr node) {
    if (!node)
        return nullptr;

    if (node->right) {
        node = node->right;
        while (node->left)
            node = node->left;
        return node;
    }

    node_ptr parent = node->parent;

    while (parent && node == parent->right) {
        node = parent;
        parent = parent->parent;
    }

    return parent;
}

template <typename KeyType, typename ValueType>
void RBTree<KeyType, ValueType>::remove_fix(node_ptr node) {
    if (!node)
        return;

    while (node != root && !node->color) {
        node_ptr sibling = nullptr;
        if (node == node->parent->left) {

            sibling = node->parent->right;

            if (sibling->color) {

                sibling->color = false;
                node->parent->color = true;
                left_rotate(node->parent);
                sibling = node->parent->right;
            }

            if (!sibling->left->color && !sibling->right->color) {

                sibling->color = true;
                node = node->parent;
            } else {
                if (!sibling->right->color) {

                    sibling->left->color = false;
                    sibling->color = true;
                    right_rotate(sibling);
                    sibling = node->parent->right;
                }


                sibling->color = node->parent->color;
                node->parent->color = false;
                sibling->right->color = false;
                left_rotate(node->parent);
                node = root;
            }
        } else {

            sibling = node->parent->left;

            if (sibling->color) {
                sibling->color = false;
                node->parent->color = true;
                right_rotate(node->parent);
                sibling = node->parent->left;
            }

            if (!sibling->left->color && !sibling->right->color) {
                sibling->color = true;
                node = node->parent;
            } else {
                if (!sibling->left->color) {
                    sibling->right->color = false;
                    sibling->color = true;
                    left_rotate(sibling);
                    sibling = node->parent->left;
                }

                sibling->color = node->parent->color;
                node->parent->color = false;
                sibling->left->color = false;
                right_rotate(node->parent);
                node = root;
            }
        }
    }

    if (node)
        node->color = false;
}


template <typename KeyType, typename ValueType>
void RBTree<KeyType, ValueType>::inner_remove(node_ptr node) {

    if (!node)
        return;

    if (!node->left || !node->right) {

        node_ptr child = node->left ? node->left : node->right;
        if (child)
            child->parent = node->parent;

        if (!node->parent) {
            root = child;
        } else if (node == node->parent->left) {

            node->parent->left = child;
        } else {

            node->parent->right = child;
        }

        if (!node->color)
            remove_fix(child);

        delete node;
    } else {

        node_ptr s = successor(node);
        node->my_pair = s->my_pair;
        inner_remove(s);
    }
}

template<typename KeyType, typename ValueType>
typename RBTree<KeyType, ValueType>::node_ptr RBTree<KeyType, ValueType>::find_min_node(node_ptr node) {
    if (!node)
        return nullptr;
    while (node->left)
        node = node->left;
    return node;
}

template<typename KeyType, typename ValueType>
typename RBTree<KeyType, ValueType>::node_ptr RBTree<KeyType, ValueType>::find_max_node(node_ptr node) {
    if (!node)
        return nullptr;
    while (node->right)
        node = node->right;
    return node;
}

template<typename KeyType, typename ValueType>
void RBTree<KeyType, ValueType>::min_max_nodes(node_ptr) {
    min_node = find_min_node(root);
    max_node = find_max_node(root);
    make_list();
}
/*template<class K,class V>
 class my{
    private:
        std::shared_ptr iter;
    public:
        my(Node<K, V> * ptr = nullptr) : RBTree<K, V>::Iterator(ptr), iter(ptr){}
        my(RBTree<K, V>::Iterator& it) : RBTree<K, V>::Iterator(it), iter(it){}
        bool operator==(const my& other){
            return this->iter == other.iter;
        }
        bool operator != (const my& other){
            return this->iter != other.iter;
        }
        my& operator ++(){
            ++iter;
            return *this;
        }
        my& operator --(){
            --iter;
            return *this;
        }

        V operator * (){
            return *iter;
        }

    };
    template<class K, class V>
    my<K, V> mbegin() {
        return iterator(RBTree<K, V>::min_node);
    }
    template<class K, class V>
    my<K, V> mend(){
        return iterator(RBTree<K, V>::max_node);
    }*/

#endif //MAP_AND_SET_TREE_H
