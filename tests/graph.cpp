#include "chapters.hpp"
#include <gtest/gtest.h>

using namespace CTCI;

TEST(GRAPH, INIT) {
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

TEST(GRAPH, GET_EMPTY) {
    Graph<int> graph{{0, 1}};
    EXPECT_EQ(graph.getNode(2), nullptr);
}