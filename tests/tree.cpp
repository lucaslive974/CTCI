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

    EXPECT_EQ(tree.depth, 3);
}

TEST(TREE, RANK_INCREASE) {
    Tree<int> tree;

    EXPECT_EQ(tree.depth, 0);

    tree.append(3);
    EXPECT_EQ(tree.depth, 1);

    tree.append(2);
    tree.append(5);
    EXPECT_EQ(tree.depth, 2);

    tree.append(4);
    EXPECT_EQ(tree.depth, 3);
}

TEST(TREE, RANGES) {
    Tree<int> tree;

    for (const auto &node : tree)
        FAIL();

    tree.append(2);
    tree.append(1);
    tree.append(3);

    for (const auto [node, val] : std::views::zip(tree, std::views::iota(1, 4)))
        EXPECT_EQ(node->val, val);
}

TEST(TREE, NODE_SIZE_SHOULD_INIT_AS_ONE) {
    Tree<int> tree{2};

    EXPECT_EQ(tree.root->size, 1);
}

TEST(TREE, NODE_SIZE_SHOULD_INCREMENT_ON_APPEND) {
    Tree<int> tree{2};

    tree.append(3);
    EXPECT_EQ(tree.root->size, 2);

    tree.append(1);
    EXPECT_EQ(tree.root->size, 3);

    EXPECT_EQ(tree.root->right->size, 1);
    EXPECT_EQ(tree.root->left->size, 1);
}

TEST(TREE, NODE_SIZE_SHOULD_CONSTRUCT_WITH_CORRECT_SIZE) {
    Tree<int> tree{2, 3, 1};

    /* 2 */
    EXPECT_EQ(tree.root->size, 3);

    /* 3 */
    EXPECT_EQ(tree.root->right->size, 1);

    /* 1 */
    EXPECT_EQ(tree.root->left->size, 1);
}

TEST(TREE, TREE_DEGENERATED_SHOULD_OUTPUT_CORRECT_SIZE) {
    Tree<int> tree{3, 2, 1};

    /* 3 */
    EXPECT_EQ(tree.root->size, 3);

    /* 2 */
    EXPECT_EQ(tree.root->left->size, 2);

    /* 1 */
    EXPECT_EQ(tree.root->left->left->size, 1);
}
