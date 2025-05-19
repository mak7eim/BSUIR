#pragma once

#ifndef MY_DEQUE_H
#define MY_DEQUE_H

#include <iostream>
#include <memory>

template <class T>
class shared_ptr
{
private:
    T *ptr;
    size_t *count;

public:
    ~shared_ptr()
    {
        if (!count)
        {
            return;
        }
        --*count;
        if (!*count)
        {
            delete ptr;
            delete count;
        }
    }

    size_t use_count()
    {
        return *count;
    }

    T *get()
    {
        return ptr;
    }

    shared_ptr(T *tmp) : ptr(tmp), count(new size_t(1)) {}

    shared_ptr(const shared_ptr<T> &tmp) : ptr(tmp.ptr), count(tmp.count)
    {
        ++*count;
    }

    shared_ptr<T> &operator=(const shared_ptr<T> &tmp)
    {
        if (this == &tmp)
        {
            return *this;
        }
        --*count;
        if (*count == 0)
        {
            delete ptr;
            delete count;
        }
        ptr = tmp.ptr;
        count = tmp.count;
        ++*count;
        return *this;
    }

    shared_ptr<T> &operator=(T *tmp)
    {
        if (ptr != tmp)
        {
            if (count && --(*count) == 0)
            {
                delete ptr;
                delete count;
            }
            ptr = tmp;
            count = new size_t(1);
        }
        return *this;
    }

    bool operator==(const shared_ptr<T> &tmp)
    {
        return this->ptr == tmp.ptr;
    }

    bool operator!=(const shared_ptr<T> &tmp)
    {
        return !(this->ptr == tmp.ptr);
    }
    bool operator!=(T *tmp)
    {
        return !(this->ptr == tmp);
    }

    shared_ptr(shared_ptr<T> &&tmp) noexcept
    {
        ptr = tmp.ptr;
        count = tmp.count;
        tmp.count = nullptr;
        tmp.ptr = nullptr;
    }

    shared_ptr<T> &operator=(shared_ptr<T> &&tmp) noexcept
    {
        if (this == &tmp)
        {
            return *this;
        }
        --*count;
        if (*count == 0)
        {
            delete ptr;
            delete count;
        }
        ptr = tmp.ptr;
        count = tmp.count;
        tmp.count = nullptr;
        tmp.ptr = nullptr;
        return *this;
    }

    T &operator*()
    {
        return *ptr;
    }

    T *operator->()
    {
        return ptr;
    }

    T &operator[](size_t index)
    {
        return *(ptr + index);
    }
};

template <class T>
class My_deque
{

private:
    struct node
    {
    public:
        const size_t size_arr = 5;
        T *obj_arr;
        shared_ptr<node> next = nullptr;
        shared_ptr<node> prev = nullptr;

        node()
        {
            obj_arr = new T[size_arr];
            this->next = nullptr;
            this->prev = nullptr;
        }
        ~node()
        {
            for (int i = 0; i < 5; ++i)
            {
                obj_arr[i].~T();
            }
            delete[] obj_arr;
            next = prev = nullptr;
        };
    };

    class My_queue
    {
    public:
        shared_ptr<node> head;
        shared_ptr<node> tail;

        My_queue() : head(nullptr), tail(nullptr) {}

        void qpush_back()
        {
            shared_ptr<node> ptr(new node());
            ptr->prev = tail;
            if (tail != shared_ptr<node>(nullptr))
            {
                tail->next = ptr;
            }
            if (head == shared_ptr<node>(nullptr))
            {
                head = ptr;
            }
            tail = ptr;
        }

        void qpush_front()
        {
            shared_ptr<node> ptr(new node());
            ptr->next = head;
            if (head != shared_ptr<node>(nullptr))
            {
                head->prev = ptr;
            }
            if (tail == shared_ptr<node>(nullptr))
            {

                tail = ptr;
            }
            head = ptr;
        }
        void qpop_back()
        {
            if (tail == shared_ptr<node>(nullptr))
            {
                return;
            }
            shared_ptr<node> ptr = tail->prev;
            if (ptr != shared_ptr<node>(nullptr))
            {
                ptr->next = shared_ptr<node>(nullptr);
            }
            else
            {
                head = shared_ptr<node>(nullptr);
            }
            // delete tail;
            tail = ptr;
        }

        void qpop_front()
        {
            if (head == shared_ptr<node>(nullptr))
            {
                return;
            }
            shared_ptr<node> ptr = head->next;
            if (ptr != shared_ptr<node>(nullptr))
            {
                ptr->prev = shared_ptr<node>(nullptr);
            }
            else
            {
                tail = shared_ptr<node>(nullptr);
            }
            head = ptr;
        }
        T *get_at(size_t index)
        {
            shared_ptr<node> ptr = head;
            int n = 0;
            while (n != index)
            {
                if (ptr == shared_ptr<node>(nullptr))
                {
                    return head->obj_arr;
                }
                ptr = ptr->next;
                ++n;
            }
            return ptr->obj_arr;
        }

