#include "tree.hpp"
#include <gtest/gtest.h>

using namespace CTCI;

TEST(TREE, TREE_APPEND) {
    Tree<int> tree{5};
    auto &root = tree.root;

    tree.append(4);
    EXPECT_EQ(root->left->val, 4);

    tree.append(5);
    EXPECT_EQ(root->right->val, 5);
}

TEST(TREE, TREE_APPEND_SUBTREE) {
    Tree<int> tree{5};
    auto &root = tree.root;

    auto subTreeLeft = tree.append(root, 4);
    EXPECT_EQ(root->left, subTreeLeft);

    auto subTreeRight = tree.append(root, 6);
    EXPECT_EQ(root->right, subTreeRight);

    auto subTreeRightLeft = tree.append(subTreeRight, 5);
    EXPECT_EQ(root->right->left, subTreeRightLeft);

    auto subTreeRightRight = tree.append(subTreeRight, 7);
    EXPECT_EQ(root->right->right, subTreeRightRight);

    auto subTreeLeftLeft = tree.append(subTreeLeft, 3);
    EXPECT_EQ(root->left->left, subTreeLeftLeft);

    auto subTreeLeftRight = tree.append(subTreeLeft, 4);
    EXPECT_EQ(root->left->right, subTreeLeftRight);
}

TEST(TREE, EMPTY_TREE_DESTRUCTOR) {
    Tree<int> tree;

    EXPECT_NO_THROW({ tree.~Tree(); });
}

TEST(TREE, RANKS_INIT) {
    Tree<int> tree{3, 2, 1, 5, 4};

    EXPECT_EQ(tree.rank, 3);
}

TEST(TREE, RANK_INCREASE) {
    Tree<int> tree;

    EXPECT_EQ(tree.rank, 0);

    tree.append(3);
    EXPECT_EQ(tree.rank, 1);

    tree.append(2);
    tree.append(5);
    EXPECT_EQ(tree.rank, 2);

    tree.append(4);
    EXPECT_EQ(tree.rank, 3);
}
