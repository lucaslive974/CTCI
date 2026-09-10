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