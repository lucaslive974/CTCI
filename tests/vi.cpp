#include "chapters.hpp"

#include <gtest/gtest.h>

using namespace CTCI;

TEST(VI_THE_HEAVY_PILL, BASE_CASE) { EXPECT_EQ(VI::theHeavyPill(211.3), 13); }

TEST(VI_THE_HEAVY_PILL, ROUND_UP) { EXPECT_EQ(VI::theHeavyPill(211), 10); }

TEST(VI_THE_HEAVY_PILL, ROUND_DOWN) { EXPECT_EQ(VI::theHeavyPill(210.4), 4); }
