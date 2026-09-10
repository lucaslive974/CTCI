#include "chapters.hpp"
#include <gtest/gtest.h>

using IX = CTCI::IX;

TEST(IX, IS_UNIQUE_TESTS) {
    std::string unique{"abcdefg"};
    std::string largeS{"abcdefghijklmnopqrstuvywz"};

    EXPECT_TRUE(IX::isUnique(unique));
    EXPECT_TRUE(IX::isUnique(largeS));

    std::string nonUnique{"abccdef"};
    std::string largeS2{"abcdefghijklmnopqrstuvywza"};

    EXPECT_FALSE(IX::isUnique(nonUnique));
    EXPECT_FALSE(IX::isUnique(largeS2));
}

TEST(IX, CHECK_PERMUTATION) {
    std::string s1{"lucas"};
    std::string s2{"scalu"};

    EXPECT_TRUE(IX::checkPermutation(s1, s2));

    std::string s3{"sunfire-spear"};
    std::string s4{"pears-firesuns"};

    EXPECT_FALSE(IX::checkPermutation(s3, s4));
}

TEST(IX, URLIFY) {
    std::string s1{"Mr John Smith    "};
    std::string s2{"  www.youtube    "};

    EXPECT_EQ(IX::urlify(s1, 13), R"(Mr%20John%20Smith)");
    EXPECT_EQ(IX::urlify(s2, 13), R"(%20%20www.youtube)");
}

TEST(IX, PALINDROME_PERMUTATION) {
    std::string s1{"Tact Coa"};
    EXPECT_TRUE(IX::palindromePerm(s1));
}

TEST(IX, ONE_AWAY) {
    // 1
    std::string s1p1{"pale"};
    std::string s1p2{"ple"};
    EXPECT_TRUE(IX::oneAway(s1p1, s1p2));

    // 2
    std::string s2p1{"pales"};
    std::string s2p2{"pale"};
    EXPECT_TRUE(IX::oneAway(s2p1, s2p2));

    // 3
    std::string s3p1{"pale"};
    std::string s3p2{"bale"};
    EXPECT_TRUE(IX::oneAway(s3p1, s3p2));

    // 4
    std::string s4p1{"pale"};
    std::string s4p2{"bake"};
    EXPECT_FALSE(IX::oneAway(s4p1, s4p2));

    // 5
    std::string s5p1{"ple"};
    std::string s5p2{"pale"};
    EXPECT_TRUE(IX::oneAway(s5p1, s5p2));
}