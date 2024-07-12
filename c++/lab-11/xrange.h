#pragma once

#include <iterator>

template<typename T>
class xrange_iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;
        using const_pointer = const T*;
        using const_reference = const T&;

        xrange_iterator(const_reference start, const_reference end, const_reference step, bool has_step)
            : current_(start), end_(end), step_(step), has_step_(has_step) {}

        bool operator==(const xrange_iterator& other) const {
            return current_ == other.current_;
        }

        bool operator!=(const xrange_iterator& other) const {
            return current_ != other.current_;
        }

        pointer operator->() {
            return &current_;
        }

        const_pointer operator->() const {
            return &current_;
        }

        value_type operator*() const {
            return current_;
        }

        void operator++() {
            if (!has_step_) {
                ++current_;
                if (current_ > end_) {
                    current_ = end_;
                }
                return;
            }
            current_ += step_;
            if ((step_ > value_type() && current_ > end_) || (step_ < value_type() && current_ < end_)) {
                current_ = end_;
            }
        }

        xrange_iterator operator++(int) {
            xrange_iterator tmp = *this;
            ++(*this);
            return tmp;
        }

    private:
        value_type current_;
        value_type end_;
        value_type step_;
        bool has_step_;
};

template<typename T>
class xrange {
    public:
        using value_type = T;
        using reference = T&;
        using const_reference = const T&;
        using iterator = xrange_iterator<T>;
        using const_iterator = const xrange_iterator<T>;

        explicit xrange(value_type end) : start(value_type()), end_(end){}

        xrange(value_type start, value_type end) : start(start), end_(end){}

        xrange(value_type start, value_type end, value_type step) : start(start), end_(end), step_(step) {
            has_step_ = true;
        }

        const_iterator begin() const {
            return xrange_iterator<T>(start, end_, step_, has_step_);
        }

        const_iterator end() const {
            return xrange_iterator<T>(end_, end_, step_, has_step_);
        }

    private:
        T start;
        T end_;
        T step_;
        bool has_step_ = false;
};
