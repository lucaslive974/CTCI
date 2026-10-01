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