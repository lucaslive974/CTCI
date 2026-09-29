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

    list.append(5);
    EXPECT_FALSE(list.empty());
}

TEST(COMMON, LIST_APPEND_ITENS) {
    CTCI::List<int> list;

    list.append(5);
    EXPECT_EQ(list.head->val, 5);

    list.append(4);
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

TEST(COMMON, LIST_APPEND_EXPIRING_LIST) {
    CTCI::List<int> a{1, 2, 3};
    CTCI::List<int> b{4, 5, 6};
    CTCI::List<int> ans{1, 2, 3, 4, 5, 6};

    a.append(std::move(b));
    internal::testListIsEqual(a, ans);

    EXPECT_EQ(b.head, nullptr);
    EXPECT_EQ(b.tail, nullptr);
}

TEST(COMMON, LIST_FRONT) {
    CTCI::List<int> a{3, 2, 1};
    a.pop();
    EXPECT_EQ(a.front()->val, 2);
}

TEST(COMMON, LIST_POP) {
    CTCI::List<int> a{3, 2, 1};

    for (size_t i = 0; i < 3; ++i)
        a.pop();

    EXPECT_EQ(a.front(), nullptr);
}

/* Deque Tests */
TEST(COMMON, DEQUE_INITIALIZATION) {
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

TEST(COMMON, DEQUE_INIT_EMPTY) {
    CTCI::Deque<int> deque;

    EXPECT_EQ(deque.head, nullptr);
    EXPECT_EQ(deque.tail, nullptr);
}

TEST(COMMON, DEQUE_POP_FRONT) {
    CTCI::Deque<int> deque{1};

    EXPECT_NE(deque.head, nullptr);

    deque.popFront();
    EXPECT_EQ(deque.head, nullptr);
    EXPECT_EQ(deque.tail, nullptr);
}

TEST(COMMON, DEQUE_POP_BACK) {
    CTCI::Deque<int> deque{2};

    EXPECT_NE(deque.tail, nullptr);

    deque.popBack();
    EXPECT_EQ(deque.head, nullptr);
    EXPECT_EQ(deque.tail, nullptr);
}

TEST(COMMON, DEQUE_POP_MIDDLE) {
    CTCI::Deque<int> deque{1, 2, 3};

    auto node = deque.head->next;
    deque.popMiddle(node);

    EXPECT_EQ(deque.head->val, 1);
    EXPECT_EQ(deque.head->next->val, 3);
    EXPECT_EQ(deque.head->next->next, nullptr);
}

TEST(COMMON, DEQUE_POP_HEAD_NODE) {
    CTCI::Deque<int> deque{1, 2, 3};

    deque.pop(deque.head);
    EXPECT_EQ(deque.head->val, 2);
    EXPECT_EQ(deque.tail->val, 3);
    EXPECT_EQ(deque.head->prev, nullptr);
}

TEST(COMMON, DEQUE_POP_TAIL_NODE) {
    CTCI::Deque<int> deque{2, 4};

    deque.pop(deque.tail);
    EXPECT_EQ(deque.head->next, nullptr);
}

TEST(COMMON, DEQUE_POP_MIDDLE_NODE) {
    CTCI::Deque<int> deque{1, 2, 3, 4};

    deque.pop(deque.head->next->next); // 3
    EXPECT_EQ(deque.head->next->next->val, 4);
}

TEST(COMMON, DEQUE_EMPTY) {
    CTCI::Deque<int> deque{2, 3, 4};

    deque.popFront();
    deque.popFront();
    deque.popBack();

    EXPECT_TRUE(deque.empty());
}