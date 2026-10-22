#include "bitset.hpp"

#include <cstdint>
#include <gtest/gtest.h>

using namespace CTCI;

TEST(BIT_SET, SHOULD_CORRECTLY_SET) {
    Bitset<1> bitset;

    bitset.set(7);

    EXPECT_TRUE(bitset.get(7));
    EXPECT_FALSE(bitset.get(6));
}

TEST(BIT_SET, SHOULD_INITIALIZE_EMPTY) {
    Bitset<1> bitset;
    for (int i : std::views::iota(0, 8))
        EXPECT_FALSE(bitset.get(i));
}

TEST(BIT_SET, SHOULD_INITIALIZE_CORRECTLY) {
    Bitset<1> bitset(static_cast<uint8_t>(0xFF));
    for (int i : std::views::iota(0, 8))
        EXPECT_TRUE(bitset.get(i));
}

TEST(BIT_SET, SHOULD_CLEAR_ALL_BITS) {
    Bitset<1> bitset(static_cast<uint8_t>(0xFF));

    for (auto i : std::views::iota(0, 8))
        bitset.clear(i);

    for (auto i : std::views::iota(0, 8))
        EXPECT_FALSE(bitset.get(i));
}

TEST(BIT_SET, SHOULD_CLEAR_ONLY_SPECIFIC_BIT) {
    Bitset<1> bitset(static_cast<uint8_t>(0xFF));

    bitset.clear(0);
    EXPECT_FALSE(bitset.get(0));

    for (auto i : std::views::iota(1, 8))
        EXPECT_TRUE(bitset.get(i));
}

TEST(BIT_SET, MULTI_BYTE_SIZE_SHUOLD_RETURN_AMOUNT_OF_BITS_AVAILABLE) {
    Bitset<4> bitset;
    EXPECT_EQ(bitset.size(), 32);
}

TEST(BIT_SET, RANGE_INITIALIZATION) {
    Bitset<4> bitset{0x00, 0x01, 0x10, 0x11};

    EXPECT_FALSE(bitset.get(7));
    EXPECT_TRUE(bitset.get(8));
    EXPECT_TRUE(bitset.get(20));
    EXPECT_TRUE(bitset.get(24));
    EXPECT_TRUE(bitset.get(28));
}

TEST(BIT_SET, MULTI_BYTE_INITIALIZATION) {
    Bitset<4> bitset(0xFF0FF000);

    EXPECT_TRUE(bitset.get(31));
    EXPECT_FALSE(bitset.get(23));
}

TEST(BIT_SET, OR_UNION_OPERATION) {
    Bitset<4> a(0xFF'00'00'FF);
    Bitset<4> b(0x00'FF'FF'00);
    EXPECT_EQ(a | b, 0xFF'FF'FF'FF);
}

TEST(BIT_SET, AND_INTERSECTION_OPERATION) {
    Bitset<4> a(0xFF'00'00'FF);
    Bitset<4> b(0x00'FF'FF'00);
    EXPECT_EQ(a & b, 0);
}

TEST(BIT_SET, BOOLEAN_CONVERSION) {
    Bitset<4> a(0xFF'FF'00'00);
    EXPECT_TRUE(a);

    Bitset<4> b(0x00'00'00'00);
    EXPECT_FALSE(b);
}

TEST(BIT_SET, EQUALITY_COMPARATION_OPERATOR) {
    Bitset<8> lhs(0xFF'00'00'FF);
    Bitset<8> rhs(0xFF'00'00'FF);

    EXPECT_EQ(lhs, rhs);
}

TEST(BIT_SET, INEQUALITY_COMPARATION_OPERATOR) {
    Bitset<8> lhs(0x00'00'00'FF);
    Bitset<8> rhs(0x00'00'FF'00);

    EXPECT_NE(lhs, rhs);
}

TEST(BIT_SET, NEGATION_OPERATOR) {
    Bitset<4> a(0x00'00'00'00);
    EXPECT_EQ(~a, 0xFF'FF'FF'FF);

    Bitset<4> b(0xFF'00'FF'00);
    EXPECT_EQ(~b, 0x00'FF'00'FF);
}

TEST(BIT_SET, BIT_SHIFT_GREATER_THAN_SIZE_SHOULD_ZEROED) {
    Bitset<4> a(0xFF'FF'FF'FF);
    auto b = a;

    EXPECT_EQ(a <<= 32, 0);
    EXPECT_EQ(b >>= 32, 0);
}

TEST(BIT_SET, BIT_SHIFT_ZERO_SHOULD_REMAIN_UNTOUCHED) {
    Bitset<4> a(0xFF'FF'FF'FF);
    Bitset<4> b = a;

    EXPECT_EQ(a <<= 0, b);
    EXPECT_EQ(a >>= 0, b);
}

TEST(BIT_SET, LEFT_BIT_SHIFT) {
    Bitset<4> a(0x00'00'00'FF);
    EXPECT_EQ(a <<= 4, 0x00'00'0F'F0);
    EXPECT_EQ(a <<= 4, 0x00'00'FF'00);

    Bitset<4> b(0x00'00'00'FF);
    EXPECT_EQ(b <<= 24, 0xFF'00'00'00);
}

TEST(BIT_SET, RIGHT_BIT_SHIFT) {
    Bitset<4> a(0xFF'00'00'00);

    EXPECT_EQ(a >>= 4, 0x0F'F0'00'00);
    EXPECT_EQ(a >>= 4, 0x00'FF'00'00);
    EXPECT_EQ(a >>= 16, 0x00'00'00'FF);
}

TEST(BIT_SET, SHIFTS_TEMPORARIES) {
    Bitset<4> a(0x00'FF'FF'00);

    EXPECT_EQ(a << 8, 0xFF'FF'00'00);
    EXPECT_EQ(a >> 8, 0x00'00'FF'FF);

    EXPECT_EQ(a, 0x00'FF'FF'00);
}
