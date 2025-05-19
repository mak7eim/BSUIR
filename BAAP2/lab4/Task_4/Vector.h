#ifndef VECTOR_H
#define VECTOR_H
#include <cstddef>


template <typename T>
class Vector {

   private:
    T* data_;
    size_t size_;
    size_t capacity_;


    void destroy_range(T* start, T* end) {
        while (start != end) {
            start->~T();
            ++start;
        }
    }

    void reallocate(size_t new_capacity) {
        T* new_data = static_cast<T*>(::operator new(new_capacity * sizeof(T)));
        size_t new_size = size_;

        for (size_t i = 0; i < size_; ++i) {
            new (&new_data[i]) T(data_[i]);
        }

        destroy_range(data_, data_ + size_);
        ::operator delete(data_);

        data_ = new_data;
        capacity_ = new_capacity;
        size_ = new_size;
    }

   public:
    Vector(size_t n, const T& value = T())
        : data_(nullptr), size_(0), capacity_(0) {
        reserve(n);
        for (size_t i = 0; i < n; ++i) {
            push_back(value);
        }
    }

    ~Vector() {
        destroy_range(data_, data_ + size_);
        ::operator delete(data_);
    }

    Vector() {
        data_ = nullptr;
        size_ = 0;
        capacity_ = 0;
    }
    T* begin() { return data_; }

    const T* cbegin() const { return data_; }

    T& back() { return *(data_ + size_ - 1); }

    T& front() { return *(data_); }


    T* data() { return data_; }

    bool empty() { return size_ == 0; }



    T* rbegin() { return data_ + size_ - 1; }

    T* rend() { return data_; }


    T size() { return size_; }


    T& at(size_t i) {
        if (i >= size_) {
            throw "Ошибка обращения";
        }
        return *(data_ + i);
    }

    T capacity() { return capacity_; }

    void assign(size_t count, const T& value) {
        clear();
        reserve(count);
        for (size_t i = 0; i < count; ++i) {
            push_back(value);
        }
    }


    template <typename... Args>
    T* emplace(const T* pos, Args&&... args) {
        size_t index = pos - cbegin();
        if (size_ == capacity_) {
            reserve(capacity_ == 0 ? 1 : capacity_ * 2);
        }

        for (size_t i = size_; i > index; --i) {
            new (&data_[i]) T(data_[i - 1]);
            data_[i - 1].~T();
        }
        new (&data_[index]) T(args...);
        ++size_;
        return begin() + index;
    }

    template <typename... Args>
    void emplace_back(Args&&... args) {
        if (size_ == capacity_) {
            reserve(capacity_ == 0 ? 1 : capacity_ * 2);
        }
        new (&data_[size_]) T(args...);
        ++size_;
    }

    T* erase(const T* pos) {
        size_t index = pos - cbegin();
        data_[index].~T();
        for (size_t i = index; i < size_ - 1; ++i) {
            new (&data_[i]) T(data_[i + 1]);
            data_[i + 1].~T();
        }
        --size_;
        return begin() + index;
    }

    T* erase(const T* first, const T* last) {
        size_t start = first - cbegin();
        size_t count = last - first;
        for (size_t i = start; i < start + count; ++i) {
            data_[i].~T();
        }

        for (size_t i = start; i < size_ - count; ++i) {
            new (&data_[i]) T(data_[i + count]);
            data_[i + count].~T();
        }
        size_ -= count;
        return begin() + start;
    }

    T* insert(const T* pos, const T& value) { return emplace(pos, value); }

    T* insert(const T* pos, size_t count, const T& value) {
        size_t index = pos - cbegin();
        if (size_ + count > capacity_) {
            reserve(size_ + count);
        }

        for (size_t i = size_; i > index; --i) {
            new (&data_[i + count - 1]) T(data_[i - 1]);
            data_[i - 1].~T();
        }

        for (size_t i = 0; i < count; ++i) {
            new (&data_[index + i]) T(value);
        }
        size_ += count;
        return begin() + index;
    }

    void pop_back() {
        if (!empty()) {
            data_[size_ - 1].~T();
            --size_;
        }
    }

    void push_back(const T& value) {
        if (size_ == capacity_) {
            reserve(capacity_ == 0 ? 1 : capacity_ * 2);
        }
        new (&data_[size_]) T(value);
        ++size_;
    }

    void reserve(size_t new_capacity) {
        if (new_capacity > capacity_) {
            reallocate(new_capacity);
        }
    }

    void resize(size_t count, const T& value = T()) {
        if (count > size_) {
            reserve(count);
            while (size_ < count) {
                push_back(value);
            }
        } else {
            while (size_ > count) {
                pop_back();
            }
        }
    }

    void clear() {
        destroy_range(data_, data_ + size_);
        size_ = 0;
    }

    void sWap(Vector& other) {
        T* temp_data = data_;
        size_t temp_size = size_;
        size_t temp_capacity = capacity_;

        data_ = other.data_;
        size_ = other.size_;
        capacity_ = other.capacity_;

        other.data_ = temp_data;
        other.size_ = temp_size;
        other.capacity_ = temp_capacity;
    }
};


#endif	// VECTOR_H
