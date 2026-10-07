#include "chapters.hpp"
#include "testing_utils.hpp"
#include <gtest/gtest.h>

using II = CTCI::II;

TEST(II, REMOVE_DUPS) {
    CTCI::List<int> list{1, 2, 3, 4, 3, 5};
    CTCI::List<int> listWithoutDups{1, 2, 4, 3, 5};

    II::removeDups(list);
    internal::testListIsEqual(list, listWithoutDups);
}

TEST(II, REMOVE_DUPS_ALL_UNIQUES) {
    std::vector<int> els{5, 4, 3, 2, 1};

    CTCI::List<int> l1{els};
    CTCI::List<int> l2{els};

    II::removeDups(l1);
    internal::testListIsEqual(l1, l2);
}

TEST(II, REMOVE_DUPS_EMPTY) {
    CTCI::List<int> list;

    EXPECT_NO_THROW(II::removeDups(list));
    EXPECT_TRUE(list.empty());
}

TEST(II, REMOVE_DUPS_ALL_DUPS) {
    CTCI::List<int> list{1, 1, 1, 1, 1};

    II::removeDups(list);

    EXPECT_FALSE(list.empty());
    EXPECT_EQ(list.head->val, 1);
    EXPECT_EQ(list.head->next, nullptr);
}

TEST(II, REMOVE_DUPS_HEAD_DUP) {
    CTCI::List<int> list{1, 1, 2};
    II::removeDups(list);

    EXPECT_EQ(list.head->val, 1);
    EXPECT_EQ(list.head->next->val, 2);
    EXPECT_EQ(list.head->next->next, nullptr);
}

TEST(II, RETURN_KTH_TO_LAST_ELEMEMENT) {
    CTCI::List<int> list{1, 2, 3, 4, 5};

    EXPECT_EQ(II::kthLast(list, 0), 5);
    EXPECT_EQ(II::kthLast(list, 1), 4);
    EXPECT_EQ(II::kthLast(list, 2), 3);
    EXPECT_EQ(II::kthLast(list, 3), 2);
    EXPECT_EQ(II::kthLast(list, 4), 1);
}

TEST(II, RETURN_KTH_TO_LAST_ELEMENT_K_GREATER_THAN_LIST_SHOULD_THROW) {
    CTCI::List<int> list{1, 2, 3, 4, 5};

    EXPECT_THROW(II::kthLast(list, 5), std::invalid_argument);
}

TEST(II, RETURN_KTH_TO_LAST_ELEMENT_EMPTY_LIST_THROWS) {
    CTCI::List<int> list;
    EXPECT_THROW(II::kthLast(list, 2), std::invalid_argument);
}

TEST(II, DELETE_MIDDLE_NODE) {
    CTCI::List<int> list{1, 2, 3, 4, 5};

    auto node = list.head->next->next;
    II::deleteMiddleNode(node);

    CTCI::List<int> delList{1, 2, 4, 5};
    internal::testListIsEqual(list, delList);
}

TEST(II, DELETE_MIDDLE_NODE_NULL_NODE) {
    CTCI::List<int> list{1, 2};

    std::shared_ptr<CTCI::Node<int>> node = nullptr;
    EXPECT_NO_THROW(II::deleteMiddleNode(node));
}

TEST(II, DELETE_MIDDLE_NODE_EMPTY_LIST) {
    CTCI::List<int> list;

    II::deleteMiddleNode(list.head);
    CTCI::List<int> dlist;

    internal::testListIsEqual(list, dlist);
}

TEST(II, PARTITION_LIST) {
    int k = 5;
    CTCI::List<int> list{3, 5, 8, 5, 10, 2, 1};
    II::partition(list, k);

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

    EXPECT_EQ(list.head->val, 3);
    EXPECT_EQ(list.tail->val, 10);
}

TEST(II, PARTITION_LIST_EMPTY_LIST) {
    CTCI::List<int> list;
    EXPECT_NO_THROW(II::partition(list, 1));
}

TEST(II, PARTITION_LIST_NO_LESS_THAN_K) {
    CTCI::List<int> list{2, 3, 4};
    CTCI::List<int> pList{2, 3, 4};

    EXPECT_NO_THROW(II::partition(list, 2));
    internal::testListIsEqual(list, pList);
}

TEST(II, PARTITION_LIST_NO_GREATER_THAN_K) {
    CTCI::List<int> list{1, 2, 3};
    CTCI::List<int> pList{1, 2, 3};

    EXPECT_NO_THROW(II::partition(list, 4));
    internal::testListIsEqual(list, pList);
}

TEST(II, SUM_LISTS_SAME_SIZE) {
    CTCI::List<int> a{0, 0, 1};
    CTCI::List<int> b{0, 5, 1};
    CTCI::List<int> ans{0, 5, 2};

    auto res = II::sumLists(a, b);
    internal::testListIsEqual(res, ans);
}

TEST(II, SUM_LISTS_DIFFERENT_SIZES_B_LESS) {
    CTCI::List<int> a{0, 0, 1};
    CTCI::List<int> b{0, 5};
    CTCI::List<int> ans{0, 5, 1};

    auto res = II::sumLists(a, b);
    internal::testListIsEqual(res, ans);
}

