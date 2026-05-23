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

TEST(StackInitList, Size){
    Stack<MutableSequenceArray, int> s {1,2,3,4};
    EXPECT_EQ(s.size(), 4);
    s.push(5);
    EXPECT_EQ(s.size(), 5);
}

TEST(StackInitList, Empty){
    Stack<MutableSequenceArray, int> s {1,2,3,4};
    EXPECT_FALSE(s.empty());
}

TEST(StackInitList, PushandPop){
    Stack<MutableSequenceArray, int> s {1,2,3,4};
    EXPECT_EQ(s.pop(), 4);
    EXPECT_EQ(s.pop(), 3);
    EXPECT_EQ(s.pop(), 2);
}

TEST(StackInitList, PushandTop){
    Stack<MutableSequenceArray, int> s {1,2,3,4};
    EXPECT_EQ(s.top(), 4);
    s.pop();
    EXPECT_EQ(s.top(), 3);
    s.pop();
    EXPECT_EQ(s.top(), 2);
}

TEST(StackIterator,  range_based){
    int i = 1;
    Stack<MutableSequenceArray, int> s {1,2,3,4};
    for(auto item : s){
        EXPECT_EQ(item, i++);
    }
}

TEST(StackFunctional, Map){
    Stack<MutableSequenceArray, int> s{1, 2, 3};
    auto m = s.map([](int x) { return x * 10; });
    EXPECT_EQ(m.pop(), 30);
    EXPECT_EQ(m.pop(), 20);
    EXPECT_EQ(m.pop(), 10);
}

TEST(StackFunctional, Were){
    Stack<MutableSequenceArray, int> s{1 , 2 , 3 , 4 , 5 , 6};
    auto w = s.were([](int x) { return x % 2 == 0;});
    EXPECT_EQ(w.size(), 3);
    EXPECT_EQ(w.pop(), 6);
    EXPECT_EQ(w.pop(), 4);
    EXPECT_EQ(w.pop(), 2);
}