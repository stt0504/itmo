#pragma once

#include "iterator.h"

#include <iostream>
#include <limits>
#include <memory>

template<typename T, typename Alloc = std::allocator<T>>
class CCircularBuffer {
    private:
        void Construct() {
            for (int i = 0; i < capacity_; ++i) {
                std::allocator_traits<Alloc>::construct(allocator_, begin_memory_ + i);
            }
        }

        void Destruct() {
            for (int i = 0; i < capacity_; ++i) {
                std::allocator_traits<Alloc>::destroy(allocator_, begin_memory_ + i);
            }
        }

        Alloc allocator_;
        std::size_t size_ = 0;
        std::size_t capacity_ = 0;
        T* begin_ = nullptr;
        T* end_ = nullptr;
        T* begin_memory_ = nullptr;
        T* end_memory_ = nullptr;

    public:
        using allocator_type = Alloc;
        using value_type = T;

        CCircularBuffer() = default;

        explicit CCircularBuffer(size_t capacity) : capacity_(capacity) {
            begin_memory_ = allocator_.allocate(capacity_);
            end_memory_ = begin_memory_ + capacity_;
            begin_ = begin_memory_;
            end_ = begin_memory_;
            Construct();
        };

        CCircularBuffer(const std::initializer_list<T>& il) : size_(il.size()),
                                                              capacity_(il.size()) {
            begin_memory_ = allocator_.allocate(capacity_);
            end_memory_ = begin_memory_ + capacity_;
            begin_ = begin_memory_;
            end_ = begin_memory_;
            Construct();
            std::copy(il.begin(), il.end(), begin_memory_);
        }

        CCircularBuffer(const CCircularBuffer& other) :
            size_(other.size_),
            capacity_(other.capacity_),
            allocator_(other.allocator_) {
            begin_memory_ = allocator_.allocate(capacity_);
            end_memory_ = begin_memory_ + capacity_;
            begin_ = begin_memory_;
            end_ = begin_memory_;
            Construct();
            std::copy(other.begin_memory_, other.end_memory_, begin_memory_);
        };

        explicit CCircularBuffer(std::size_t size, const T& value) : size_(size), capacity_(size) {
            begin_memory_ = allocator_.allocate(capacity_);
            end_memory_ = begin_memory_ + capacity_;
            begin_ = begin_memory_;
            end_ = begin_memory_;
            Construct();
            std::fill(begin_memory_, end_memory_, value);
        }

        template<typename Iterator>
        explicit CCircularBuffer(Iterator i, Iterator j) {
            size_ = j - i;
            capacity_ = size_;
            begin_memory_ = allocator_.allocate(capacity_);
            end_memory_ = begin_memory_ + capacity_;
            begin_ = begin_memory_;
            end_ = begin_memory_;
            Construct();
            std::copy(i, j, begin_memory_);
        }

        ~CCircularBuffer() {
            Destruct();
            std::allocator_traits<Alloc>::deallocate(allocator_, begin_memory_, capacity_);
        }

        CCircularBuffer& operator=(const CCircularBuffer& other) {
            if (this != &other) {
                Destruct();
                std::allocator_traits<Alloc>::deallocate(allocator_, begin_memory_, capacity_);
                size_ = other.size_;
                capacity_ = other.capacity_;
                allocator_ = other.allocator_;
                begin_memory_ = allocator_.allocate(capacity_);
                end_memory_ = begin_memory_ + capacity_;
                begin_ = begin_memory_;
                end_ = begin_memory_;
                Construct();
                std::copy(other.begin_memory_, other.end_memory_, begin_memory_);
            }
            return *this;
        }

        CCircularBuffer& operator=(const std::initializer_list<T>& il) {
            Destruct();
            std::allocator_traits<Alloc>::deallocate(allocator_, begin_memory_, capacity_);
            size_ = il.size();
            capacity_ = il.size();
            begin_memory_ = allocator_.allocate(capacity_);
            end_memory_ = begin_memory_ + capacity_;
            begin_ = begin_memory_;
            end_ = begin_memory_;
            Construct();
            std::copy(il.begin(), il.end(), begin_memory_);
            return *this;
        }

        bool operator==(const CCircularBuffer& other) const {
            if (size() != other.size_) {
                return false;
            }
            for (int i = 0; i < size(); i++) {
                if ((*this)[i] != other[i]) {
                    return false;
                }
            }
            return true;
        }

        bool operator!=(const CCircularBuffer& other) const {
            return !(*this == other);
        }

        T& operator[](size_t index) const {
            return begin_memory_[(begin_ - begin_memory_ + index) % capacity_];
        }

        Iterator<T> begin() const {
            return Iterator(begin_, begin_, end_, size_);
        }

        Iterator<T> end() const {
            return Iterator(end_, begin_, end_, size_);
        }

        T& back() {
            T* back = end_ - 1;
            if (back == begin_memory_ - 1) {
                back = end_memory_ - 1;
            }
            return *(back);
        }

        const T& back() const {
            T* back = end_ - 1;
            if (back == begin_memory_ - 1) {
                back = end_memory_ - 1;
            }
            return *(back);
        }

        T& front() {
            return *begin_;
        }

        const T& front() const {
            return *begin_;
        }

