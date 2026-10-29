#include "deque.hpp"

#include <gtest/gtest.h>

/* Deque Tests */
TEST(DEQUE, INITIALIZATION) {
    CTCI::Deque<int> deque{1, 2, 3};

    auto elOne = deque.head;
    auto elTwo = elOne->next;
    auto elThree = elTwo->next;

    EXPECT_EQ(elOne->prev, nullptr);
    EXPECT_EQ(elOne->next, elTwo);
    EXPECT_EQ(elTwo->prev, elOne);
    EXPECT_EQ(elTwo->next, elThree);
    EXPECT_EQ(elThree->prev, elTwo);
    EXPECT_EQ(elThree->next, nullptr);
}

TEST(DEQUE, INIT_EMPTY) {
    CTCI::Deque<int> deque;

    EXPECT_EQ(deque.head, nullptr);
    EXPECT_EQ(deque.tail, nullptr);
}

TEST(DEQUE, POP_FRONT) {
    CTCI::Deque<int> deque{1};

    EXPECT_NE(deque.head, nullptr);

    deque.popFront();
    EXPECT_EQ(deque.head, nullptr);
    EXPECT_EQ(deque.tail, nullptr);
}

TEST(DEQUE, POP_BACK) {
    CTCI::Deque<int> deque{2};

    EXPECT_NE(deque.tail, nullptr);

    deque.popBack();
    EXPECT_EQ(deque.head, nullptr);
    EXPECT_EQ(deque.tail, nullptr);
}

TEST(DEQUE, POP_MIDDLE) {
    CTCI::Deque<int> deque{1, 2, 3};

    auto node = deque.head->next;
    deque.popMiddle(node);

    EXPECT_EQ(deque.head->val, 1);
    EXPECT_EQ(deque.head->next->val, 3);
    EXPECT_EQ(deque.head->next->next, nullptr);
}

TEST(DEQUE, POP_HEAD_NODE) {
    CTCI::Deque<int> deque{1, 2, 3};

    deque.pop(deque.head);
    EXPECT_EQ(deque.head->val, 2);
    EXPECT_EQ(deque.tail->val, 3);
    EXPECT_EQ(deque.head->prev, nullptr);
}

TEST(DEQUE, POP_TAIL_NODE) {
    CTCI::Deque<int> deque{2, 4};

    deque.pop(deque.tail);
    EXPECT_EQ(deque.head->next, nullptr);
}

TEST(DEQUE, POP_MIDDLE_NODE) {
    CTCI::Deque<int> deque{1, 2, 3, 4};

    deque.pop(deque.head->next->next); // 3
    EXPECT_EQ(deque.head->next->next->val, 4);
}

TEST(DEQUE, EMPTY) {
    CTCI::Deque<int> deque{2, 3, 4};

    deque.popFront();
    deque.popFront();
    deque.popBack();

    EXPECT_TRUE(deque.empty());
}

TEST(DEQUE, FOR_RANGE_LOOP) {
    const CTCI::Deque<int> deque{0, 1, 2};

    for (auto [q, v] : std::views::zip(deque, std::views::iota(0, 3)))
        EXPECT_EQ(q, v);
}
