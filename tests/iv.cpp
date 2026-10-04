#include <chapters.hpp>
#include <gtest/gtest.h>
#include <ranges>

using namespace CTCI;

class IV_ROUTE_BETWEEN_NODES_TEST : public testing::Test {
  protected:
    IV_ROUTE_BETWEEN_NODES_TEST() = default;

    const Graph<int> graph{{0, 1}, {1, 2}, {2, 0}, {2, 3}, {3, 2}, {4, 6}, {6, 5}, {5, 4}};
};

TEST_F(IV_ROUTE_BETWEEN_NODES_TEST, ROUTE_BETWEEN_NODES_TRUE) {
    auto node0 = graph.getNode(0);
    auto node1 = graph.getNode(1);
    auto node2 = graph.getNode(2);
    auto node3 = graph.getNode(3);

    EXPECT_TRUE(IV::routeBetweenNodes(node0, node3));
    EXPECT_TRUE(IV::routeBetweenNodes(node1, node2));
    EXPECT_TRUE(IV::routeBetweenNodes(node2, node0));
    EXPECT_TRUE(IV::routeBetweenNodes(node3, node0));
};

TEST_F(IV_ROUTE_BETWEEN_NODES_TEST, ROUTE_BETWEEN_NODES_FALSE) {
    auto node0 = graph.getNode(0);
    auto node4 = graph.getNode(4);
    auto node5 = graph.getNode(5);
    auto node6 = graph.getNode(6);

    EXPECT_FALSE(IV::routeBetweenNodes(node0, node4));
    EXPECT_FALSE(IV::routeBetweenNodes(node0, node5));
    EXPECT_FALSE(IV::routeBetweenNodes(node0, node6));
};

TEST_F(IV_ROUTE_BETWEEN_NODES_TEST, ROUTE_BETWEEN_NODES_DESTINY_SAME_ORIGIN) {
    auto node0 = graph.getNode(0);
    EXPECT_TRUE(IV::routeBetweenNodes(node0, node0));
};

TEST_F(IV_ROUTE_BETWEEN_NODES_TEST, ROUTE_BETWEEN_NODES_NULL_PARAMETERS) {
    auto node0 = graph.getNode(0);
    auto node4 = graph.getNode(4);

    EXPECT_FALSE(IV::routeBetweenNodes(node0, nullptr));
    EXPECT_FALSE(IV::routeBetweenNodes(nullptr, node4));
};

TEST(IV_MINIMAL_TREE, ODD_VECTOR) {
    std::vector vec{1, 2, 3, 4, 5};
    auto tree = IV::minimalTree(vec);

    auto root = tree.root;

    EXPECT_EQ(root->val, 3);
    EXPECT_EQ(root->left->val, 2);
    EXPECT_EQ(root->left->left->val, 1);

    EXPECT_EQ(root->val, 3);
    EXPECT_EQ(root->right->val, 5);
    EXPECT_EQ(root->right->left->val, 4);

    EXPECT_EQ(tree.depth, 3);
}

TEST(IV_MINIMAL_TREE, EVEN_VECTOR) {
    std::vector vec{1, 2, 4, 8};
    auto tree = IV::minimalTree(vec);

    EXPECT_EQ(tree.depth, 3);

    auto root = tree.root;
    EXPECT_EQ(root->val, 4);

    EXPECT_EQ(root->right->val, 8);
    EXPECT_EQ(root->left->val, 2);
    EXPECT_EQ(root->left->left->val, 1);
}

TEST(IV_MINIMAL_TREE, SMALL_VECTOR_THREE_ELEMENTS) {
    std::vector vec{1, 2, 3};
    auto tree = IV::minimalTree(vec);

    EXPECT_EQ(tree.depth, 2);

    auto root = tree.root;
    EXPECT_EQ(root->val, 2);
    EXPECT_EQ(root->left->val, 1);
    EXPECT_EQ(root->right->val, 3);
}

TEST(IV_MINIMAL_TREE, SMALL_VECTOR_TWO_ELEMENTS) {
    std::vector vec{1, 2};
    auto tree = IV::minimalTree(vec);

    EXPECT_EQ(tree.depth, 2);

    auto root = tree.root;
    EXPECT_EQ(root->val, 2);
    EXPECT_EQ(root->left->val, 1);
}

TEST(IV_MINIMAL_TREE, SMALL_VECTOR_ONE_ELEMENT) {
    std::vector vec{2};
    auto tree = IV::minimalTree(vec);

    EXPECT_EQ(tree.depth, 1);

    auto root = tree.root;
    EXPECT_EQ(root->val, 2);
}

