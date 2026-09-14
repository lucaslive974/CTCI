#include "chapters.hpp"
#include <chrono>
#include <gtest/gtest.h>

using IX = CTCI::IX;

namespace {
namespace internal {
template <typename T> void testMatrixIsEqual(std::vector<std::vector<T>> &a, std::vector<std::vector<T>> &b) { // NOLINT
    size_t m = a.size();
    size_t n = a.front().size();
    for (size_t i = 0; i < m; ++i) {
        for (size_t j = 0; j < n; ++j) {
            EXPECT_EQ(a[i][j], b[i][j]);
        }
    }
}
} // namespace internal
} // namespace

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
    CTCI::Matrix<int> m1{
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9},
    };

    IX::rotateMatrix(m1);

    CTCI::Matrix<int> rotatedM1{
        {7, 4, 1},
        {8, 5, 2},
        {9, 6, 3},
    };

    internal::testMatrixIsEqual(m1, rotatedM1);
}

TEST(IX, TRANSPOSE_MATRIX_NON_SQUARE) {
    CTCI::Matrix<int> m1{
        {1, 2},
        {3, 4},
        {5, 6},
    };

    CTCI::Matrix<int> rotatedM1{
        {5, 3, 1},
        {6, 4, 2},
    };

    IX::rotateMatrix(m1);
    internal::testMatrixIsEqual(m1, rotatedM1);
}

TEST(IX, TRANPOSE_MATRIX_EMPTY) {
    CTCI::Matrix<int> m1;
    CTCI::Matrix<int> m2{1, CTCI::Row<int>{}};

    EXPECT_NO_THROW(IX::rotateMatrix(m1));
    EXPECT_NO_THROW(IX::rotateMatrix(m2));
}

TEST(IX, ZERO_MATRIX_SQUARED_ONE_ZERO) {
    CTCI::Matrix<int> m1{
        {1, 2, 3},
        {4, 0, 6},
        {7, 8, 9},
    };

    CTCI::Matrix<int> zeroedM1{
        {1, 0, 3},
        {0, 0, 0},
        {7, 0, 9},
    };

    IX::zeroMatrix(m1);
    internal::testMatrixIsEqual(m1, zeroedM1);
}

TEST(IX, ZERO_MATRIX_SQUARED_MULT_ZERO) {
    CTCI::Matrix<int> m1{
        {0, 2, 3},
        {4, 5, 6},
        {0, 8, 9},
    };

    CTCI::Matrix<int> zeroedM1{
        {0, 0, 0},
        {0, 5, 6},
        {0, 0, 0},
    };

    IX::zeroMatrix(m1);
    internal::testMatrixIsEqual(m1, zeroedM1);
}

TEST(IX, ZERO_MATRIX_FULL_ZERO) {
    CTCI::Matrix<int> m1{
        {0, 2, 3},
        {4, 0, 6},
        {7, 8, 0},
    };

    CTCI::Matrix<int> zeroed{
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0},
    };

    IX::zeroMatrix(m1);
    internal::testMatrixIsEqual(m1, zeroed);
}

TEST(IX, ZERO_MATRIX_SQUARED_UNITARY) {
    CTCI::Matrix<int> m1{
        {0},
    };

    EXPECT_NO_THROW(IX::zeroMatrix(m1));
    EXPECT_EQ(m1, m1);
}

TEST(IX, ZERO_MATRIX_NON_SQUARED_ONE_ZERO) {
    CTCI::Matrix<int> m1{
        {1, 2},
        {4, 0},
        {7, 8},
    };

    CTCI::Matrix<int> zeroedM1{
        {1, 0},
        {0, 0},
        {7, 0},
    };

    IX::zeroMatrix(m1);
    internal::testMatrixIsEqual(m1, zeroedM1);
}

TEST(IX, ZERO_MATRIX_EMPTY) {
    CTCI::Matrix<int> m1;
    EXPECT_NO_THROW(IX::zeroMatrix(m1));
}

TEST(IX, ZERO_MATRIX_EMPTY_II) {
    CTCI::Matrix<int> m1(1, CTCI::Row<int>{});
    EXPECT_NO_THROW(IX::zeroMatrix(m1));
}