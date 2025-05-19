#pragma once

#ifndef MAP_AND_SET_RBTREE_H
#define MAP_AND_SET_RBTREE_H

#include <memory>

using namespace std;

template <class T, class T1>
struct Node
{
    Node(T nKey, T1 nValue);

    Node();

    shared_ptr<Node> left;
    shared_ptr<Node> right;
    weak_ptr<Node> parent;

    bool color;

    T key;
    T1 data;
};

template <class T, class T1>
class RBT
{
public:
    RBT();

    ~RBT();

    void add(T key, T1 value);

    void remove(T key);

    T1 findValueWithKey(T key);

    bool contains(T key);

    T1 &operator[](T key);

    void clear();

    class iterator;

protected:
    struct Node;

    shared_ptr<Node> grandparent(shared_ptr<Node> node);

    shared_ptr<Node> uncle(shared_ptr<Node> node);

    shared_ptr<Node> sibling(shared_ptr<Node> node);

    void RotateLeft(shared_ptr<Node> node);

    void RotateRight(shared_ptr<Node> node);

    void InsCase1(shared_ptr<Node> node);

    void InsCase2(shared_ptr<Node> node);

    void InsCase3(shared_ptr<Node> node);

    void InsCase4(shared_ptr<Node> node);

    void InsCase5(shared_ptr<Node> node);

    void DelCase1(shared_ptr<Node> node);

    void DelCase2(shared_ptr<Node> node);

    void DelCase3(shared_ptr<Node> node);

    void DelCase4(shared_ptr<Node> node);

    void DelCase5(shared_ptr<Node> node);

    void DelCase6(shared_ptr<Node> node);

    shared_ptr<Node> find(shared_ptr<Node> node, T key);

    shared_ptr<Node> min(shared_ptr<Node> node);

    shared_ptr<Node> max(shared_ptr<Node> node);

    shared_ptr<Node> next(shared_ptr<Node> node);

    shared_ptr<Node> prev(shared_ptr<Node> node);

protected:
    shared_ptr<Node> root;
};

template <class T, class T1>
class iterator
{
public:
    iterator(shared_ptr<Node<T, T1>> node, RBT<T, T1> *own);
    iterator(const iterator &it);
    bool operator!=(iterator const &other) const;
    bool operator==(iterator const &other) const;
    T1 &operator*() const;
    iterator &operator++()
    {
        iter = owner->next(iter);
        return *this;
    }
    iterator &operator--()
    {
        iter = owner->prev(iter);
        return *this;
    }

private:
    shared_ptr<Node<T, T1>> iter;
    RBT<T, T1> *owner;
};

template <class T, class T1>
shared_ptr<typename RBT<T, T1>::Node> RBT<T, T1>::next(shared_ptr<Node> node)
{
    shared_ptr<Node> tmp = node->right;
    if (tmp)
    {
        while (tmp->left)
            tmp = tmp->left;
        return tmp;
    }
    tmp = node;
    while (tmp->parent && tmp.equals(tmp->parent.lock()->right))
        tmp = tmp->parent;

    return tmp->parent.lock();
}

#endif // MAP_AND_SET_RBTREE_H
