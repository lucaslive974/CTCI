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

TEST(VIII_ROBOT_IN_A_GRID, SPOT_COMPARISON) {
    VIII::Spot a{.x = 0, .y = 0};
    VIII::Spot b{.x = 0, .y = 0};
    VIII::Spot c{.x = 1, .y = 0};
    VIII::Spot d{.x = 0, .y = 1};

    EXPECT_EQ(a, b);
    EXPECT_NE(a, c);
    EXPECT_NE(a, d);
    EXPECT_NE(c, d);
}

TEST(VIII_ROBOT_IN_A_GRID, BLOCK_DOWN) {
    Vector<VIII::Spot> ans{
        {.x = 0, .y = 0}, {.x = 0, .y = 1}, {.x = 1, .y = 1}, {.x = 2, .y = 1},
        {.x = 3, .y = 1}, {.x = 3, .y = 2}, {.x = 3, .y = 3},
    };
    Vector<VIII::Spot> limits{{.x = 1, .y = 0}};

    EXPECT_EQ(ans, VIII::robotInAGrid(VIII::GridInfo{4, 4}, limits));
}

TEST(VIII_ROBOT_IN_A_GRID, X_AXIS_SHOULD_NOT_OVERFLOW) {
    Vector<VIII::Spot> limits{{.x = 0, .y = 1}, {.x = 1, .y = 1}, {.x = 2, .y = 1}, {.x = 3, .y = 1}};

    auto ans = VIII::robotInAGrid(
        VIII::GridInfo{
            .rowSize = 4,
            .colSize = 4,
        },
        limits);

    EXPECT_TRUE(ans.empty());
}

TEST(VIII_ROBOT_IN_A_GRID, Y_AXIS_SHOULD_NOT_OVERFLOW) {
    Vector<VIII::Spot> limits{{.x = 1, .y = 0}, {.x = 1, .y = 1}, {.x = 1, .y = 2}, {.x = 1, .y = 3}};

    auto ans = VIII::robotInAGrid(
        VIII::GridInfo{
            .rowSize = 4,
            .colSize = 4,
        },
        limits);

    EXPECT_TRUE(ans.empty());
}

TEST(VIII_ROBOT_IN_A_GRID, WITHOUT_A_VALID_PATH_SHOULD_RETURN_EMPTY) {
    Vector<VIII::Spot> limits{{.x = 0, .y = 1}, {.x = 1, .y = 0}};
    auto ans = VIII::robotInAGrid(VIII::GridInfo{.rowSize = 4, .colSize = 4}, limits);
    EXPECT_TRUE(ans.empty());
}

TEST(VIII_FIND_MAGIC_INDEX, MIDDLE_ELEMENT) {
    Vector<int> arr{0, 1, 2, 3, 4};
    EXPECT_EQ(VIII::magicIndex(arr), 2);
}

TEST(VIII_FIND_MAGIC_INDEX, LEFT_SIDE_SEARCH) {
    Vector<int> arr{-1, 1, 3, 4, 5};
    EXPECT_EQ(VIII::magicIndex(arr), 1);
}

TEST(VIII_FIND_MAGIC_INDEX, RIGHT_SIDE_SEARCH) {
    Vector<int> arr{-1, 0, 1, 3, 5};
    EXPECT_EQ(VIII::magicIndex(arr), 3);
}

TEST(VIII_FIND_MAGIC_INDEX, LEFT_SIDE_SHOULD_NOT_ENTER_IN_LOOP) {
    Vector<int> arr{1, 2, 3, 4, 5};
    EXPECT_EQ(VIII::magicIndex(arr), -1);
}

TEST(VIII_FIND_MAGIC_INDEX, NO_MAGIC_INDEX_ON_ARRY_SHOULD_RETURN_MINUS_ONE) {
    Vector<int> arr{-1, 0, 1, 2, 3};
    EXPECT_EQ(VIII::magicIndex(arr), -1);
}

TEST(VIII_FIND_MAGIC_INDEX, RIGHT_SIDE_SHOULD_NOT_OVERFLOW_SIZE) {
    Vector<int> arr{-1, 0, 1, 2, 3};
    EXPECT_EQ(VIII::magicIndex(arr), -1);
}

TEST(VIII_POWER_SET, BASE_CASE) {
    // clang-format off
    Vector<UnorderedSet<int>> exp = {
        {},   
        {1},
        {1, 2}, 
        {1, 2, 3}, 
        {1, 2, 3, 4},

        {1, 2, 4}, 

        {1, 3}, 
        {1, 3, 4},

        {1, 4}, 
        
        {2},
        {2, 3},
        {2, 3, 4},
        
        {2, 4},
        
        {3},
        {3, 4}, 
        
        {4},
    };
    // clang-format on

    UnorderedSet<int> set{1, 2, 3, 4};
    auto ans = VIII::powerSet(set);

    for (auto [setA, setB] : std::views::zip(ans, exp)) {
        EXPECT_EQ(setA.size(), setB.size());

        for (const auto &val : setA)
            EXPECT_TRUE(setB.contains(val));
    }
}

TEST(VIII_RECURSIVE_MULTIPLY, BASE_CASE) {
    EXPECT_EQ(VIII::recursiveMultiply(2, 2), 4);

    EXPECT_EQ(VIII::recursiveMultiply(3, 2), 6);
    EXPECT_EQ(VIII::recursiveMultiply(3, 3), 9);

    EXPECT_EQ(VIII::recursiveMultiply(4, 2), 8);
}

TEST(VIII_RECURSIVE_MULTIPLY, MULTIPLY_BY_ONE) { EXPECT_EQ(VIII::recursiveMultiply(3, 1), 3); }

TEST(VIII_RECURSIVE_MULTIPLY, MULTIPLY_BY_ZERO) { EXPECT_EQ(VIII::recursiveMultiply(3, 0), 0); }
