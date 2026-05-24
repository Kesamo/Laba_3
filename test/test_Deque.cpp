#include <gtest/gtest.h>
#include <string>
#include "Deque/Deque.hpp"
#include "Deque/DequeAliases.hpp"

TEST(DequeBasic, PushandPop_1){
    ArrayDeque<int> d;
    d.push_back(1);
    d.push_back(2);
    d.push_back(3);
    EXPECT_EQ(d.pop_back(), 3);
    EXPECT_EQ(d.pop_back(), 2);
    EXPECT_EQ(d.size(), 1);
}

TEST(DequeBasic, PushandPop_2){
    ListDeque<int> d;
    d.push_front(1);
    d.push_front(2);
    d.push_front(3);
    EXPECT_EQ(d.pop_front(), 3);
    EXPECT_EQ(d.pop_front(), 2);
    EXPECT_EQ(d.size(), 1);
}

TEST(DequeBasic, PushandPop_3){
    ArrayDeque<int> d;
    d.push_back(1);
    d.push_front(0);
    d.push_back(2);
    EXPECT_EQ(d.front(), 0);
    EXPECT_EQ(d.back(), 2);
    EXPECT_EQ(d.pop_front(), 0);
    EXPECT_EQ(d.pop_back(), 2);
    EXPECT_EQ(d.size(), 1);
}

TEST(DequeInitList, Size){
    ArrayDeque<int> d{1, 2, 3};
    EXPECT_EQ(d.size(), 3);
    EXPECT_EQ(d.front(), 1);
    EXPECT_EQ(d.back(), 3);
}

TEST(DequeFunctional, Map){
    ArrayDeque<int> d{1, 2, 3};
    auto m = d.map([](int x) { return x * 10; });
    EXPECT_EQ(m.pop_front(), 10);
    EXPECT_EQ(m.pop_front(), 20);
    EXPECT_EQ(m.pop_front(), 30);
    EXPECT_TRUE(m.empty());
}

TEST(DequeFunctional, Where){
    ListDeque<int> d{1, 2, 3, 4, 5, 6};
    auto w = d.where([](int x) { return x % 2 == 0;});
    EXPECT_EQ(w.size(), 3);
    EXPECT_EQ(w.pop_front(), 2);
    EXPECT_EQ(w.pop_front(), 4);
    EXPECT_EQ(w.pop_front(), 6);
}

TEST(DequeFunctional, Reduce){
    ArrayDeque<int> d{1, 2, 3, 4};
    int sum = d.reduce([](int a, int b) { return a + b;}, 0);
    EXPECT_EQ(sum, 10);
}

TEST(DequeOps, Concat) {
    ListDeque<int> a{1, 2};
    ListDeque<int> b{3, 4};
    auto ab = a.Concat(b);
    EXPECT_EQ(ab.size(), 4);
    EXPECT_EQ(ab.pop_front(), 1);
    EXPECT_EQ(ab.pop_back(), 4);
}

TEST(DequeOps, GetSubsequence) {
    ArrayDeque<int> d{1, 2, 3, 4, 5};
    auto sub = d.GetSubsequence(1, 3);
    EXPECT_EQ(sub.size(), 3);
    EXPECT_EQ(sub.pop_front(), 2);
    EXPECT_EQ(sub.pop_back(), 4);
}

TEST(DequeOps, SubsequenceBadRangeThrows) {
    ArrayDeque<int> d{1, 2, 3};
    EXPECT_THROW(d.GetSubsequence(3, 1), InvalidRangeException);
    EXPECT_THROW(d.GetSubsequence(0, 10), InvalidRangeException);
}