TEST(II, SUM_LISTS_DIFFERENT_SIZES_A_LESS) {
    CTCI::List<int> a{0, 8};
    CTCI::List<int> b{0, 0, 3};
    CTCI::List<int> ans{0, 8, 3};

    auto res = II::sumLists(a, b);
    internal::testListIsEqual(res, ans);
}

TEST(II, SUM_LISTS_CARRY_ON_MIDDLE) {
    CTCI::List<int> a{9, 1};
    CTCI::List<int> b{9, 1};
    CTCI::List<int> ans{8, 3};

    auto res = II::sumLists(a, b);
    internal::testListIsEqual(res, ans);
}

TEST(II, SUM_LISTS_CARRY_ON_END) {
    CTCI::List<int> a{0, 9};
    CTCI::List<int> b{0, 9};
    CTCI::List<int> ans{0, 8, 1};

    auto res = II::sumLists(a, b);
    internal::testListIsEqual(res, ans);
}

TEST(II, SUM_LISTS_MULTIPLE_CARRY) {
    CTCI::List<int> a{9, 9};
    CTCI::List<int> b{9, 9};
    CTCI::List<int> ans{8, 9, 1};

    auto res = II::sumLists(a, b);
    internal::testListIsEqual(res, ans);
}

TEST(II, SUM_LISTS_EMPTY_A) {
    CTCI::List<int> a;
    CTCI::List<int> b{0, 9};

    auto res = II::sumLists(a, b);
    internal::testListIsEqual(res, b);
}

TEST(II, SUM_LISTS_EMPTY_B) {
    CTCI::List<int> a{9, 8};
    CTCI::List<int> b;

    auto res = II::sumLists(a, b);
    internal::testListIsEqual(res, a);
}

TEST(II, SUM_LISTS_BOTH_EMPTY) {
    CTCI::List<int> a;
    CTCI::List<int> b;

    auto res = II::sumLists(a, b);
    internal::testListIsEqual(res, {});
}

TEST(II, PALINDROME_ODD_TRUE) {
    CTCI::List<char> a{'a', 'b', 'c', 'b', 'a'};
    EXPECT_TRUE(II::palindrome(a));
}

TEST(II, PALINDROME_EVEN_TRUE) {
    CTCI::List<char> a{'a', 'b', 'b', 'a'};
    EXPECT_TRUE(II::palindrome(a));
}

TEST(II, PALINDROME_ODD_FALSE) {
    CTCI::List<char> a{'a', 'a', 'c', 'b', 'a'};
    EXPECT_FALSE(II::palindrome(a));
}

TEST(II, PALINDROME_EVEN_FALSE) {
    CTCI::List<char> a{'a', 'a', 'b', 'a'};
    EXPECT_FALSE(II::palindrome(a));
}

TEST(II, PALINDROME_ONE_ELEMENT) {
    CTCI::List<char> a{'a'};
    EXPECT_TRUE(II::palindrome(a));
}

TEST(II, PALINDROME_TWO_ELEMENTS) {
    CTCI::List<char> a{'a', 'a'};
    EXPECT_TRUE(II::palindrome(a));
}

TEST(II, PALINDROME_TWO_ELEMENTS_II) {
    CTCI::List<char> a{'a', 'b'};
    EXPECT_FALSE(II::palindrome(a));
}

TEST(II, PALINDROME_EMPTY) {
    CTCI::List<char> a;
    EXPECT_TRUE(II::palindrome(a));
}

TEST(II, PALINDROME_LIST_RECONSTRUCTION) {
    CTCI::List<char> a{'a', 'b', 'c', 'b', 'a'};
    CTCI::List<char> aCopy{a};

    II::palindrome(a);
    internal::testListIsEqual(a, aCopy);
}

TEST(II, INTERSECTION_LIST_TRUE) {
    CTCI::List<int> a{1, 2};
    CTCI::List<int> b{3, 4};

    auto nodeIntersecting = std::make_shared<CTCI::Node<int>>(5);

    a.push(nodeIntersecting);
    b.push(nodeIntersecting);

    EXPECT_EQ(II::intersection(a, b), nodeIntersecting);
}

TEST(II, INTERSECTION_LIST_FALSE) {
    CTCI::List<int> a{1, 2};
    CTCI::List<int> b{3, 4};

    EXPECT_EQ(II::intersection(a, b), nullptr);
}

TEST(II, LOOP_DETECTION_LIST_CYCLIC) {
    CTCI::List<int> a{1, 2};
    auto circularNodeI = std::make_shared<CTCI::Node<int>>(3);
    a.push(circularNodeI);
    a.push({4, 5});

    auto circularNodeII = std::make_shared<CTCI::Node<int>>(6);
    circularNodeII->next = circularNodeI;

    a.push(circularNodeII);

    EXPECT_EQ(II::loopDetection(a), circularNodeI);
}

TEST(II, LOOP_DETECTION_LIST_ACYCLIC) {
    CTCI::List<int> list{1, 2, 3, 4, 5};

    EXPECT_EQ(II::loopDetection(list), nullptr);
}

TEST(II, LOOP_DETECTION_LIST_ACYCLIC_II) {
    CTCI::List<int> list{1, 2, 3, 4, 5, 6};

    EXPECT_EQ(II::loopDetection(list), nullptr);
}
