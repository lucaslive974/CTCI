#include "chapters.hpp"

#include <gtest/gtest.h>

using CTCI::V;

TEST(V_INSERTION, BASE_CASE) {
    auto info = V::InsertionData{.M = 0b1'0011, .N = 0b100'0000'0000, .i = 2, .j = 6};
    EXPECT_EQ(V::insertion(info), 0b100'0100'1100);
}

TEST(V_INSERTION, EXISTENT_DATA_ON_INPUT_SHOULD_BE_OVERWRITTED) {
    auto info = V::InsertionData{.M = 0b1'0011, .N = 0b100'0111'1100, .i = 2, .j = 6};
    EXPECT_EQ(V::insertion(info), 0b100'0100'1100);
}

TEST(V_FLIP_BIT_TO_WIN, BASE_CASE) {
    EXPECT_EQ(V::flipBitToWin(0b110'1110'1111), 8);
    EXPECT_EQ(V::flipBitToWin(0b1101), 4);
}

TEST(V_FLIP_BIT_TO_WIN, ALL_ONES_EQUAL_TO_BIT_SIZE_PLUS_ONE) { EXPECT_EQ(V::flipBitToWin(0b1111'1111), 9); }

TEST(V_FLIP_BIT_TO_WIN, FIRST_SEQUENCE_SHOULD_BE_GREATER) { EXPECT_EQ(V::flipBitToWin(0b1011'0011), 4); }

TEST(V_FLIP_BIT_TO_WIN, ALL_ZEROS_EQUAL_TO_ONE) { EXPECT_EQ(V::flipBitToWin(0b0000'0000), 1); }

TEST(V_FLIP_BIT_TO_WIN, ALL_ONES_INT) { EXPECT_EQ(V::flipBitToWin(-1), 32); }

TEST(V_FLIP_BIT_TO_WIN, ENDING_IN_ONES) { EXPECT_EQ(V::flipBitToWin(0xFF'00'00'00), 9); }

TEST(V_FLIP_BIT_TO_WIN, TWO_LANES_MERGEABLE) { EXPECT_EQ(V::flipBitToWin(0xFF'FF'FF'7F), 32); }