#include "chapters.hpp"
#include "testing_utils.hpp"
#include <gtest/gtest.h>

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