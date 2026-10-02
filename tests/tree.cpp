#include "chapters.hpp"
#include "gtest/gtest.h"
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

    tree.append(4);
    EXPECT_EQ(root->left->val, 4);

    tree.append(3);
    EXPECT_EQ(root->left->left->val, 3);

    tree.append(4);
    EXPECT_EQ(root->left->right->val, 4);
}

TEST(TREE, EMPTY_TREE_DESTRUCTOR) {
    Tree<int> tree;

    EXPECT_NO_THROW(tree.~Tree());
}