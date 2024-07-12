#include "algorithm.h"
#include <gtest/gtest.h>

#include <deque>
#include <list>

TEST(AlgorithmTests, all_of) {
    std::vector<int> vector;
    EXPECT_TRUE(my_algo::all_of(vector.begin(), vector.end(), [](int x) { return x > 0; }));

    std::array<double, 5> array = {7.3, 6.26, 88.26, 10.0, 3.846};
    EXPECT_TRUE(my_algo::all_of(array.begin(), array.end(), [](double x) { return x > 0; }));

    std::list<int> list = {85, -2234, 25, -2958, 37};
    EXPECT_FALSE(my_algo::all_of(list.begin(), list.end(), [](int x) { return x > 0; }));

    struct Person {
        std::string name;
        int age;
    };

    std::vector<Person> vector_struct = {{"Name1", 24}, {"Name2", 56}, {"Name3", 47}};
    EXPECT_TRUE(my_algo::all_of(vector_struct.begin(),
                                vector_struct.end(),
                                [](const Person& p) { return p.age < 100; }));

    std::map<int, std::string> map = {{1, "one"}, {2, "two"}, {3, "three"}};
    EXPECT_TRUE(my_algo::all_of(map.begin(),
                                map.end(),
                                [](const std::pair<int, std::string>& p) { return p.first > 0; }));

    std::set<int> set = {1, 2, 3, 4, 5, 6, 7};
    EXPECT_TRUE(my_algo::all_of(set.begin(), set.end(), [](int x) { return x > 0; }));
}

TEST(AlgorithmTests, any_of) {
    std::vector<int> vector = {1, 2, -3, 4, -5};
    EXPECT_TRUE(my_algo::any_of(vector.begin(), vector.end(), [](int x) { return x > 0; }));
    EXPECT_FALSE(my_algo::any_of(vector.begin(), vector.end(), [](int x) { return x < -5; }));

    std::array<double, 5> array = {7.3, 6.26, 88.26, 10.0, 3.846};
    EXPECT_TRUE(my_algo::any_of(array.begin(), array.end(), [](double x) { return x < 7; }));
    EXPECT_FALSE(my_algo::any_of(array.begin(), array.end(), [](double x) { return x < 0; }));

    std::list<int> list = {85, -2234, 25, -2958, 37};
    EXPECT_TRUE(my_algo::any_of(list.begin(), list.end(), [](int x) { return x < 0; }));
    EXPECT_FALSE(my_algo::any_of(list.begin(), list.end(), [](int x) { return x < -3000; }));
}

TEST(AlgorithmTests, none_of) {
    std::vector<int> vector;
    EXPECT_TRUE(my_algo::none_of(vector.begin(), vector.end(), [](int x) { return x > 0; }));

    std::array<double, 5> array = {7.3, 6.26, 88.26, 10.0, 3.846};
    EXPECT_TRUE(my_algo::none_of(array.begin(), array.end(), [](double x) { return x < 0; }));

    std::list<int> list = {85, -2234, 25, -2958, 37};
    EXPECT_FALSE(my_algo::none_of(list.begin(), list.end(), [](int x) { return x > 0; }));
}

TEST(AlgorithmTests, one_of) {
    std::vector<int> vector;
    EXPECT_FALSE(my_algo::one_of(vector.begin(), vector.end(), [](int x) { return x == 0; }));

    std::array<double, 5> array = {7.3, 6.26, 88.26, 10.0, 3.846};
    EXPECT_TRUE(my_algo::one_of(array.begin(), array.end(), [](double x) { return x < 4; }));

    std::list<int> list = {85, -2234, 25, -2958, 37};
    EXPECT_FALSE(my_algo::one_of(list.begin(), list.end(), [](int x) { return x < 0; }));
}

TEST(AlgorithmTests, is_sorted) {
    std::list<int> list = {1, 2, 3, 4, 5, 6};
    EXPECT_TRUE(my_algo::is_sorted(list.begin(), list.end()));
    EXPECT_FALSE(my_algo::is_sorted(list.begin(), list.end(), std::greater()));

    std::vector<std::string> vector = {"a", "bbb", "ccccc", "ddddddd"};
    EXPECT_TRUE(my_algo::is_sorted(vector.begin(), vector.end(), [](const std::string& s1, const std::string& s2) {
        return s1.size() < s2.size();
    }));
}

TEST(AlgorithmTests, is_partitioned) {
    std::list<int> list = {1, 2, 3, 4, 5, 6, -1, -2, -3, -4, -5, -6};
    EXPECT_TRUE(my_algo::is_partitioned(list.begin(), list.end(), [](int i) { return i > 0; }));
    EXPECT_FALSE(my_algo::is_partitioned(list.begin(), list.end(), [](int i) { return i < 0; }));

    std::vector<std::string> vector = {"1", "1", "1", "2", "1"};
    EXPECT_FALSE(my_algo::is_partitioned(vector.begin(), vector.end(), [](const std::string& s) { return s == "1"; }));
}

TEST(AlgorithmTests, find_not) {
    std::vector<int> vector = {1, 2, 3, 4, 5};
    auto result1 = my_algo::find_not(vector.begin(), vector.end(), 3);
    EXPECT_EQ(*result1, 1);

    std::list<std::string> list = {"aaaa", "bbbb", "ccccccc"};
    auto result2 = my_algo::find_not(list.begin(), list.end(), "aaaa");
    EXPECT_EQ(*result2, "bbbb");

    std::deque<float> deque = {1.1, 2.2, 3.3, 4.4, 5.5};
    auto result3 = my_algo::find_not(deque.begin(), deque.end(), 5.5);
    EXPECT_FLOAT_EQ(*result3, 1.1);

    vector = {1, 1, 1, 1, 1};
    auto result4 = my_algo::find_not(vector.begin(), vector.end(), 1);
    EXPECT_EQ(result4, vector.end());
}

TEST(AlgorithmTests, find_backward) {
    std::vector<int> vector = {1, 2, 3, 4, 5, 4, 3, 2, 1};
    auto result1 = my_algo::find_backward(vector.begin(), vector.end(), 4);
    EXPECT_EQ(result1, vector.end() - 4);
    auto result2 = my_algo::find_backward(vector.begin(), vector.end(), 6);
    EXPECT_EQ(result2, vector.end());
}

TEST(AlgorithmTests, is_palindrome) {
    std::string palindrome = "abcdcba";
    std::string not_palindrome = "hello";
    std::string empty_string;
    EXPECT_TRUE(my_algo::is_palindrome(palindrome.begin(), palindrome.end()));
    EXPECT_FALSE(my_algo::is_palindrome(not_palindrome.begin(), not_palindrome.end()));
    EXPECT_TRUE(my_algo::is_palindrome(empty_string.begin(), empty_string.end()));

    std::vector<int> vector1{1, 2, 3, 4, 3, 2, 1};
    std::vector<int> vector2{1, 2, 3, 4, 5, 6};
    EXPECT_TRUE(my_algo::is_palindrome(vector1.begin(), vector1.end()));
    EXPECT_FALSE(my_algo::is_palindrome(vector2.begin(), vector2.end()));
}
