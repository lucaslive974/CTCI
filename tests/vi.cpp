#include "chapters.hpp"

#include <gtest/gtest.h>

using namespace CTCI;

class VI_THE_HEAVY_PILL : public testing::Test {
  protected:
    VI_THE_HEAVY_PILL() = default;
    Array<VI::Bottle, 20> bottles = Array<VI::Bottle, 20>(/*value=*/{1.0});
};

TEST_F(VI_THE_HEAVY_PILL, BASE_CASE) {
    bottles[12] = {.weight = 1.1};

    EXPECT_EQ(VI::theHeavyPill(bottles), 13);
}

TEST_F(VI_THE_HEAVY_PILL, ROUND_UP) {
    bottles[9] = {.weight = 1.1};

    EXPECT_EQ(VI::theHeavyPill(bottles), 10);
}

TEST_F(VI_THE_HEAVY_PILL, ROUND_DOWN) {
    bottles[3] = {.weight = 1.1};

    EXPECT_EQ(VI::theHeavyPill(bottles), 4);
}
