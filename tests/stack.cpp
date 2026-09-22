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

    EXPECT_TRUE(stack.isEmpty());

    stack.push(0);
    EXPECT_FALSE(stack.isEmpty());

    stack.pop();
    EXPECT_TRUE(stack.isEmpty());
}

TEST(STACK, SIZE) {
    StackInt stack{0, 2, 3};

    EXPECT_EQ(stack.size(), 3);
}

using StacksInt = CTCI::SetOfStacks<int>;

TEST(SET_OF_STACKS, PUSH) {
    StacksInt stacks(/*threshold=*/3);

    stacks.push({1, 2, 3});
    EXPECT_EQ(stacks.numberOfStacks(), 1);

    stacks.push(4);
    EXPECT_EQ(stacks.numberOfStacks(), 2);
}

TEST(SET_OF_STACKS, POP) {
    StacksInt stacks(/*list=*/{1, 2, 3, 4, 5}, /*threshold=*/3);
    EXPECT_EQ(stacks.numberOfStacks(), 2);

    stacks.pop();
    EXPECT_EQ(stacks.numberOfStacks(), 2);

    stacks.pop();
    EXPECT_EQ(stacks.numberOfStacks(), 1);
}

TEST(SET_OF_STACKS, SIZE) {
    StacksInt stacks({1, 2, 3, 4, 5, 6});
    EXPECT_EQ(stacks.size(), 6);
}

TEST(SET_OF_STACKS, SIZE_AT) {
    StacksInt stacks({1, 2, 3, 4}, 2);
    stacks.popAt(0);

    EXPECT_EQ(stacks.sizeAt(0), 1);
}

TEST(SET_OF_STACKS, PEEK) {
    StacksInt stacks{1, 2, 3, 4};
    EXPECT_EQ(stacks.peek(), 4);

    stacks.push({5, 6});
    EXPECT_EQ(stacks.peek(), 6);
}

TEST(SET_OF_STACKS, PEEK_AT) {
    StacksInt stacks{{1, 2, 3, 4, 5, 6}, 3};
    stacks.popAt(0);

    EXPECT_EQ(stacks.peekAt(0), 2);
    EXPECT_EQ(stacks.size(), 5);
}

TEST(SET_OF_STACKS, POP_AT) {
    StacksInt stacks{{1, 2, 3, 4, 5, 6}, 3};
    stacks.popAt(0);

    EXPECT_EQ(stacks.peek(), 6);
    EXPECT_EQ(stacks.size(), 5);
}

TEST(SET_OF_STACKS, EMPTY_STACKS_ON_MIDDLE_AMORTIZED) {
    StacksInt stacks{{1, 2, 3}, 1};
    EXPECT_EQ(stacks.numberOfStacks(), 3);

    stacks.popAt(1);
    EXPECT_EQ(stacks.numberOfStacks(), 2);

    stacks.pop();
    EXPECT_EQ(stacks.peek(), 1);
    EXPECT_EQ(stacks.numberOfStacks(), 1);
}

TEST(SET_OF_STACKS, EMPTY_STACK_ON_MIDDLE) {
    StacksInt stacks{{1, 2, 3}, 1};

    stacks.popAt(1);
    EXPECT_EQ(stacks.numberOfStacks(), 2);
}

TEST(SET_OF_STACKS, EMPTY_STACK_ON_END) {
    StacksInt stacks{{1, 2, 3}, 1};

    stacks.pop();
    EXPECT_EQ(stacks.numberOfStacks(), 2);
}

TEST(SET_OF_STACKS, IS_EMPTY_TRUE) {
    StacksInt stacks;
    EXPECT_TRUE(stacks.isEmpty());
}

TEST(SET_OF_STACKS, IS_EMPTY_FALSE) {
    StacksInt stacks{1, 2};
    EXPECT_FALSE(stacks.isEmpty());
}

TEST(SET_OF_STACKS, IS_EMPTY_TWO_STACKS) {
    StacksInt stacks{{1, 2}, 1};

    stacks.popAt(0);
    EXPECT_FALSE(stacks.isEmpty());

    stacks.pop();
    EXPECT_TRUE(stacks.isEmpty());
}