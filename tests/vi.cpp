#include "chapters.hpp"

#include <gtest/gtest.h>
#include <random>

using namespace CTCI;

TEST(VI_THE_HEAVY_PILL, BASE_CASE) { EXPECT_EQ(VI::theHeavyPill(211.3), 13); }

TEST(VI_THE_HEAVY_PILL, ROUND_UP) { EXPECT_EQ(VI::theHeavyPill(211), 10); }

TEST(VI_THE_HEAVY_PILL, ROUND_DOWN) { EXPECT_EQ(VI::theHeavyPill(210.4), 4); }

TEST(VI_THE_APOCALYPSE, BASE_CASE) {
    std::mt19937 urbg{1337}; // NOLINT
    auto res = VI::theApocalypse(urbg);

    EXPECT_NEAR(res.first, 0.50, 0.05);
    EXPECT_NEAR(res.second, 0.50, 0.05);
}
