#include "CCircularBufferExt.h"
#include <gtest/gtest.h>

#include <numeric>

TEST(CircularBufferExtConstructorTests, DefaultConstructor) {
    CCircularBufferExt<int> buffer;
    EXPECT_TRUE(buffer.empty());
    EXPECT_EQ(buffer.size(), 0);
    EXPECT_EQ(buffer.capacity(), 0);
}

TEST(CircularBufferExtConstructorTests, ConstructorWithCapacity) {
    size_t capacity = 10;
    CCircularBufferExt<int> buffer(capacity);
    EXPECT_EQ(buffer.size(), 0);
    EXPECT_EQ(buffer.capacity(), capacity);
    EXPECT_TRUE(buffer.empty());
}

TEST(CircularBufferExtConstructorTests, InitializerListConstructor) {
    CCircularBufferExt<std::string> buffer1({"apple", "banana", "cherry"});
    EXPECT_EQ(buffer1.size(), 3);
    EXPECT_EQ(buffer1.capacity(), 3);
    EXPECT_EQ(buffer1.front(), "apple");
    EXPECT_EQ(buffer1.back(), "cherry");
    std::vector<std::string> expected = {"apple", "banana", "cherry"};
    for (size_t i = 0; i < expected.size(); ++i) {
        EXPECT_EQ(buffer1[i], expected[i]);
    }
    CCircularBufferExt<std::string> buffer2({});
    EXPECT_TRUE(buffer2.empty());
}

TEST(CircularBufferExtConstructorTests, CopyConstructor) {
    CCircularBufferExt<int> buffer1({1, 2, 3, 4, 5});
    CCircularBufferExt<int> buffer2(buffer1);
    EXPECT_EQ(buffer2.size(), buffer1.size());
    EXPECT_EQ(buffer2.capacity(), buffer1.capacity());
    for (int i = 0; i < buffer1.size(); ++i) {
        EXPECT_EQ(buffer2[i], buffer1[i]);
    }
}

TEST(CircularBufferExtConstructorTests, FillConstructor) {
    const size_t n = 8;
    const int value = 102;
    CCircularBufferExt<int> buffer(n, value);
    ASSERT_EQ(buffer.size(), n);
    ASSERT_EQ(buffer.capacity(), n);
    for (int i = 0; i < n; i++) {
        ASSERT_EQ(buffer[i], value);
    }
}

TEST(CircularBufferExtConstructorTests, IteratorConstructor) {
    CCircularBufferExt<int> buffer1({1, 2, 3, 4, 5});
    CCircularBufferExt<int> buffer2(buffer1.begin(), buffer1.end());
    CCircularBufferExt<int> buffer3(buffer1.begin(), buffer1.begin() + 1);
    EXPECT_EQ(buffer1.size(), buffer2.size());
    EXPECT_EQ(buffer1.capacity(), buffer2.size());
    EXPECT_EQ(buffer3.size(), 1);
}

TEST(CircularBufferExtOperatorTests, CopyAssignmentOperator) {
    CCircularBufferExt<int> buffer1({1, 2, 3, 4, 5});
    CCircularBufferExt<int> buffer2({6, 7, 8});
    buffer2 = buffer1;
    EXPECT_EQ(buffer2.size(), 5);
    EXPECT_EQ(buffer2.capacity(), 5);
    for (int i = 0; i < buffer2.size(); i++) {
        EXPECT_EQ(buffer2[i], i + 1);
    }
}

TEST(CircularBufferExtOperatorTests, AssignInitializerOperator) {
    std::initializer_list<int> il1 = {1, 2, 3};
    std::initializer_list<int> il2 = {4, 5, 6, 7};
    std::initializer_list<int> il3 = {};
    const size_t n = 10;
    CCircularBufferExt<int> buf(n, 0);
    buf = il1;
    EXPECT_EQ(buf.size(), 3);
    EXPECT_EQ(buf.capacity(), 3);
    EXPECT_EQ(buf.front(), 1);
    EXPECT_EQ(buf.back(), 3);
    buf = il2;
    EXPECT_EQ(buf.size(), 4);
    EXPECT_EQ(buf.capacity(), 4);
    EXPECT_EQ(buf.front(), 4);
    EXPECT_EQ(buf.back(), 7);
    buf = il3;
    EXPECT_EQ(buf.size(), 0);
    EXPECT_EQ(buf.capacity(), 0);
}

