#include "list.hpp"
#include "testing_utils.hpp"

#include <gtest/gtest.h>

TEST(LIST, INITIALIZER_LIST_INIT) {
    CTCI::List<int> list{0, 1, 2, 3, 4};

    EXPECT_FALSE(list.empty());

    auto head = list.head;
    for (size_t i = 0; i < 5; ++i) {
        EXPECT_EQ(head->val, i);
        head = head->next;
    }
}

TEST(LIST, INITIALIZE_VECTOR_INIT) {
    CTCI::Vector<int> vec{5, 4, 3, 2, 1};
    CTCI::List<int> list{vec};

    auto head = list.head;
    for (int val : vec) {
        EXPECT_EQ(head->val, val);
        head = head->next;
    }
}

TEST(LIST, EMPTY) {
    CTCI::List<int> list;

    EXPECT_TRUE(list.empty());

    list.push(5);
    EXPECT_FALSE(list.empty());
}

TEST(LIST, APPEND_ITENS) {
    CTCI::List<int> list;

    list.push(5);
    EXPECT_EQ(list.head->val, 5);

    list.push(4);
    EXPECT_EQ(list.head->next->val, 4);
}

TEST(LIST, COPY_INITIALIZER) {
    CTCI::List<int> a{1, 2, 3};
    CTCI::List<int> b;

    // Assignment operator
    b = a;

    EXPECT_NE(&b.head, &a.head);
    internal::testListIsEqual(a, b);
}

TEST(LIST, MOVE_INITIALIZER) {
    CTCI::List<int> a{1, 2, 3, 4, 5};
    CTCI::List<int> b = std::move(a);

    EXPECT_EQ(a.head, nullptr);
    EXPECT_EQ(a.tail, nullptr);

    EXPECT_EQ(b.head->val, 1);
    EXPECT_EQ(b.tail->val, 5);
}

TEST(LIST, REVERT) {
    CTCI::List<int> a{1, 2, 3, 4, 5};
    CTCI::List<int> b{5, 4, 3, 2, 1};

    CTCI::revertLinkedList(a);

    internal::testListIsEqual(a, b);
}

TEST(LIST, REVERT_EMPTY) {
    CTCI::List<int> a;
    EXPECT_NO_THROW(CTCI::revertLinkedList(a));
}

TEST(LIST, APPEND_EXPIRING_LIST) {
    CTCI::List<int> a{1, 2, 3};
    CTCI::List<int> b{4, 5, 6};
    CTCI::List<int> ans{1, 2, 3, 4, 5, 6};

    a.push(std::move(b));
    internal::testListIsEqual(a, ans);

    EXPECT_EQ(b.head, nullptr);
    EXPECT_EQ(b.tail, nullptr);
}

TEST(LIST, FRONT) {
    CTCI::List<int> a{3, 2, 1};
    a.pop();
    EXPECT_EQ(a.front(), 2);
}

TEST(LIST, POP) {
    CTCI::List<int> a{3, 2, 1};

    for (size_t i = 0; i < 2; ++i)
        a.pop();

    EXPECT_EQ(a.front(), 1);

    a.pop();
    EXPECT_TRUE(a.empty());
}

TEST(LIST, EMPTY_SIZE) {
    CTCI::List<int> a;
    EXPECT_EQ(a.size, 0);
}

TEST(LIST, SIZE) {
    CTCI::List<int> a{5, 4, 3, 2, 1};

    EXPECT_EQ(a.size, 5);

    a.pop();
    EXPECT_EQ(a.size, 4);
}

TEST(LIST, APPEND_SIZE) {
    CTCI::List<int> a{1, 2, 3};
    CTCI::List<int> b{4, 5, 6};

    a.push(std::move(b));

    EXPECT_EQ(a.size, 6);
    EXPECT_EQ(b.size, 0);
}
