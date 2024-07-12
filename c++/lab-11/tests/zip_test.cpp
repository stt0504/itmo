#include "zip.h"
#include <gtest/gtest.h>

#include <deque>
#include <list>
#include <forward_list>

TEST(ZipTest, Test1) {
    std::vector<int> vector = {1, 2, 3};
    std::array<int, 2> array = {4, 5};
    std::vector<std::pair<int, int>> expected = {{1, 4}, {2, 5}};
    zip result = zip(vector, array);
    EXPECT_EQ(result, expected);
}

TEST(ZipTest, Test2) {
    std::list<int> list = {};
    std::vector<int> vector = {1, 2};
    std::vector<std::pair<int, int>> expected = {};
    auto result = zip(list, vector);
    EXPECT_EQ(result, expected);
}

TEST(ZipTest, Test3) {
    std::forward_list<int> forward_list = {1, 2, 3};
    std::list<char> list = {'a', 'b', 'c'};
    std::vector<std::pair<int, char>> expected = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
    auto result = zip(forward_list, list);
    EXPECT_EQ(result, expected);
}

TEST(ZipTest, Test4) {
    struct Person {
        std::string name;
        int age;
        bool operator==(const Person& other) const {
            return (name == other.name) && (age == other.age);
        }
    };

    std::vector<Person> persons = {{"Person1", 27}, {"Person2", 37}, {"Person3", 46}};
    std::vector<int> ids = {1, 2, 3};
    std::vector<std::pair<Person, int>> expected = {{{"Person1", 27}, 1}, {{"Person2", 37}, 2}, {{"Person3", 46}, 3}};
    auto result = zip(persons, ids);
    EXPECT_EQ(result, expected);
}

TEST(ZipTest, Test5) {
    std::vector<int> vector = {1, 2, 3};
    std::set<int> set = {4, 5, 6};
    std::vector<std::pair<int, int>> expected = {{1, 4}, {2, 5}, {3, 6}};
    zip result = zip(vector, set);
    EXPECT_EQ(result, expected);
}

TEST(ZipTest, Test6) {
    std::vector<int> vector1 = {1, 2, 3};
    std::vector<double> vector2 = {2.5, 3.5, 4.5};
    std::vector<std::pair<int, double>> expected = {{1, 2.5}, {2, 3.5}, {3, 4.5}};
    zip result = zip(vector1, vector2);
    EXPECT_EQ(result, expected);
}

TEST(ZipTest, Test7) {
    std::deque<std::string> deque = {"aaa", "bbb", "ccc"};
    std::list<int> list = {1, 2, 3};
    std::vector<std::pair<std::string, int>> expected = {{"aaa", 1}, {"bbb", 2}, {"ccc", 3}};
    zip result = zip(deque, list);
    EXPECT_EQ(result, expected);
}
