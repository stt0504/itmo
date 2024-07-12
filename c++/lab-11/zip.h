#pragma once

#include <iterator>

template<typename Iterator1, typename Iterator2>
class zip_iterator {
    public:
        using value_type = std::pair<
            typename std::iterator_traits<Iterator1>::value_type,
            typename std::iterator_traits<Iterator2>::value_type
        >;
        using reference = value_type&;
        using pointer = value_type*;

        zip_iterator(Iterator1 it1, Iterator2 it2, Iterator1 end1, Iterator2 end2)
            : it1_(it1), it2_(it2), end1_(end1), end2_(end2) {
            if (it1_ != end1_ && it2_ != end2_) {
                current_pair_ = std::make_pair(*it1_, *it2_);
            }
            if (it1_ == end1_) {
                it2_ = end2_;
            }
            if (it2_ == end2_) {
                it1_ = end1_;
            }
        }

        reference operator*() {
            return current_pair_;
        }

        pointer operator->() const {
            return &current_pair_;
        }

        zip_iterator& operator++() {
            ++it1_;
            ++it2_;
            if (it1_ == end1_) {
                it2_ = end2_;
                return *this;
            }

            if (it2_ == end2_) {
                it1_ = end1_;
                return *this;
            }
            current_pair_ = std::make_pair(*it1_, *it2_);
            return *this;
        }

        zip_iterator operator++(int) {
            zip_iterator tmp(*this);
            ++(*this);
            return tmp;
        }

        bool operator==(const zip_iterator& other) const {
            return it1_ == other.it1_ && it2_ == other.it2_;
        }

        bool operator!=(const zip_iterator& other) const {
            return !(*this == other);
        }

    private:
        Iterator1 it1_;
        Iterator2 it2_;
        Iterator1 end1_;
        Iterator2 end2_;
        value_type current_pair_;
};

template<typename Container1, typename Container2>
class zip {
    public:
        using value_type = std::pair<
            typename Container1::value_type,
            typename Container2::value_type
        >;
        using iterator = zip_iterator<typename Container1::iterator, typename Container2::iterator>;

        zip(Container1& c1, Container2& c2): container1_(c1), container2_(c2) {}

        iterator begin() const {
            return zip_iterator<typename Container1::iterator, typename Container2::iterator>(container1_.begin(),
                                                                                              container2_.begin(),
                                                                                              container1_.end(),
                                                                                              container2_.end());
        }

        iterator end() const {
            return zip_iterator<typename Container1::iterator, typename Container2::iterator>(container1_.end(),
                                                                                              container2_.end(),
                                                                                              container1_.end(),
                                                                                              container2_.end());
        }

        [[nodiscard]] size_t size() const {
            return std::min(std::distance(container1_.begin(), container1_.end()),
                            std::distance(container2_.begin(), container2_.end()));
        }

        template<typename Container>
        bool operator==(const Container& other) {
            if (size() != other.size()) {
                return false;
            }
            auto i1 = other.begin();
            for (zip_iterator i2 = begin(); i2 != end(); i2++) {
                if (*i1 != *i2) {
                    return false;
                }
                i1++;
            }
            return true;
        }

        template<typename Container>
        bool operator!=(const Container& other) {
            return !(*this == other);
        }

    private:
        Container1& container1_;
        Container2& container2_;
};

template<typename Container, typename Container1, typename Container2>
bool operator==(const zip<Container1, Container2>& zip, const Container& other) {
    if (zip.size() != other.size()) {
        return false;
    }
    auto i1 = other.begin();
    for (auto i2 = zip.begin(); i2 != zip.end(); i2++) {
        if (*i1 != *i2) {
            return false;
        }
        i1++;
    }
    return true;
}

template<typename Container, typename Container1, typename Container2>
bool operator!=(const zip<Container1, Container2>& zip, const Container& other) {
    return !(zip == other);
}
