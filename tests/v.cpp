#include "chapters.hpp"

#include <gtest/gtest.h>

using CTCI::V;

TEST(V_INSERTION, BASE_CASE) {
    auto info = V::InsertionData{.M = 0b10011, .N = 0b10000000000, .i = 2, .j = 6};
    EXPECT_EQ(V::insertion(info), 0b10001001100);
}

TEST(V_INSERTION, EXISTENT_DATA_ON_INPUT_SHOULD_BE_OVERWRITTED) {
    auto info = V::InsertionData{.M = 0b10011, .N = 0b10001111100, .i = 2, .j = 6};
    EXPECT_EQ(V::insertion(info), 0b10001001100);
}
