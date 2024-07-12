#pragma once

#include <cstddef>
#include <iostream>
#include <iterator>

template<typename T>
class Iterator {
    private:
        T* ptr_ = nullptr;
        T* begin_ = nullptr;
        T* end_ = nullptr;
        size_t size_ = 0;

    public:
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::random_access_iterator_tag;
        using reference = T&;
        using pointer = T*;

        Iterator() = default;

        Iterator(pointer ptr, pointer begin, pointer end, size_t size)
            : ptr_(ptr), begin_(begin), end_(end), size_(size) {}

        Iterator(const Iterator& other) : ptr_(other.ptr_),
                                          begin_(other.begin_),
                                          end_(other.end_), size_(other.size_) {}

        Iterator& operator=(const Iterator& other) {
            if (this != &other) {
                this->ptr_ = other.ptr_;
                this->begin_ = other.begin_;
                this->end_ = other.end_;
                this->size_ = other.size_;
            }
            return *this;
        }

        ~Iterator() = default;

        Iterator& operator++() {
            ++ptr_;
            if (ptr_ == end_) {
                ptr_ = begin_;
            }
            return *this;
        }

        Iterator& operator--() {
            --ptr_;
            if (ptr_ == begin_ - 1) {
                ptr_ = end_;
            }
            return *this;
        }

        Iterator operator++(int) {
            Iterator temp = *this;
            ++(*this);
            return temp;
        }

        Iterator operator--(int) {
            Iterator temp = *this;
            --(*this);
            return temp;
        }

        Iterator operator+(int n) const {
            Iterator iter(*this);
            if (n < 0) {
                return iter - (-n);
            }
            int new_pos = (iter.ptr_ - begin_ + n) % size_;
            iter.ptr_ = begin_ + new_pos;
            return iter;
        }

        Iterator& operator+=(int n) {
            return *this + n;
        }

        Iterator operator-(int n) const {
            Iterator iter(*this);
            if (n < 0) {
                return iter + (-n);
            }
            int new_pos = (iter.ptr_ - begin_ - n + size_) % size_;
            iter.ptr_ = begin_ + new_pos;
            return iter;
        }

        bool operator==(const Iterator& other) const {
            return ptr_ == other.ptr_;
        }

        bool operator!=(const Iterator& other) const {
            return !(*this == other);
        }

        reference operator*() {
            return *ptr_;
        }

        pointer operator->() {
            return ptr_;
        }

        pointer ptr() const {
            return ptr_;
        }

        size_t size() const {
            return size_;
        }
};

template<typename T>
size_t operator-(const Iterator<T>& lhs, const Iterator<T>& rhs) {
    if (lhs.ptr() >= rhs.ptr()) {
        return lhs.ptr() - rhs.ptr();
    }
    return lhs.ptr() - rhs.ptr() + lhs.size();
}

template<typename T>
class ConstIterator {
    private:
        T* ptr_ = nullptr;
        T* begin_ = nullptr;
        T* end_ = nullptr;
        size_t size_ = 0;

    public:
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::random_access_iterator_tag;
        using const_reference = const T&;
        using pointer = T*;

        ConstIterator() = default;

        ConstIterator(pointer ptr, pointer begin, pointer end, size_t size)
            : ptr_(ptr), begin_(begin), end_(end), size_(size) {}

        ConstIterator(const ConstIterator& other) : ptr_(other.ptr_),
                                                    begin_(other.begin_),
                                                    end_(other.end_), size_(other.size_) {}

        ConstIterator& operator=(const ConstIterator& other) {
            if (this != &other) {
                this->ptr_ = other.ptr_;
                this->begin_ = other.begin_;
                this->end_ = other.end_;
                this->size_ = other.size_;
            }
            return *this;
        }

        ~ConstIterator() = default;

        ConstIterator& operator++() {
            ++ptr_;
            if (ptr_ == end_ + 1) {
                ptr_ = begin_;
            }
            return *this;
        }

        ConstIterator& operator--() {
            --ptr_;
            if (ptr_ == begin_ - 1) {
                ptr_ = end_;
            }
            return *this;
        }

        ConstIterator operator++(int) {
            Iterator temp = *this;
            ++(*this);
            return temp;
        }

        ConstIterator operator--(int) {
            Iterator temp = *this;
            --(*this);
            return temp;
        }

        ConstIterator operator+(int n) const {
            Iterator iter(*this);
            if (n < 0) {
                return iter - (-n);
            }
            int new_pos = (iter.ptr_ - begin_ + n) % size_;
            iter.ptr_ = begin_ + new_pos;
            return iter;
        }

        ConstIterator& operator+=(int n) {
            return *this + n;
        }

        ConstIterator operator-(int n) const {
            Iterator iter(*this);
            if (n < 0) {
                return iter + (-n);
            }
            int new_pos = (iter.ptr_ - begin_ - n + size_) % size_;
            iter.ptr_ = begin_ + new_pos;
            return iter;
        }

        bool operator==(const ConstIterator& other) const {
            return ptr_ == other.ptr_;
        }

        bool operator!=(const ConstIterator& other) const {
            return !(*this == other);
        }

        const_reference operator*() {
            return *ptr_;
        }

        pointer operator->() {
            return ptr_;
        }

        pointer ptr() const {
            return ptr_;
        }
};
