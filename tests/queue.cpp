#include "chapters.hpp"
#include <gtest/gtest.h>

using QueueInt = CTCI::Queue<int>;

TEST(QUEUE, INITIALIZATION) {
    QueueInt queue{5, 4, 3, 2, 1};

    EXPECT_EQ(queue.front(), 5);
}

TEST(QUEUE, PUSH) {
    QueueInt queue{4, 2, 1};

    queue.push(3);
    for (size_t i = 0; i < 3; ++i)
        queue.pop();

    EXPECT_EQ(queue.front(), 3);
}

TEST(QUEUE, POP) {
    QueueInt queue{5, 3, 1};

    queue.pop();
    EXPECT_EQ(queue.front(), 3);
}

TEST(QUEUE, EMPTY) {
    QueueInt queue{5, 2};

    EXPECT_FALSE(queue.isEmpty());

    for (size_t i = 0; i < 2; ++i)
        queue.pop();

    EXPECT_TRUE(queue.isEmpty());
}
