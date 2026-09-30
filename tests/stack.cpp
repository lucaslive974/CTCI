#include "chapters.hpp"
#include <gtest/gtest.h>

using StackInt = CTCI::Stack<int>;

TEST(STACK, POP) {
    StackInt stack{1, 2, 3};

    auto get = [&stack]() -> int {
        int val = stack.peek();
        stack.pop();
        return val;
    };

    EXPECT_EQ(get(), 3);
    EXPECT_EQ(get(), 2);
    EXPECT_EQ(get(), 1);
}

TEST(STACK, PUSH) {
    StackInt stack;

    stack.push(0);
    EXPECT_EQ(stack.peek(), 0);
    stack.push(1);
    EXPECT_EQ(stack.peek(), 1);
}

TEST(STACK, EMPTY) {
    StackInt stack;

    EXPECT_TRUE(stack.empty());

    stack.push(0);
    EXPECT_FALSE(stack.empty());

    stack.pop();
    EXPECT_TRUE(stack.empty());
}

TEST(STACK, SIZE) {
    StackInt stack{0, 2, 3};

    EXPECT_EQ(stack.size(), 3);
}