        T *operator[](size_t index)
        {
            return get_at(index);
        }
    };

public:
    size_t index_head = 5;
    size_t index_tail = 5;

private:
    size_t amount = 0;
    My_queue list;

public:
    My_deque()
    {
        list.qpush_back();
    }
    void push_back(const T &tmp)
    {
        if (index_head == 5)
        {
            list.tail->obj_arr[0] = tmp;
            index_head = 0;
            index_tail = 0;
        }
        else
        {
            if (index_tail == 4)
            {
                list.qpush_back();
                list.tail->obj_arr[0] = tmp;
                index_tail = 0;
            }
            else
            {
                list.tail->obj_arr[index_tail + 1] = tmp;
                ++index_tail;
            }
        }
        ++amount;
    }
    void push_front(const T &tmp)
    {
        if (index_head == 5)
        {
            list.head->obj_arr[0] = tmp;
            index_tail = 0;
            index_head = 0;
        }
        else
        {
            if (index_head == 0)
            {
                list.qpush_front();
                list.head->obj_arr[4] = tmp;
                index_head = 4;
            }
            else
            {
                list.head->obj_arr[index_head - 1] = tmp;
                --index_head;
            }
        }
        ++amount;
    }
    T &operator[](size_t index)
    {
        if (index >= amount)
        {
            throw std::runtime_error("out of range");
        }
        if (index < 5 - index_head)
        {
            return list.head->obj_arr[index_head + index];
        }
        if (index >= amount - index_tail - 1)
        {
            return list.tail->obj_arr[index - (amount - index_tail - 1)];
        }
        else
        {
            int amount_first = 5 - index_head;
            int i = (index - amount_first) / 5;
            int j = (index - amount_first) % 5;
            return list[i + 1][j];
        }
    }
    T &begin()
    {
        return list.head->obj_arr[index_head];
    }
    size_t size()
    {
        return amount;
    }
    void pop_front()
    {
        if (amount == 0)
        {
            return;
        }
        if (amount == 1)
        {
            list.head->obj_arr[index_head].~T();
            amount = 0;
            index_head = 5;
            index_tail = 5;
            return;
        }
        if (index_head == 4)
        {
            list.head->obj_arr[index_head].~T();
            list.qpop_front();
            index_head = 0;
            --amount;
            return;
        }
        list.head->obj_arr[index_head].~T();
        ++index_head;
        --amount;
    }
    void pop_back()
    {
        if (amount == 0)
        {
            return;
        }
        if (amount == 1)
        {
            list.tail->obj_arr[index_tail].~T();
            amount = 0;
            index_head = 5;
            index_tail = 5;
            return;
        }
        if (index_tail == 0)
        {
            list.tail->obj_arr[index_tail].~T();
            list.qpop_back();
            index_tail = 4;
            --amount;
            return;
        }
        list.head->obj_arr[index_tail].~T();
        --index_tail;
        --amount;
    }

    void resize(size_t n)
    {
        if (n == amount)
        {
            return;
        }
        if (n > amount)
        {
            while (amount != n)
            {
                push_back(T());
            }
        }
        if (n < amount)
        {
            while (amount != n)
            {
                pop_back();
            }
        }
    }
};

// template <class T>
// class my_iterator
// {
// private:
//     T *ptr = nullptr;
//     My_deque<T> &d;

// public:
//     my_iterator() = default;
//     my_iterator(My_deque<T> &d, T *p) : ptr(p), d(d) {}
//     my_iterator(My_deque<T> &d, const my_iterator &iter) : ptr(iter.ptr), d(d) {}
//     my_iterator(My_deque<T> &d, const shared_ptr<T> &ptr) : ptr(ptr.get()), d(d) {}
//     bool operator!=(my_iterator<T> tmp)
//     {
//         return !(ptr == tmp.ptr);
//     }
//     my_iterator &operator++()
//     {
//         int i = 0;
//         while (ptr != &d[i])
//         {
//             ++i;
//         }
//         ++i;
//         if (i > d.size() - 1)
//         {
//             ptr = &d[i - 1];
//             return *this;
//         }

//         ptr = &d[i];

//         return *this;
//     }
//     my_iterator &operator--()
//     {
//         int i = 0;
//         while (ptr != &d[i])
//         {
//             ++i;
//         }
//         --i;
//         ptr = &d[i];
//         return *this;
//     }

//     T &operator*()
//     {
//         return *ptr;
//     }
// };

#endif // MY_DEQUE_H