TEST(CircularBufferExtOperatorTests, EqualityOperator) {
    CCircularBufferExt<int> buffer1 = {1, 2, 3};
    CCircularBufferExt<int> buffer2 = {1, 2, 3};
    CCircularBufferExt<int> buffer3 = {4, 5, 6};
    ASSERT_TRUE(buffer1 == buffer2);
    ASSERT_TRUE(buffer2 != buffer3);
    buffer2 = {1, 2};
    ASSERT_FALSE(buffer1 == buffer2);
    ASSERT_TRUE(buffer1 != buffer2);
}

TEST(CircularBufferExtMethodTests, PushBackTest) {
    CCircularBufferExt<int> buffer1;
    buffer1.push_back(1);
    buffer1.push_back(2);
    buffer1.push_back(3);
    EXPECT_EQ(buffer1.size(), 3);
    EXPECT_EQ(buffer1[0], 1);
    EXPECT_EQ(buffer1[1], 2);
    EXPECT_EQ(buffer1[2], 3);

    buffer1.push_back(4);
    EXPECT_EQ(buffer1.size(), 4);

    EXPECT_EQ(buffer1[0], 1);
    EXPECT_EQ(buffer1[1], 2);
    EXPECT_EQ(buffer1[2], 3);
    EXPECT_EQ(buffer1[3], 4);
    buffer1 = {};
    buffer1.push_back(2);
    EXPECT_EQ(buffer1[0], 2);
}

TEST(CircularBufferExtMethodTests, BackAndFrontTest) {
    CCircularBufferExt<double> buffer;
    EXPECT_EQ(buffer.size(), 0);
    EXPECT_EQ(buffer.capacity(), 0);
    buffer.push_back(1.1);
    buffer.push_back(2.2);
    buffer.push_back(3.3);
    EXPECT_EQ(buffer.size(), 3);
    EXPECT_EQ(buffer.back(), 3.3);
    EXPECT_EQ(buffer.front(), 1.1);
    buffer.push_back(4.4);
    EXPECT_EQ(buffer.back(), 4.4);
    EXPECT_EQ(buffer.front(), 1.1);
    buffer = {7.7};
    EXPECT_EQ(buffer.back(), 7.7);
    EXPECT_EQ(buffer.front(), 7.7);
}

TEST(CircularBufferExtMethodTests, PopBackTest) {
    CCircularBufferExt<std::string> buffer;
    buffer.push_back("Hello");
    buffer.push_back("world");
    buffer.push_back("!");
    buffer.pop_back();
    EXPECT_EQ(buffer.size(), 2);
    EXPECT_EQ(buffer[0], "Hello");
    EXPECT_EQ(buffer[1], "world");
    buffer.push_back("foo");
    buffer.pop_back();
    EXPECT_EQ(buffer.size(), 2);
    EXPECT_EQ(buffer[0], "Hello");
    EXPECT_EQ(buffer[1], "world");
    buffer.pop_back();
    EXPECT_EQ(buffer.size(), 1);
    EXPECT_EQ(buffer[0], "Hello");
    buffer.pop_back();
    EXPECT_TRUE(buffer.empty());
    buffer.pop_back();
    EXPECT_EQ(buffer.size(), 0);
}

TEST(CircularBufferExtMethodTests, SwapTest) {
    CCircularBufferExt<std::string> buffer1(3);
    buffer1.push_back("Hello");
    buffer1.push_back("world");
    buffer1.push_back("!");

    CCircularBufferExt<std::string> buffer2(2);
    buffer2.push_back("Goodbye");
    buffer2.push_back("!");

    buffer1.swap(buffer2);

    EXPECT_EQ(buffer1.size(), 2);
    EXPECT_EQ(buffer1[0], "Goodbye");
    EXPECT_EQ(buffer1[1], "!");

    EXPECT_EQ(buffer2.size(), 3);
    EXPECT_EQ(buffer2[0], "Hello");
    EXPECT_EQ(buffer2[1], "world");
    EXPECT_EQ(buffer2[2], "!");
}