        void push_back(const T& t) {
            if (size_ == capacity_) {
                ++end_;
                if (end_ == end_memory_) {
                    end_ = begin_memory_;
                }
                begin_ = end_;
                back() = t;
            } else {
                ++end_;
                if (end_ == end_memory_) {
                    end_ = begin_memory_;
                }
                back() = t;
                size_++;
            }
        }

        void push_front(const T& t) {
            if (size_ == capacity_) {
                --begin_;
                if (begin_ == begin_memory_ - 1) {
                    begin_ = end_memory_ - 1;
                }
                end_ = begin_;
                front() = t;
            } else {
                --begin_;
                if (begin_ == begin_memory_ - 1) {
                    begin_ = end_memory_ - 1;
                }
                front() = t;
                size_++;
            }
        }

        void pop_back() {
            if (empty()) return;
            --end_;
            if (end_ == begin_memory_ - 1) {
                end_ = end_memory_ - 1;
            }
            size_--;
        }

        void pop_front() {
            if (empty()) return;
            ++begin_;
            if (begin_ == end_memory_) {
                begin_ = begin_memory_;
            }
            size_--;
        }

        ConstIterator<T> cbegin() const {
            return ConstIterator(begin_, begin_, end_, size_);
        }

        ConstIterator<T> cend() const {
            return ConstIterator(end_, begin_, end_, size_);
        }

        void swap(CCircularBuffer& other) {
            if (*this != other) {
                std::swap(begin_, other.begin_);
                std::swap(end_, other.end_);
                std::swap(begin_memory_, other.begin_memory_);
                std::swap(end_memory_, other.end_memory_);
                std::swap(size_, other.size_);
                std::swap(capacity_, other.capacity_);
            }
        }

        [[nodiscard]] std::size_t size() const {
            return size_;
        }

        [[nodiscard]] std::size_t capacity() const {
            return capacity_;
        }

        [[nodiscard]] std::size_t max_size() const {
            const auto alloc_max_size = std::allocator_traits<allocator_type>::max_size(allocator_);
            const auto container_max_size = alloc_max_size / sizeof(value_type);
            return container_max_size;
        }

        [[nodiscard]] bool empty() const {
            return size_ == 0;
        }

        void clear() {
            size_ = 0;
            begin_ = begin_memory_;
            end_ = begin_memory_;
        }

        Iterator<T> insert(const Iterator<T>& p, const T& t) {
            Iterator<T> pos = p;
            if (size() == capacity()) {
                for (Iterator it = end() - 1; it != pos; --it) {
                    *it = *(it - 1);
                }
                *pos = t;
            } else {
                size_++;
                for (Iterator it = Iterator(end_, begin_, end_, size_); it != pos; --it) {
                    *it = *(it - 1);
                }
                *pos = t;
                ++end_;
                if (end_ == end_memory_) {
                    end_ = begin_memory_;
                }
            }
            return pos;
        }

        Iterator<T> insert(const Iterator<T>& p, size_t n, const T& t) {
            Iterator<T> pos = p;
            for (int i = 0; i < n; i++) {
                insert(pos, t);
            }
            return pos;
        }

        template<typename AnyIterator>
        Iterator<T> insert(const Iterator<T>& p, AnyIterator i, AnyIterator j) {
            AnyIterator it;
            Iterator<T> pos = p;
            if (std::distance(i, j) <= 0) {
                return pos;
            }
            for (it = --j; it != i - 1; --it) {
                insert(pos, *it);
                --pos;
            }
            return pos;
        }

        Iterator<T> insert(const Iterator<T>& p, const std::initializer_list<T>& il) {
            Iterator<T> pos = p;
            auto iterator = il.end() - 1;
            for (int i = 0; i < il.size(); i++) {
                insert(p, *iterator);
                iterator--;
            }
            return pos;
        }

        Iterator<T> erase(const Iterator<T>& p) {
            Iterator pos = p;
            for (Iterator it = pos; it != end() - 1; ++it) {
                *it = *(it + 1);
            }
            --end_;
            if (end_ == begin_memory_ - 1) {
                end_ = end_memory_ - 1;
            }
            size_--;
            return pos;
        }

        Iterator<T> erase(Iterator<T> p1, Iterator<T> p2) {
            int count = std::distance(p1, p2 - 1);
            for (int i = 0; i < count; i++) {
                erase(p1);
            }
            if (count >= 0) {
                erase(p1);
            }
            return p1;
        }

        template<typename Iterator>
        void assign(Iterator i, Iterator j) {
            *this = CCircularBuffer(i, j);
        }

        void assign(const std::initializer_list<T>& il) {
            *this = il;
        }

        void assign(std::size_t n, const T& t) {
            *this = CCircularBuffer(n, t);
        }

        const T& at(std::size_t index) const {
            return (*this)[index];
        }
};

template<typename T>
void swap(CCircularBuffer<T>& a, CCircularBuffer<T>& b) {
    a.swap(b);
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const CCircularBuffer<T>& a) {
    if (a.empty()) {
        os << "[]";
        return os;
    }
    os << "[";
    for (auto it = a.begin(); it != a.end() - 1; ++it) {
        os << *it;
        os << ", ";
    }
    os << *(a.end() - 1);
    os << "]";
    return os;
}
