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
    BitSet<1> bitset(0xFF);
    for (int i : std::views::iota(0, 8))
        EXPECT_TRUE(bitset.get(i));
}

TEST(BIT_SET, SHOULD_CLEAR_ALL_BITS) {
    BitSet<1> bitset(0xFF);

    for (auto i : std::views::iota(0, 8))
        bitset.clear(i);

    for (auto i : std::views::iota(0, 8))
        EXPECT_FALSE(bitset.get(i));
}

TEST(BIT_SET, SHOULD_CLEAR_ONLY_SPECIFIC_BIT) {
    BitSet<1> bitset(0xFF);

    bitset.clear(0);
    EXPECT_FALSE(bitset.get(0));

    for (auto i : std::views::iota(1, 8))
        EXPECT_TRUE(bitset.get(i));
}

TEST(BIT_SET, MULTI_BYTE_SIZE_SHUOLD_RETURN_CORRECTLY) {
    BitSet<4> bitset;
    EXPECT_EQ(bitset.size(), 4);
}

TEST(BIT_SET, RANGE_INITIALIZATION) {
    BitSet<4> bitset{ 0x00, 0x01, 0x10, 0x11 };
    
    EXPECT_FALSE(bitset.get(7));
    EXPECT_TRUE(bitset.get(8));
    EXPECT_TRUE(bitset.get(20));
    EXPECT_TRUE(bitset.get(24));
    EXPECT_TRUE(bitset.get(28));
}
