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

TEST(IX, CHECK_PERMUTATION_DIFFERENT_LENGTH) {
    std::string s1{"abcd"};
    std::string s2{"aabcd"};

    EXPECT_FALSE(IX::checkPermutation(s1, s2));
}

TEST(IX, CHECK_PERMUTATION_DIFFERENT_CHARS) {
    std::string s1{"abcde"};
    std::string s2{"fghi"};

    EXPECT_FALSE(IX::checkPermutation(s1, s2));
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

    std::string s2{"abcdbbcd"};
    EXPECT_FALSE(IX::palindromePerm(s2));

    std::string s3{"aadbc"};
    EXPECT_FALSE(IX::palindromePerm(s3));
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

TEST(IX, STRING_COMPRESSION_EMPTY_STRING) {
    std::string empty;
    EXPECT_EQ(IX::stringCompression(empty), "");
}

TEST(IX, STRING_COMPRESSION) {
    std::string s1{"aabcccccaaa"};
    EXPECT_EQ(IX::stringCompression(s1), "a2b1c5a3");
}

TEST(IX, STRING_COMPRESSION_LONGER_THAN_ORIGINAL) {
    std::string s1{"abcdefg"};

    // a1b1c1d1e1f1g1
    EXPECT_EQ(IX::stringCompression(s1), s1);
}

TEST(IX, TRANSPOSE_MATRIX_SQUARED) {
    std::vector<std::vector<int>> m1{
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9},
    };

    IX::rotateMatrix(m1);

    std::vector<std::vector<int>> rotatedM1{
        {7, 4, 1},
        {8, 5, 2},
        {9, 6, 3},
    };

    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = 0; j < 3; ++j) {
            EXPECT_EQ(m1[i][j], rotatedM1[i][j]);
        }
    }
}

TEST(IX, TRANSPOSE_MATRIX_NON_SQUARE) {
    std::vector<std::vector<int>> m1{
        {1, 2},
        {3, 4},
        {5, 6},
    };

    std::vector<std::vector<int>> rotatedM1{
        {5, 3, 1},
        {6, 4, 2},
    };

    IX::rotateMatrix(m1);

    for (size_t i = 0; i < 2; ++i) {
        for (size_t j = 0; j < 3; ++j) {
            EXPECT_EQ(m1[i][j], rotatedM1[i][j]);
        }
    }
}