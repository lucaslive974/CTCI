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

TEST(V_NEXT_NUMBER, BASE_CASE) {
    auto res = V::nextNumber(0b0110);
    EXPECT_EQ(res.first, 0b1001);
    EXPECT_EQ(res.second, 0b0101);
}

TEST(V_NEXT_NUMBER, ALL_BITS_EQUAL_SHOULD_RETURN_THE_NUMBER_UNALTERED) {
    constexpr auto max = std::numeric_limits<uint>::max();

    auto a = V::nextNumber(max);
    EXPECT_EQ(a.first, max);
    EXPECT_EQ(a.second, max);

    auto b = V::nextNumber(0);
    EXPECT_EQ(b.first, 0);
    EXPECT_EQ(b.second, 0);
}

TEST(V_NEXT_NUMBER, TRAILING_TARGETS_BITS) {
    auto res = V::nextNumber(0xFF'FF'00'00);

    EXPECT_EQ(res.first, 0xFF'FF'00'00);
    EXPECT_EQ(res.second, 0xFF'FE'80'00);
}

TEST(V_CONVERSION, BASE_CASE) { EXPECT_EQ(V::conversion(0b11101, 0b01111), 2); }

TEST(V_CONVERSION, ALL_BITS_DIFFERENT_SHOULD_RETURN_BITS_SIZE) { EXPECT_EQ(V::conversion(0b1010, 0b0101), 4); }

TEST(V_CONVERSION, ALL_BITS_EQUAL_SHOULD_RETURN_ZERO) { EXPECT_EQ(V::conversion(0b1111, 0b1111), 0); }

TEST(V_PAIRWISE_SWAP, BASE_CASE) { EXPECT_EQ(V::pairwiseSwap(0b1010), 0b0101); }

TEST(V_PAIRWISE_SWAP, SAME_BITS) {
    EXPECT_EQ(V::pairwiseSwap(0b1111), 0b1111);
    EXPECT_EQ(V::pairwiseSwap(0b0000), 0000);
}

TEST(V_PAIRWISE_SWAP, CONTIGUOS_SEQUENCE) { EXPECT_EQ(V::pairwiseSwap(0b1100), 0b1100); }

class V_DRAW_LINE : public testing::Test {

  protected:
    V_DRAW_LINE() = default;
    V::Screen<40> screen{/*width=*/8};
};

TEST_F(V_DRAW_LINE, BASE_CASE) {
    V::drawLine(screen, /*a1=*/{.x = 2, .y = 0}, /*a2=*/{.x = 2, .y = 7});

    // clang-format off
    CTCI::BitSet<5> output{
        0b0000'0000,
        0b0000'0000,
        0b1111'1111,
        0b0000'0000,
        0b0000'0000,
    };
    // clang-format on

    EXPECT_EQ(output, screen.buffer);
}

TEST_F(V_DRAW_LINE, NON_FULL_LINE) {
    V::drawLine(screen, /*a1=*/{.x = 2, .y = 1}, /*a2=*/{.x = 2, .y = 6});

    // clang-format off
    CTCI::BitSet<5> output{
        0b0000'0000,
        0b0000'0000,
        0b0111'1110, 
        0b0000'0000,
        0b0000'0000,
    };
    // clang-format on

    EXPECT_EQ(output, screen.buffer);
}

TEST_F(V_DRAW_LINE, DRAW_ON_BORDERS) {
    V::drawLine(screen, /*a1=*/{.x = 0, .y = 0}, /*a2=*/{.x = 0, .y = 7});
    V::drawLine(screen, /*a1=*/{.x = 4, .y = 0}, /*a2=*/{.x = 4, .y = 7});

    // clang-format off
    CTCI::BitSet<5> output{
        0b1111'1111, 
        0b0000'0000,
        0b0000'0000,
        0b0000'0000,
        0b1111'1111, 
    };
    // clang-format on

    EXPECT_EQ(output, screen.buffer);
}

TEST_F(V_DRAW_LINE, DRAW_ON_ENTIRE_SCREEN) {
    for (auto i : std::views::iota(0UZ, screen.buffer.size() / 8))
        V::drawLine(screen, /*a1=*/{.x = i, .y = 0}, /*a2=*/{.x = i, .y = 7});

    // clang-format off
    CTCI::BitSet<5> output{
        0b1111'1111, 
        0b1111'1111, 
        0b1111'1111, 
        0b1111'1111, 
        0b1111'1111, 
    };
    // clang-format on

    EXPECT_EQ(output, screen.buffer);
}
