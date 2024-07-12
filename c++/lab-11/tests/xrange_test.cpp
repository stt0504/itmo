#include "xrange.h"
#include <gtest/gtest.h>

#include <deque>
#include <list>
#include <numeric>

TEST(XrangeTest, Test1) {
    xrange x = xrange(0, 5);
    std::vector<int> vector(x.begin(), x.end());
    std::vector<int> expected{0, 1, 2, 3, 4};
    EXPECT_EQ(vector, expected);
}

TEST(XrangeTest, Test2) {
    xrange x = xrange(5);
    std::vector<int> vector(x.begin(), x.end());
    std::vector<int> expected{0, 1, 2, 3, 4};
    EXPECT_EQ(vector, expected);
}

TEST(XrangeTest, Test3) {
    xrange x = xrange(1, 10, 2);
    std::vector<int> vector(x.begin(), x.end());
    std::vector<int> expected{1, 3, 5, 7, 9};
    ASSERT_EQ(vector, expected);
}

TEST(XrangeTest, Test4) {
    xrange x = xrange(10, 1, -2);
    std::vector<int> vector(x.begin(), x.end());
    std::vector<int> expected{10, 8, 6, 4, 2};
    ASSERT_EQ(vector, expected);
}

TEST(XrangeTest, Test5) {
    xrange x = xrange(1, 6);
    std::vector<int> vector(x.begin(), x.end());
    int sum = std::accumulate(x.begin(), x.end(), 0);
    ASSERT_EQ(sum, 15);
}

TEST(XrangeTest, Test6) {
    xrange x = xrange(0.5, 5.5);
    std::vector<double> vector(x.begin(), x.end());
    std::vector<double> expected{0.5, 1.5, 2.5, 3.5, 4.5};
    ASSERT_EQ(vector, expected);
}

TEST(XrangeTest, Test7) {
    xrange x = xrange(1, 6, 2);
    std::list<int> list(x.begin(), x.end());
    std::list<int> expected{1, 3, 5};
    ASSERT_EQ(list, expected);
}

TEST(XrangeTest, Test8) {
    xrange x = xrange(0, 10, 3);
    std::deque<int> deque(x.begin(), x.end());
    std::deque<int> expected{0, 3, 6, 9};
    ASSERT_EQ(deque, expected);
}

TEST(XrangeTest, Test9) {
    class Point {
        public:
            Point() = default;

            Point(int x, int y) : x_(x), y_(y) {}

            Point& operator++() {
                ++x_;
                ++y_;
                return *this;
            }

            Point operator+(const Point& other) const {
                return Point(x_ + other.x_, y_ + other.y_);
            }

            bool operator<(const Point& other) const {
                if (x_ < other.x_) {
                    return true;
                } else if (x_ == other.x_) {
                    return y_ < other.y_;
                } else {
                    return false;
                }
            }

            bool operator>(const Point& other) const {
                if (x_ > other.x_) {
                    return true;
                } else if (x_ == other.x_) {
                    return y_ > other.y_;
                } else {
                    return false;
                }
            }

            Point& operator+=(const Point& other) {
                x_ += other.x_;
                y_ += other.y_;
                return *this;
            }

            bool operator==(const Point& other) const {
                return x_ == other.x_ && y_ == other.y_;
            }

            bool operator!=(const Point& other) const {
                return !(*this == other);
            }

            [[nodiscard]] int x() const {
                return x_;
            }

            [[nodiscard]] int y() const {
                return y_;
            }

        private:
            int x_ = 0;
            int y_ = 0;
    };

    xrange<Point> x(Point(1, 1), Point(5, 5));
    std::vector<Point> vector(x.begin(), x.end());
    std::vector<Point> expected{Point(1, 1), Point(2, 2), Point(3, 3), Point(4, 4)};
    ASSERT_EQ(vector, expected);

    x = xrange(Point(5, 5));
    vector = std::vector(x.begin(), x.end());
    expected = std::vector{Point(0, 0), Point(1, 1), Point(2, 2), Point(3, 3), Point(4, 4)};
    ASSERT_EQ(vector, expected);

    x = xrange(Point(1, 1), Point(10, 10), Point(2, 2));
    vector = std::vector(x.begin(), x.end());
    expected = std::vector{Point(1, 1), Point(3, 3), Point(5, 5), Point(7, 7), Point(9, 9)};
    ASSERT_EQ(vector, expected);
}
