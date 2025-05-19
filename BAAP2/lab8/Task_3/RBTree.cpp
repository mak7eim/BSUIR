#pragma once

#include "RBTree.h"
template<class T, class T1>
shared_ptr<typename RBT<T, T1>::Node> RBT<T, T1>::grandparent(shared_ptr<Node> node) {
    shared_ptr<Node> p = node->parent;
    if (p && p->parent) {
        return p->parent;
    } else {
        return shared_ptr<Node>();
    }
}

template<class T, class T1>
shared_ptr<typename RBT<T, T1>::Node> RBT<T, T1>::uncle(shared_ptr<Node> node) {
    shared_ptr<Node> tmp = grandparent(node);

    if (tmp) {
        if (tmp->left.equals(node->parent)) {
            return tmp->right;
        } else {
            return tmp->left;
        }
    } else {
        return shared_ptr<Node>();
    }
}

template<class T, class T1>
void RBT<T, T1>::RotateLeft(shared_ptr<Node> node) {
    shared_ptr<Node> right = node->right;

    right->parent = node->parent;
    if (node->parent) {
        shared_ptr<Node> p = node->parent;

        if (p->left.equals(node)) {
            p->left = right;
        } else {
            p->right = right;
        }
    } else {
        root = right;
    }

    node->right = right->left;
    if (right->left) {
        right->left->parent = node;
    }

    node->parent = right;
    right->left = node;
}

template<class T, class T1>
void RBT<T, T1>::RotateRight(shared_ptr<Node> node) {
    shared_ptr<Node> left = node->left;

    left->parent = node->parent;
    if (node->parent) {
        shared_ptr<Node> p = node->parent;

        if (p->left.equals(node)) {
            p->left = left;
        } else {
            p->right = left;
        }
    } else {
        root = left;
    }

    node->left = left->right;
    if (left->right) {
        left->right->parent = node;
    }

    node->parent = left;
    left->right = node;
}

template<class T, class T1>
void RBT<T, T1>::add(T key, T1 value) {
    shared_ptr<Node> tmp = root, p = shared_ptr<Node>();

    while (tmp) {
        p = tmp;

        if (tmp->key > key) {
            tmp = tmp->left;
        } else if (tmp->key < key) {
            tmp = tmp->right;
        } else {
            return;
        }
    }

    tmp = shared_ptr<Node>(new Node(key, value));
    tmp->parent = p;

    if (p) {
        if (tmp->key > p->key) {
            p->right = tmp;
        } else {
            p->left = tmp;
        }
    } else {
        root = tmp;
    }

    InsCase1(tmp);
    return;
}

template<class T, class T1>
void RBT<T, T1>::InsCase1(shared_ptr<Node> node) {
    if (!node->parent) {
        node->color = 1;
    }
    else {
        InsCase2(node);
    }
}

template<class T, class T1>
void RBT<T, T1>::InsCase2(shared_ptr<Node> node) {
    if (node->parent.lock()->color) {
        return;
    } else {
        InsCase3(node);
    }
}

template<class T, class T1>
void RBT<T, T1>::InsCase3(shared_ptr<Node> node) {
    shared_ptr<Node> u = uncle(node);

    if (u && !u->color) {
        node->parent.lock()->color = 1;
        u->color = 1;
        shared_ptr<Node> g = grandparent(node);
        g->color = 0;
        InsCase1(g);
    } else {
        InsCase4(node);
    }
}

template<class T, class T1>
void RBT<T, T1>::InsCase4(shared_ptr<Node> node) {
    shared_ptr<Node> g = grandparent(node), tmp = node;
    shared_ptr<Node> p = node->parent;
    if (node.equals(p->right) && p.equals(g->left)) {
        RotateLeft(p);
        tmp = node->left;
    } else if (node.equals(p->left) && p.equals(g->right)) {
        RotateRight(p);
        tmp = node->right;
    }

    InsCase5(tmp);
}

template<class T, class T1>
void RBT<T, T1>::InsCase5(shared_ptr<Node> node) {
    shared_ptr<Node> g = grandparent(node);
    shared_ptr<Node> p = node->parent;
    p->color = 1;
    g->color = 0;

    if (node.equals(p->left)) {
        RotateRight(g);
    } else {
        RotateLeft(g);
    }
}

