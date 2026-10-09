#include "array.hpp"

#include <gtest/gtest.h>
#include <ranges>

#include <algorithm>

using namespace CTCI;
using ArrayT = Array<int, 3>;

TEST(ARRAY, INIT) {
    ArrayT array{0, 1, 2};

    for (auto i : std::views::iota(0, 3))
        EXPECT_EQ(array[i], i);

    EXPECT_EQ(array.size(), 3);
}

TEST(ARRAY, RANGE) {
    static_assert(std::ranges::range<ArrayT>);
    const ArrayT array{0, 1, 2};

    size_t ans = 0;
    for (const auto &el : array)
        EXPECT_EQ(el, ans++);
}

TEST(ARRAY, INPUT_OUTPUT_RANGE) {
    static_assert(std::ranges::input_range<ArrayT>);
    static_assert(std::ranges::output_range<ArrayT, int>);

    ArrayT array{1, 2, 3};
    std::array<int, 3> ans{2, 4, 6};

    for (auto &el : array)
        el *= 2;

    for (const auto [el, val] : std::views::zip(array, ans))
        EXPECT_EQ(el, val);
}

TEST(ARRAY, FORWARD_RANGE) {
    static_assert(std::ranges::forward_range<ArrayT>);

    ArrayT array{1, 2, 3};
    std::array<int, 3> ans{1, 2, 3};

    for (auto i : std::views::iota(0, 2))
        for (auto [el, val] : std::views::zip(array, ans))
            EXPECT_EQ(el, val);
}

TEST(ARRAY, BIDIRECTIONAL_RANGE) {
    static_assert(std::ranges::bidirectional_range<ArrayT>);

    ArrayT array{1, 2, 3};
    std::array<int, 3> ans{3, 2, 1};

    for (auto [el, val] : std::views::zip(std::views::reverse(array), ans))
        EXPECT_EQ(el, val);
}

TEST(ARRAY, RANDOM_ACCESS_RANGE) {
    static_assert(std::ranges::random_access_range<ArrayT>);
    ArrayT array{2, 3, 1};
    std::array<int, 3> ans{1, 2, 3};

    std::ranges::sort(array);
    for (auto [el, val] : std::views::zip(array, ans))
        EXPECT_EQ(el, val);
}

TEST(ARRAY, RANGE_ORDERING) {
    ArrayT arr{1, 2, 3};

    EXPECT_TRUE(arr.begin() < arr.end());
    EXPECT_FALSE(arr.end() < arr.end());

    EXPECT_TRUE(arr.end() <= arr.end());
    EXPECT_FALSE(arr.end() <= arr.begin());

    EXPECT_TRUE(arr.end() > arr.begin());
    EXPECT_FALSE(arr.begin() > arr.begin());

    EXPECT_TRUE(arr.begin() >= arr.begin());
    EXPECT_FALSE(arr.begin() >= arr.end());
}

TEST(ARRAY, RANGE_DIFF) {
    ArrayT arr{1, 2, 3};

    EXPECT_EQ(arr.end() - 3, arr.begin());
    EXPECT_EQ(arr.end() - 3, arr.begin());
    EXPECT_EQ(arr.begin() + 3, arr.end());
}
