#include "chapters.hpp"
#include "testing_utils.hpp"

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

TEST(VIII_ROBOT_IN_A_GRID, BASE_CASE) {
    Vector<VIII::Spot> ans{
        {.x = 0, .y = 0}, {.x = 1, .y = 0}, {.x = 2, .y = 0}, {.x = 3, .y = 0},
        {.x = 3, .y = 1}, {.x = 3, .y = 2}, {.x = 3, .y = 3},
    };

    EXPECT_EQ(ans, VIII::robotInAGrid(VIII::GridInfo{4, 4}));
}

TEST(VIII_ROBOT_IN_A_GRID, BLOCK_DOWN) {
    Vector<VIII::Spot> ans{
        {.x = 0, .y = 0}, {.x = 0, .y = 1}, {.x = 1, .y = 1}, {.x = 2, .y = 1},
        {.x = 3, .y = 1}, {.x = 3, .y = 2}, {.x = 3, .y = 3},
    };
    Vector<VIII::Spot> limits{{.x = 1, .y = 0}};

    EXPECT_EQ(ans, VIII::robotInAGrid(VIII::GridInfo{4, 4}, limits));
}
