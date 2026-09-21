#include "chapters.hpp"
#include "testing_utils.hpp"
#include <gtest/gtest.h>
#include <memory>
#include <stdexcept>

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

TEST(IX, STRING_ROTATION_SUBSTR) {
    std::string s1{"waterbottle"};
    std::string s2{"erbottlewat"};

    EXPECT_TRUE(IX::stringRotation(s1, s2));
}

TEST(IX, STRING_ROTATION_ISNT_SUBSTR) {
    std::string s1{"abcdef"};
    std::string s2{"fabdee"};

    EXPECT_FALSE(IX::stringRotation(s1, s2));
}

TEST(IX, REMOVE_DUPS) {
    CTCI::List<int> list{1, 2, 3, 4, 3, 5};
    CTCI::List<int> listWithoutDups{1, 2, 4, 3, 5};

    IX::removeDups(list);
    internal::testListIsEqual(list, listWithoutDups);
}

TEST(IX, REMOVE_DUPS_ALL_UNIQUES) {
    std::vector<int> els{5, 4, 3, 2, 1};

    CTCI::List<int> l1{els};
    CTCI::List<int> l2{els};

    IX::removeDups(l1);
    internal::testListIsEqual(l1, l2);
}

TEST(IX, REMOVE_DUPS_EMPTY) {
    CTCI::List<int> list;

    EXPECT_NO_THROW(IX::removeDups(list));
    EXPECT_TRUE(list.empty());
}

TEST(IX, REMOVE_DUPS_ALL_DUPS) {
    CTCI::List<int> list{1, 1, 1, 1, 1};

    IX::removeDups(list);

    EXPECT_FALSE(list.empty());
    EXPECT_EQ(list.head->val, 1);
    EXPECT_EQ(list.head->next, nullptr);
}

TEST(IX, REMOVE_DUPS_HEAD_DUP) {
    CTCI::List<int> list{1, 1, 2};
    IX::removeDups(list);

    EXPECT_EQ(list.head->val, 1);
    EXPECT_EQ(list.head->next->val, 2);
    EXPECT_EQ(list.head->next->next, nullptr);
}

TEST(IX, RETURN_KTH_TO_LAST_ELEMEMENT) {
    CTCI::List<int> list{1, 2, 3, 4, 5};

    EXPECT_EQ(IX::kthLast(list, 0), 5);
    EXPECT_EQ(IX::kthLast(list, 1), 4);
    EXPECT_EQ(IX::kthLast(list, 2), 3);
    EXPECT_EQ(IX::kthLast(list, 3), 2);
    EXPECT_EQ(IX::kthLast(list, 4), 1);
}

TEST(IX, RETURN_KTH_TO_LAST_ELEMENT_K_GREATER_THAN_LIST_SHOULD_THROW) {
    CTCI::List<int> list{1, 2, 3, 4, 5};

    EXPECT_THROW(IX::kthLast(list, 5), std::invalid_argument);
}

TEST(IX, RETURN_KTH_TO_LAST_ELEMENT_EMPTY_LIST_THROWS) {
    CTCI::List<int> list;
    EXPECT_THROW(IX::kthLast(list, 2), std::invalid_argument);
}

TEST(IX, DELETE_MIDDLE_NODE) {
    CTCI::List<int> list{1, 2, 3, 4, 5};

    auto node = list.head->next->next;
    IX::deleteMiddleNode(node);

    CTCI::List<int> delList{1, 2, 4, 5};
    internal::testListIsEqual(list, delList);
}

TEST(IX, DELETE_MIDDLE_NODE_NULL_NODE) {
    CTCI::List<int> list{1, 2};

    std::shared_ptr<CTCI::Node<int>> node = nullptr;
    EXPECT_NO_THROW(IX::deleteMiddleNode(node));
}

TEST(IX, DELETE_MIDDLE_NODE_EMPTY_LIST) {
    CTCI::List<int> list;

    IX::deleteMiddleNode(list.head);
    CTCI::List<int> dlist;

    internal::testListIsEqual(list, dlist);
}

TEST(IX, PARTITION_LIST) {
    int k = 5;
    CTCI::List<int> list{3, 5, 8, 5, 10, 2, 1};
    IX::partition(list, k);

    std::unordered_map<int, int> leftNums;
    std::unordered_map<int, int> rightNums;

    bool isRightSide = false;

    auto head = list.head;
    while (head != nullptr) {
        if (head->val >= k)
            isRightSide = true;

        if (!isRightSide)
            leftNums[head->val]++;
        else
            rightNums[head->val]++;

        head = head->next;
    }

    EXPECT_EQ(leftNums.size(), 3);
    EXPECT_EQ(rightNums.size(), 3);

    /* Left */
    EXPECT_EQ(leftNums[3], 1);
    EXPECT_EQ(leftNums[2], 1);
    EXPECT_EQ(leftNums[1], 1);

    /* Right */
    EXPECT_EQ(rightNums[5], 2);
    EXPECT_EQ(rightNums[10], 1);
    EXPECT_EQ(rightNums[8], 1);
}

TEST(IX, PARTITION_LIST_EMPTY_LIST) {
    CTCI::List<int> list;
    EXPECT_NO_THROW(IX::partition(list, 1));
}

TEST(IX, PARTITION_LIST_NO_LESS_THAN_K) {
    CTCI::List<int> list{2, 3, 4};
    CTCI::List<int> pList{2, 3, 4};

    EXPECT_NO_THROW(IX::partition(list, 2));
    internal::testListIsEqual(list, pList);
}

