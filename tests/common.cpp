#include "chapter.hpp"
#include "chapters.hpp"
#include "testing_utils.hpp"
#include "utils.hpp"
#include "gtest/gtest.h"

TEST(COMMON, CHAPTER_NAME_ATTR) {
    Chapter chapter{"Test Chapter"};

    EXPECT_EQ(chapter.name(), "Test Chapter");
}

TEST(COMMON, CHAPTER_IX_NAME) {
    CTCI::IX chapter;

    EXPECT_EQ(chapter.name(), "CTCI::IX::Exercises");
}

TEST(COMMON, LIST_INITIALIZER_LIST_INIT) {
    CTCI::List<int> list{0, 1, 2, 3, 4};

    EXPECT_FALSE(list.empty());

    auto head = list.head;
    for (size_t i = 0; i < 5; ++i) {
        EXPECT_EQ(head->val, i);
        head = head->next;
    }
}

TEST(COMMON, LIST_INITIALIZE_VECTOR_INIT) {
    std::vector<int> vec{5, 4, 3, 2, 1};
    CTCI::List<int> list{vec};

    auto head = list.head;
    for (int val : vec) {
        EXPECT_EQ(head->val, val);
        head = head->next;
    }
}

TEST(COMMON, LIST_EMPTY) {
    CTCI::List<int> list;

    EXPECT_TRUE(list.empty());

    list.appendToTail(5);
    EXPECT_FALSE(list.empty());
}

TEST(COMMON, LIST_APPEND_ITENS) {
    CTCI::List<int> list;

    list.appendToTail(5);
    EXPECT_EQ(list.head->val, 5);

    list.appendToTail(4);
    EXPECT_EQ(list.head->next->val, 4);
}

TEST(COMMON, LIST_COPY_INITIALIZER) {
    CTCI::List<int> a{1, 2, 3};
    CTCI::List<int> b;

    // Assignment operator
    b = a;

    EXPECT_NE(&b.head, &a.head);
    internal::testListIsEqual(a, b);
}

TEST(COMMON, LIST_MOVE_INITIALIZER) {
    CTCI::List<int> a{1, 2, 3, 4, 5};
    CTCI::List<int> b = std::move(a);

    EXPECT_EQ(a.head, nullptr);
    EXPECT_EQ(a.tail, nullptr);

    EXPECT_EQ(b.head->val, 1);
    EXPECT_EQ(b.tail->val, 5);
}

TEST(COMMON, LIST_REVERT) {
    CTCI::List<int> a{1, 2, 3, 4, 5};
    CTCI::List<int> b{5, 4, 3, 2, 1};

    CTCI::revertLinkedList(a);

    internal::testListIsEqual(a, b);
}

TEST(COMMON, LIST_REVERT_EMPTY) {
    CTCI::List<int> a;
    EXPECT_NO_THROW(CTCI::revertLinkedList(a));
}

using StackInt = CTCI::Stack<int>;

TEST(COMMON, STACK_POP) {
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

TEST(COMMON, STACK_PUSH) {
    StackInt stack;

    stack.push(0);
    EXPECT_EQ(stack.peek(), 0);
    stack.push(1);
    EXPECT_EQ(stack.peek(), 1);
}

TEST(COMMON, STACK_EMPTY) {
    StackInt stack;

    EXPECT_TRUE(stack.isEmpty());

    stack.push(0);
    EXPECT_FALSE(stack.isEmpty());

    stack.pop();
    EXPECT_TRUE(stack.isEmpty());
}

TEST(COMMON, STACK_SIZE) {
    StackInt stack{0, 2, 3};

    EXPECT_EQ(stack.size(), 3);
}

using StacksInt = CTCI::SetOfStacks<int>;

TEST(COMMON, SET_OF_STACKS_PUSH) {
    StacksInt stacks(/*threshold=*/3);

    stacks.push({1, 2, 3});
    EXPECT_EQ(stacks.numberOfStacks(), 1);

    stacks.push(4);
    EXPECT_EQ(stacks.numberOfStacks(), 2);
}

TEST(COMMON, SET_OF_STACKS_POP) {
    StacksInt stacks(/*list=*/{1, 2, 3, 4, 5}, /*threshold=*/3);
    EXPECT_EQ(stacks.numberOfStacks(), 2);

    stacks.pop();
    EXPECT_EQ(stacks.numberOfStacks(), 2);

    stacks.pop();
    EXPECT_EQ(stacks.numberOfStacks(), 1);
}

TEST(COMMON, SET_OF_STACKS_SIZE) {
    StacksInt stacks({1, 2, 3, 4, 5, 6});
    EXPECT_EQ(stacks.size(), 6);
}

TEST(COMMON, SET_OF_STACKS_SIZE_AT) {
    StacksInt stacks({1, 2, 3, 4}, 2);
    stacks.popAt(0);

    EXPECT_EQ(stacks.sizeAt(0), 1);
}

TEST(COMMON, SET_OF_STACKS_PEEK) {
    StacksInt stacks{1, 2, 3, 4};
    EXPECT_EQ(stacks.peek(), 4);

    stacks.push({5, 6});
    EXPECT_EQ(stacks.peek(), 6);
}

TEST(COMMON, SET_OF_STACKS_PEEK_AT) {
    StacksInt stacks{{1, 2, 3, 4, 5, 6}, 3};
    stacks.popAt(0);

    EXPECT_EQ(stacks.peekAt(0), 2);
    EXPECT_EQ(stacks.size(), 5);
}

TEST(COMMON, SET_OF_STACKS_POP_AT) {
    StacksInt stacks{{1, 2, 3, 4, 5, 6}, 3};
    stacks.popAt(0);

    EXPECT_EQ(stacks.peek(), 6);
    EXPECT_EQ(stacks.size(), 5);
}

TEST(COMMON, SET_OF_STACKS_EMPTY_STACKS_ON_MIDDLE_AMORTIZED) {
    StacksInt stacks{{1, 2, 3}, 1};

    stacks.popAt(1);
    stacks.pop();

    EXPECT_EQ(stacks.peek(), 1);
    EXPECT_EQ(stacks.numberOfStacks(), 1);
}

TEST(COMMON, SET_OF_STACKS_EMPTY_STACK_ON_MIDDLE) {
    StacksInt stacks{{1, 2, 3}, 1};

    stacks.popAt(1);
    EXPECT_EQ(stacks.numberOfStacks(), 2);
}

TEST(COMMON, SET_OF_STACKS_EMPTY_STACK_ON_END) {
    StacksInt stacks{{1, 2, 3}, 1};

    stacks.pop();
    EXPECT_EQ(stacks.numberOfStacks(), 2);
}

TEST(UTILS, PrintTitleOutputsFormattedMessage) {
    testing::internal::CaptureStdout();

    CTCI::utils::printTitle("Chapter Test");

    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "[Chapter Test]\n");
}

TEST(UTILS, BreakLineOutputsNewLine) {
    testing::internal::CaptureStdout();

    CTCI::utils::breakLine();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "\n");
}
