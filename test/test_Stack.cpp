#include <gtest/gtest.h>
#include <cstdint>
#include "Stack.hpp"
#include "MutableSequenceArray.hpp"

TEST(StackBasic, PushandPop){
    Stack<MutableSequenceArray, int> s;
    s.push(1);
    s.push(2);
    s.push(3);
    EXPECT_EQ(s.pop(), 3);
    EXPECT_EQ(s.pop(), 2);
    EXPECT_EQ(s.pop(), 1);
}

TEST(StackBasic, PushandTop){
    Stack<MutableSequenceArray, int> s;
    s.push(1);
    EXPECT_EQ(s.top(), 1);
    s.push(2);
    EXPECT_EQ(s.top(), 2);
    s.push(3);
    EXPECT_EQ(s.top(), 3);
}


TEST(StackBasic, Empty){
    Stack<MutableSequenceArray, int> s;
    EXPECT_TRUE(s.empty());
}

TEST(StackBasic, Size){
    Stack<MutableSequenceArray, int> s;
    EXPECT_EQ(s.size(), 0);
    s.push(1);
    EXPECT_EQ(s.size(), 1);
    s.push(2);
    EXPECT_EQ(s.size(), 2);
}