TEST(IX, PARTITION_LIST_NO_GREATER_THAN_K) {
    CTCI::List<int> list{1, 2, 3};
    CTCI::List<int> pList{1, 2, 3};

    EXPECT_NO_THROW(IX::partition(list, 4));
    internal::testListIsEqual(list, pList);
}

TEST(IX, SUM_LISTS_SAME_SIZE) {
    CTCI::List<int> a{0, 0, 1};
    CTCI::List<int> b{0, 5, 1};
    CTCI::List<int> ans{0, 5, 2};

    auto res = IX::sumLists(a, b);
    internal::testListIsEqual(res, ans);
}

TEST(IX, SUM_LISTS_DIFFERENT_SIZES_B_LESS) {
    CTCI::List<int> a{0, 0, 1};
    CTCI::List<int> b{0, 5};
    CTCI::List<int> ans{0, 5, 1};

    auto res = IX::sumLists(a, b);
    internal::testListIsEqual(res, ans);
}

TEST(IX, SUM_LISTS_DIFFERENT_SIZES_A_LESS) {
    CTCI::List<int> a{0, 8};
    CTCI::List<int> b{0, 0, 3};
    CTCI::List<int> ans{0, 8, 3};

    auto res = IX::sumLists(a, b);
    internal::testListIsEqual(res, ans);
}

TEST(IX, SUM_LISTS_CARRY_ON_MIDDLE) {
    CTCI::List<int> a{9, 1};
    CTCI::List<int> b{9, 1};
    CTCI::List<int> ans{8, 3};

    auto res = IX::sumLists(a, b);
    internal::testListIsEqual(res, ans);
}

TEST(IX, SUM_LISTS_CARRY_ON_END) {
    CTCI::List<int> a{0, 9};
    CTCI::List<int> b{0, 9};
    CTCI::List<int> ans{0, 8, 1};

    auto res = IX::sumLists(a, b);
    internal::testListIsEqual(res, ans);
}

TEST(IX, SUM_LISTS_MULTIPLE_CARRY) {
    CTCI::List<int> a{9, 9};
    CTCI::List<int> b{9, 9};
    CTCI::List<int> ans{8, 9, 1};

    auto res = IX::sumLists(a, b);
    internal::testListIsEqual(res, ans);
}

TEST(IX, SUM_LISTS_EMPTY_A) {
    CTCI::List<int> a;
    CTCI::List<int> b{0, 9};

    auto res = IX::sumLists(a, b);
    internal::testListIsEqual(res, b);
}

TEST(IX, SUM_LISTS_EMPTY_B) {
    CTCI::List<int> a{9, 8};
    CTCI::List<int> b;

    auto res = IX::sumLists(a, b);
    internal::testListIsEqual(res, a);
}

TEST(IX, SUM_LISTS_BOTH_EMPTY) {
    CTCI::List<int> a;
    CTCI::List<int> b;

    auto res = IX::sumLists(a, b);
    internal::testListIsEqual(res, {});
}

TEST(IX, PALINDROME_ODD_TRUE) {
    CTCI::List<char> a{'a', 'b', 'c', 'b', 'a'};
    EXPECT_TRUE(IX::palindrome(a));
}

TEST(IX, PALINDROME_EVEN_TRUE) {
    CTCI::List<char> a{'a', 'b', 'b', 'a'};
    EXPECT_TRUE(IX::palindrome(a));
}

TEST(IX, PALINDROME_ODD_FALSE) {
    CTCI::List<char> a{'a', 'a', 'c', 'b', 'a'};
    EXPECT_FALSE(IX::palindrome(a));
}

TEST(IX, PALINDROME_EVEN_FALSE) {
    CTCI::List<char> a{'a', 'a', 'b', 'a'};
    EXPECT_FALSE(IX::palindrome(a));
}

TEST(IX, PALINDROME_ONE_ELEMENT) {
    CTCI::List<char> a{'a'};
    EXPECT_TRUE(IX::palindrome(a));
}

TEST(IX, PALINDROME_TWO_ELEMENTS) {
    CTCI::List<char> a{'a', 'a'};
    EXPECT_TRUE(IX::palindrome(a));
}

TEST(IX, PALINDROME_TWO_ELEMENTS_II) {
    CTCI::List<char> a{'a', 'b'};
    EXPECT_FALSE(IX::palindrome(a));
}

TEST(IX, PALINDROME_EMPTY) {
    CTCI::List<char> a;
    EXPECT_TRUE(IX::palindrome(a));
}

TEST(IX, PALINDROME_LIST_RECONSTRUCTION) {
    CTCI::List<char> a{'a', 'b', 'c', 'b', 'a'};
    CTCI::List<char> aCopy{a};

    IX::palindrome(a);
    internal::testListIsEqual(a, aCopy);
}

TEST(IX, INTERSECTION_LIST_TRUE) {
    CTCI::List<int> a{1, 2};
    CTCI::List<int> b{3, 4};

    auto nodeIntersecting = std::make_shared<CTCI::Node<int>>(5);

    a.appendToTail(nodeIntersecting);
    b.appendToTail(nodeIntersecting);

    EXPECT_EQ(IX::intersection(a, b), nodeIntersecting);
}

TEST(IX, INTERSECTION_LIST_FALSE) {
    CTCI::List<int> a{1, 2};
    CTCI::List<int> b{3, 4};

    EXPECT_EQ(IX::intersection(a, b), nullptr);
}