TEST(CircularBufferExtTest, SizeCapacityAndEmptyTest) {
    CCircularBufferExt<std::string> buffer = {"one", "two", "three"};
    EXPECT_EQ(buffer.size(), 3);
    EXPECT_EQ(buffer.capacity(), 3);
    EXPECT_EQ(buffer.empty(), false);

    buffer.push_back("four");
    buffer.push_back("five");
    buffer.push_back("six");

    EXPECT_EQ(buffer.size(), 6);
    EXPECT_EQ(buffer.capacity(), 6);
    EXPECT_EQ(buffer.empty(), false);
    EXPECT_EQ(buffer.capacity(), 6);

    buffer.clear();

    EXPECT_EQ(buffer.size(), 0);
    EXPECT_EQ(buffer.capacity(), 6);
    EXPECT_EQ(buffer.empty(), true);

    buffer.push_back("!");
    EXPECT_EQ(buffer.size(), 1);
    EXPECT_EQ(buffer.capacity(), 6);
    EXPECT_EQ(buffer.empty(), false);
}

TEST(CircularBufferExtInsertTest, InsertTest1) {
    CCircularBufferExt<int> res1{1};
    CCircularBufferExt<int> res2{2, 1};
    CCircularBufferExt<int> res3{3, 2, 1};
    CCircularBufferExt<int> res4{3, 2, 1, 4};
    CCircularBufferExt<int> res5{3, 2, 1, 5, 4};
    CCircularBufferExt<int> res6{3, 2, 6, 1, 5, 4};
    CCircularBufferExt<int> buffer;
    buffer.insert(buffer.begin(), 1);
    EXPECT_EQ(buffer, res1);
    buffer.insert(buffer.begin(), 2);
    EXPECT_EQ(buffer, res2);
    buffer.insert(buffer.begin(), 3);
    EXPECT_EQ(buffer, res3);
    buffer.insert(buffer.end(), 4);
    EXPECT_EQ(buffer, res4);
    buffer.insert(buffer.begin() + 3, 5);
    EXPECT_EQ(buffer, res5);
    buffer.insert(buffer.end() - 3, 6);
    EXPECT_EQ(buffer, res6);
}

TEST(CircularBufferExtInsertTest, InsertTest2) {
    CCircularBufferExt<std::string> res1{"1", "1", "1"};
    CCircularBufferExt<std::string> res2{"1", "1", "1", "2", "2", "2"};
    CCircularBufferExt<std::string> res3{"3", "3", "3", "1", "1", "1", "2", "2", "2"};
    CCircularBufferExt<std::string> buffer1;
    buffer1.insert(buffer1.begin(), 3, "1");
    EXPECT_EQ(buffer1, res1);
    buffer1.insert(buffer1.end(), 3, "2");
    EXPECT_EQ(buffer1, res2);
    buffer1.insert(buffer1.begin(), 3, "3");
    EXPECT_EQ(buffer1, res3);

    CCircularBufferExt<int> buf;
    std::vector<int> vec = {1, 2, 3, 4, 5};
    CCircularBufferExt<int> res5{1, 2, 3, 4, 5};
    buf.insert(buf.begin(), vec.begin(), vec.end());
    EXPECT_EQ(buf, res5);

    CCircularBufferExt<int> buf1;
    buf1.insert(buf1.begin(), {1, 2, 3, 4, 5});
    EXPECT_EQ(buf1, res5);
}

TEST(CircularBufferExtAssignTest, AssignTest) {
    CCircularBufferExt<std::string> buff1 = {"a", "b", "c"};
    CCircularBufferExt<std::string> buff2 = {"hello, ", "world"};
    buff1.assign(buff2.begin(), buff2.end());
    ASSERT_EQ("hello, ", buff1[0]);
    buff1.assign({"proga"});
    ASSERT_EQ("proga", buff1[0]);
    ASSERT_EQ(1, buff1.size());
    buff2.assign(5, "wow");
    ASSERT_EQ("wow", buff2[0]);
    ASSERT_EQ(5, buff2.size());
}

TEST(CircularBufferExtMethods, EraseTest) {
    CCircularBufferExt<int> buffer1 = {1, 2, 3, 4, 5, 6};
    buffer1.erase(buffer1.begin() + 2);
    CCircularBufferExt<int> res = {1, 2, 4, 5, 6};
    ASSERT_TRUE(buffer1 == res);
    buffer1.erase(buffer1.begin() + 1, buffer1.end());
    CCircularBufferExt<int> res2 = {1};
    ASSERT_TRUE(buffer1 == res2);
}

TEST(CircularBufferExtSTL, STLTest) {
    CCircularBufferExt<int> buffer1 = {1, 2, 3, 4, 5, 6};
    auto it = std::find(buffer1.begin(), buffer1.end(), 2);
    ASSERT_EQ(it, buffer1.begin() + 1);

    ASSERT_EQ(std::accumulate(buffer1.begin(), buffer1.end() - 1, 0), 15);
}