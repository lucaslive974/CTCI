#include "chapters.hpp"

#include <gtest/gtest.h>

using namespace CTCI;

TEST(VIII_TRIPLE_STEPS, BASE_CASE) {
    // EXPECT_EQ(VIII::tripleSteps(0), 0);
    EXPECT_EQ(VIII::tripleSteps(1), 1);
    EXPECT_EQ(VIII::tripleSteps(2), 2);
    EXPECT_EQ(VIII::tripleSteps(3), 4);
    EXPECT_EQ(VIII::tripleSteps(4), 7);
    EXPECT_EQ(VIII::tripleSteps(5), 13);
    EXPECT_EQ(VIII::tripleSteps(6), 24);
}

TEST(VIII_TRIPLE_STEPS, GREAT_INPUTS) {
    EXPECT_EQ(VIII::tripleSteps(30), 53'798'080);
    EXPECT_EQ(VIII::tripleSteps(36), 2'082'876'103);
}