template<class T, class T1>
shared_ptr<typename RBT<T, T1>::Node> RBT<T, T1>::sibling(shared_ptr<Node> node) {
    if (!node->parent) {
        return shared_ptr<Node>();
    }

    shared_ptr<Node> p = node->parent;

    if (node.equals(p->left)) {
        return p->right;
    } else {
        return p->left;
    }
}

template<class T, class T1>
void RBT<T, T1>::remove(T key) {
    shared_ptr<Node> tmp = root ? find(root, key) : shared_ptr<Node>();
    if (!tmp) {
        return;
    }


    if (!tmp->parent && !tmp->left && !tmp->right) {
        root = shared_ptr<Node>();
        return;
    }


    if (tmp->left && tmp->right)  {
        shared_ptr<Node> removed = tmp->left;
        while (removed->right) {
            removed = removed->right;
        }
        tmp->data = removed->data;
        tmp->key = removed->key;
        tmp = removed;
    }
    shared_ptr<Node> child = tmp->left ? tmp->left : tmp->right;

    if (!child) {
        if (tmp->color) {
            DelCase1(tmp);
        }
        shared_ptr<Node> p = tmp->parent;

        if (p->left.equals(tmp)) {
            p->left = child;
        } else {
            p->right = child;
        }
    }

    else {
        child->parent = tmp->parent;
        shared_ptr<Node> p = tmp->parent;


        if (tmp->parent) {
            if (tmp.equals(p->left)) {
                p->left = child;
            } else {
                p->right = child;
            }
        } else {
            root = child;
            if (tmp->color) {
                if (!child->color) {
                    child->color = 1;
                } else {
                    DelCase1(child);
                }
            }
        }
    }
}

template<class T, class T1>
void RBT<T, T1>::DelCase1(shared_ptr<Node> node) {
    if (node->parent) {
        DelCase2(node);
    }
}

template<class T, class T1>
void RBT<T, T1>::DelCase2(shared_ptr<Node> node) {
    shared_ptr<Node> s = sibling(node);
    shared_ptr<Node> p = node->parent;
    bool scol = s ? s->color : 1;

    if (!scol) {
        p->color = 0;
        s->color = 1;

        if (node.equals(p->left)) {
            RotateLeft(p);
        } else {
            RotateRight(p);
        }
    }

    DelCase3(node);
}

template<class T, class T1>
void RBT<T, T1>::DelCase3(shared_ptr<Node> node) {
    shared_ptr<Node> s = sibling(node);
    shared_ptr<Node> p = node->parent;

    bool scol = s ? s->color : 1;
    bool lcol = s && s->left ? s->left->color : 1;
    bool rcol = s && s->right ? s->right->color : 1;

    if (p->color && scol && lcol && rcol) {
        if (s) {
            s->color = 0;
        }
        DelCase1(p);
    } else {
        DelCase4(node);
    }
}

template<class T, class T1>
void RBT<T, T1>::DelCase4(shared_ptr<Node> node) {
    shared_ptr<Node> s = sibling(node);
    shared_ptr<Node> p = node->parent;

    bool scol = s ? s->color : 1;
    bool lcol = s && s->left ? s->left->color : 1;
    bool rcol = s && s->right ? s->right->color : 1;

    if (!p->color && scol && lcol && rcol) {
        if (s) {
            s->color = 0;
        }
        p->color = 1;
    } else {
        DelCase5(node);
    }
}

template<class T, class T1>
void RBT<T, T1>::DelCase5(shared_ptr<Node> node) {
    shared_ptr<Node> s = sibling(node);
    shared_ptr<Node> p = node->parent;

    bool lcol = s->left ? s->left->color : 1;
    bool rcol = s->right ? s->right->color : 1;

    if (s->color) {
        if (node.equals(p->left) && rcol && !lcol) {
            s->color = 0;
            s->left->color = 1;
            RotateRight(s);
        } else if (node.equals(p->right) && lcol && !rcol) {
            s->color = 0;
            s->right->color = 1;
            RotateLeft(s);
        }
    }

    DelCase6(node);
}

template<class T, class T1>
void RBT<T, T1>::DelCase6(shared_ptr<Node> node) {
    shared_ptr<Node>  s = sibling(node);
    shared_ptr<Node> p = node->parent;
    s->color = p->color;
    p->color = 1;

    if (node.equals(p->left)) {
        if (s->right) {
            s->right->color = 1;
        }
        RotateLeft(p);
    } else {
        if (s->left) {
            s->left->color = 1;
        }
        RotateRight(p);
    }
}

