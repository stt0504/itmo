#pragma once
#include <iostream>
#include <iterator>

namespace my_algo {

template<typename Iterator, typename UnaryPredicate>
bool all_of(Iterator first, Iterator last, UnaryPredicate pred) {
    while (first != last) {
        if (!pred(*first)) {
            return false;
        }
        ++first;
    }
    return true;
}

template<typename Iterator, typename UnaryPredicate>
bool any_of(Iterator first, Iterator last, UnaryPredicate pred) {
    while (first != last) {
        if (pred(*first)) {
            return true;
        }
        ++first;
    }
    return false;
}

template<typename Iterator, typename UnaryPredicate>
bool none_of(Iterator first, Iterator last, UnaryPredicate pred) {
    while (first != last) {
        if (pred(*first)) {
            return false;
        }
        ++first;
    }
    return true;
}

template<typename Iterator, typename UnaryPredicate>
bool one_of(Iterator first, Iterator last, UnaryPredicate pred) {
    bool found_one = false;
    while (first != last) {
        if (pred(*first)) {
            if (found_one) {
                return false;
            }
            found_one = true;
        }
        ++first;
    }
    return found_one;
}

template<typename Iterator, typename Compare = std::less<>>
bool is_sorted(Iterator first, Iterator last, Compare comp = Compare()) {
    if (first == last) {
        return true;
    }

    Iterator next = first;
    while (++next != last) {
        if (!comp(*first, *next)) {
            return false;
        }
        ++first;
    }
    return true;
}

template<typename Iterator, typename UnaryPredicate>
bool is_partitioned(Iterator first, Iterator last, UnaryPredicate pred) {
    bool is_partitioned = true;
    Iterator it = first;

    while (it != last && pred(*it)) {
        ++it;
    }

    while (it != last) {
        if (pred(*it)) {
            return false;
        }
        ++it;
    }

    return is_partitioned;
}

template<typename Iterator, typename T>
Iterator find_not(Iterator first, Iterator last, const T& value) {
    while (first != last && *first == value) {
        ++first;
    }
    return first;
}

template<typename Iterator, typename T>
Iterator find_backward(Iterator first, Iterator last, const T& value) {
    Iterator it = last;
    while (it != first) {
        --it;
        if (*it == value) {
            return it;
        }
    }
    return last;
}

template<typename Iterator, typename BinaryPredicate = std::equal_to<>>
bool is_palindrome(Iterator first, Iterator last, BinaryPredicate pred = BinaryPredicate()) {
    if (first == last) {
        return true;
    }

    --last;
    while (first < last) {
        if (!pred(*first, *last)) {
            return false;
        }
        ++first;
        --last;
    }
    return true;
}

}
