#include <chapters.hpp>
#include <gtest/gtest.h>

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

    EXPECT_EQ(tree.rank, 3);
}

TEST(IV_MINIMAL_TREE, EVEN_VECTOR) {
    std::vector vec{1, 2, 4, 8};
    auto tree = IV::minimalTree(vec);

    EXPECT_EQ(tree.rank, 3);

    auto root = tree.root;
    EXPECT_EQ(root->val, 4);

    EXPECT_EQ(root->right->val, 8);
    EXPECT_EQ(root->left->val, 2);
    EXPECT_EQ(root->left->left->val, 1);
}

TEST(IV_MINIMAL_TREE, SMALL_VECTOR_THREE_ELEMENTS) {
    std::vector vec{1, 2, 3};
    auto tree = IV::minimalTree(vec);

    EXPECT_EQ(tree.rank, 2);

    auto root = tree.root;
    EXPECT_EQ(root->val, 2);
    EXPECT_EQ(root->left->val, 1);
    EXPECT_EQ(root->right->val, 3);
}

TEST(IV_MINIMAL_TREE, SMALL_VECTOR_TWO_ELEMENTS) {
    std::vector vec{1, 2};
    auto tree = IV::minimalTree(vec);

    EXPECT_EQ(tree.rank, 2);

    auto root = tree.root;
    EXPECT_EQ(root->val, 2);
    EXPECT_EQ(root->left->val, 1);
}

TEST(IV_MINIMAL_TREE, SMALL_VECTOR_ONE_ELEMENT) {
    std::vector vec{2};
    auto tree = IV::minimalTree(vec);

    EXPECT_EQ(tree.rank, 1);

    auto root = tree.root;
    EXPECT_EQ(root->val, 2);
}