TEST(IV_MINIMAL_TREE, BIG_VECTOR) {
    std::vector vec{1, 2, 4, 8, 16, 32, 64, 128, 256};

    auto tree = IV::minimalTree(vec);
    EXPECT_EQ(tree.depth, 4);
}

TEST(IV_LIST_OF_DEPTHS, TREE_EMPTY) {
    Tree<int> tree;
    auto listOfDepths = IV::listOfDepths(tree);
    EXPECT_EQ(listOfDepths.size(), 0);
}

TEST(IV_LIST_OF_DEPTHS, TREE_RANK_1) {
    Tree<int> tree{2};

    auto listOfDepths = IV::listOfDepths(tree);
    EXPECT_EQ(listOfDepths.size(), 1);

    auto &listRank1 = listOfDepths[0];
    EXPECT_EQ(listRank1.front()->val, 2);

    listRank1.pop();
    EXPECT_TRUE(listRank1.empty());
}

TEST(IV_LIST_OF_DEPTHS, TREE_RANK_2_PERFECT) {
    Tree<int> tree{2, 1, 4};

    auto listOfDepths = IV::listOfDepths(tree);
    EXPECT_EQ(listOfDepths.size(), 2);

    auto &listRank1 = listOfDepths[0];
    EXPECT_EQ(listRank1.front()->val, 2);

    auto &listRank2 = listOfDepths[1];
    std::vector<int> listRank2Ans{1, 4};
    for (auto [treeNode, ans] : std::ranges::zip_view(listRank2, listRank2Ans)) {
        EXPECT_EQ(treeNode->val, ans);
    }
}

TEST(IV_LIST_OF_DEPTHS, TREE_RANK_2_FULL) {
    Tree<int> tree{2, 1};

    auto listOfDepths = IV::listOfDepths(tree);
    EXPECT_EQ(listOfDepths.size(), 2);

    auto &listRank1 = listOfDepths[0];
    EXPECT_EQ(listRank1.front()->val, 2);

    auto &listRank2 = listOfDepths[1];
    std::vector<int> listRank2Ans{1};
    for (auto [treeNode, ans] : std::ranges::zip_view(listRank2, listRank2Ans)) {
        EXPECT_EQ(treeNode->val, ans);
    }

    listRank2.pop();
    EXPECT_TRUE(listRank2.empty());
}

TEST(IV_LIST_OF_DEPTHS, TREE_RANK_3_PERFECT) {
    Tree<int> tree{8, 2, 1, 4, 32, 16, 64};

    auto listOfDepths = IV::listOfDepths(tree);
    EXPECT_EQ(listOfDepths.size(), 3);

    auto &listRank1 = listOfDepths[0];
    EXPECT_EQ(listRank1.front()->val, 8);

    auto &listRank2 = listOfDepths[1];
    std::vector<int> listRank2Ans{2, 32};
    for (auto [treeNode, ans] : std::ranges::zip_view(listRank2, listRank2Ans)) {
        EXPECT_EQ(treeNode->val, ans);
    }

    auto &listRank3 = listOfDepths[2];
    std::vector<int> listRank3Ans{1, 4, 16, 64};
    for (auto [treeNode, ans] : std::ranges::zip_view(listRank3, listRank3Ans)) {
        EXPECT_EQ(treeNode->val, ans);
    }
}

TEST(IV_CHECK_BALANCED, EMPTY_TREE) {
    Tree<int> tree;
    EXPECT_TRUE(IV::checkBalanced(tree));
}

TEST(IV_CHECK_BALANCED, PERFECT_TREES) {
    Tree<int> tree{2, 1, 3};
    EXPECT_TRUE(IV::checkBalanced(tree));
}

TEST(IV_CHECK_BALANCED, COMPLETE_TREE) {
    Tree<int> tree{2, 1};
    EXPECT_TRUE(IV::checkBalanced(tree));
}

TEST(IV_CHECK_BALANCED, FULL_TREE) {
    Tree<int> tree{2, 1, 4, 3, 5};
    EXPECT_TRUE(IV::checkBalanced(tree));
}

TEST(IV_CHECK_BALANCED, TREE_DEGENERATED_TO_LIST) {
    Tree<int> tree{1, 2, 3};
    EXPECT_FALSE(IV::checkBalanced(tree));
}

TEST(IV_CHECK_BALANCED, TREE_HEAVY_RIGHT) {
    Tree<int> tree{2, 1, 3, 4, 5};
    EXPECT_FALSE(IV::checkBalanced(tree));
}

TEST(IV_CHECK_BALANCED, TREE_HEAVY_LEFT) {
    Tree<int> tree{3, 1, 2, 2, 4};
    EXPECT_FALSE(IV::checkBalanced(tree));
}
