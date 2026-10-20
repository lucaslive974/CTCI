#include "bitset.hpp"

#include <gtest/gtest.h>

using namespace CTCI;

TEST(BIT_SET, SHOULD_CORRECTLY_SET) {
    BitSet<1> bitset;

    bitset.set(7);

    EXPECT_TRUE(bitset.get(7));
    EXPECT_FALSE(bitset.get(6));
}

TEST(BIT_SET, SHOULD_INITIALIZE_EMPTY) {
    BitSet<1> bitset;
    for (int i : std::views::iota(0, 8))
        EXPECT_FALSE(bitset.get(i));
}

TEST(BIT_SET, SHOULD_INITIALIZE_CORRECTLY) {
    BitSet<1> bitset(static_cast<uint8_t>(0xFF));
    for (int i : std::views::iota(0, 8))
        EXPECT_TRUE(bitset.get(i));
}

TEST(BIT_SET, SHOULD_CLEAR_ALL_BITS) {
    BitSet<1> bitset(static_cast<uint8_t>(0xFF));

    for (auto i : std::views::iota(0, 8))
        bitset.clear(i);

    for (auto i : std::views::iota(0, 8))
        EXPECT_FALSE(bitset.get(i));
}

TEST(BIT_SET, SHOULD_CLEAR_ONLY_SPECIFIC_BIT) {
    BitSet<1> bitset(static_cast<uint8_t>(0xFF));

    bitset.clear(0);
    EXPECT_FALSE(bitset.get(0));

    for (auto i : std::views::iota(1, 8))
        EXPECT_TRUE(bitset.get(i));
}

TEST(BIT_SET, MULTI_BYTE_SIZE_SHUOLD_RETURN_AMOUNT_OF_BITS_AVAILABLE) {
    BitSet<4> bitset;
    EXPECT_EQ(bitset.size(), 32);
}

TEST(BIT_SET, RANGE_INITIALIZATION) {
    BitSet<4> bitset{0x00, 0x01, 0x10, 0x11};

    EXPECT_FALSE(bitset.get(7));
    EXPECT_TRUE(bitset.get(8));
    EXPECT_TRUE(bitset.get(20));
    EXPECT_TRUE(bitset.get(24));
    EXPECT_TRUE(bitset.get(28));
}

TEST(BIT_SET, MULTI_BYTE_INITIALIZATION) {
    BitSet<4> bitset(0xFF0FF000);

    EXPECT_TRUE(bitset.get(31));
    EXPECT_FALSE(bitset.get(23));
}

TEST(BIT_SET, OR_UNION_OPERATION) {
    BitSet<4> a(0xFF'00'00'FF);
    BitSet<4> b(0x00'FF'FF'00);
    EXPECT_EQ(static_cast<uint>(a | b), 0xFF'FF'FF'FF);
}

TEST(BIT_SET, AND_INTERSECTION_OPERATION) {
    BitSet<4> a(0xFF'00'00'FF);
    BitSet<4> b(0x00'FF'FF'00);
    EXPECT_EQ(static_cast<uint>(a & b), 0);
}
