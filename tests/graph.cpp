#include "graph.hpp"

#include <gtest/gtest.h>

using namespace CTCI;

TEST(GRAPH, INIT_WITH_EDGES) {
    Graph<int> graph{
        {0, 1},
        {1, 2},
        {2, 0},
        {3, 2},
    };

    auto node1 = graph.getNode(1);

    EXPECT_EQ(node1->neighbors.size(), 1);
    EXPECT_EQ(node1->neighbors[0]->val, 2);
}

TEST(GRAPH, INIT_WITHOUT_EDGES) {
    Graph<size_t> graph{0, 1, 2, 3};

    for (size_t i = 0; i < 4; ++i) {
        auto node = graph.getNode(i);
        EXPECT_EQ(node->neighbors.size(), 0);
    }
}

TEST(GRAPH, BIDIRECTIONAL_GRAPH) {
    Graph<int, /*Directed=*/false> graph{{0, 1}};

    auto node0 = graph.getNode(0);
    auto node1 = graph.getNode(1);

    EXPECT_EQ(node0->neighbors[0], node1);
    EXPECT_EQ(node1->neighbors[0], node0);
}

TEST(GRAPH, GET_EMPTY) {
    Graph<int> graph{{0, 1}};
    EXPECT_EQ(graph.getNode(2), nullptr);
}
