#include "associative_containers.hpp"

#include <gtest/gtest.h>
#include <ranges>

using namespace CTCI;

TEST(MAP, INSERT) {
    HashMap<int, int> map;

    map.insert({1, 2});
    map.insert({2, 1});

    EXPECT_EQ(map.get(1), 2);
    EXPECT_EQ(map.get(2), 1);
}

TEST(MAP, INSERT_UPDATE) {
    HashMap<int, int> map;

    map.insert({1, 1});
    map.insert({1, 2});

    EXPECT_EQ(map.get(1), 2);
}

TEST(MAP, INSERT_COLLISIONS) {
    HashMap<int, int> map;

    map.insert({0, 0});
    map.insert({101, 101});

    EXPECT_EQ(map.get(0), 0);
    EXPECT_EQ(map.get(101), 101);
}

TEST(MAP, SUBSCRIPT_OPERATOR) {
    HashMap<int, int> map;

    map.insert({1, 2});

    EXPECT_EQ(map[1], 2);
}

TEST(MAP, SUBSCRIPT_OPERATOR_INEXISTENT_INSERT_DEFAULT) {
    HashMap<int, int> map;
    EXPECT_EQ(map[1], 0);
}

TEST(MAP, GET_INEXISTENT_VALUE_CREATE_VALUE_DEFAULT) {
    HashMap<int, int> map;
    EXPECT_EQ(map.get(1), 0);
}

TEST(MAP, GET_WITH_COLLISIONS) {
    HashMap<int, int> map;

    map.insert({0, 0});
    map.insert({101, 101});

    EXPECT_EQ(map.get(0), 0);
    EXPECT_EQ(map.get(101), 101);
}

TEST(MAP, CONTAINS) {
    HashMap<int, int> map;
    map.insert({1, 1});
    map.insert({2, 2});

    EXPECT_TRUE(map.contains(1));
    EXPECT_TRUE(map.contains(2));
    EXPECT_FALSE(map.contains(3));
}

TEST(MAP, CONTAINS_COLLISIONS) {
    HashMap<int, int> map;

    map.insert({0, 0});
    EXPECT_FALSE(map.contains(101));
}

TEST(MAP, RESIZE) {
    HashMap<int, int> map{6};
    for (auto i : std::views::iota(1, 6))
        map.insert({i, i});

    EXPECT_EQ(map.size(), 5);
    EXPECT_EQ(map.get(4), 4);
    EXPECT_EQ(map.get(5), 5);
};

TEST(MAP, SIZE) {
    HashMap<int, int> map;

    map.insert({1, 1});
    EXPECT_EQ(map.size(), 1);
    map.insert({2, 2});
    EXPECT_EQ(map.size(), 2);
}

TEST(MAP, FOR_RANGE_ITERATOR) {
    HashMap<int, int> map;

    map.insert({2, 2});
    map.insert({105, 105});

    size_t idx = 0;
    std::vector<int> ans{2, 105};
    for (const auto &entry : map) {
        if (entry.second != ans[idx++])
            FAIL();
    };

    if (idx > ans.size())
        FAIL();
}

TEST(MAP, FOR_RANGE_ITERATOR_EMPTY_MAP) {
    HashMap<int, int> map;

    for (auto &entry : map)
        FAIL();
}

TEST(MAP, IT_POS_INCREMENT) {
    HashMap<int, int> map;

    map.insert({1, 1});
    map.insert({2, 2});

    auto begin = map.begin()++;
    EXPECT_EQ(begin->second, 2);
    EXPECT_EQ(++begin, map.end());
}

TEST(SET, INSERT_DUPLICATE) {
   Set<int> set; 
   
   set.insert(1);
   set.insert(1);
   
   EXPECT_TRUE(set.contains(1));
}

TEST(SET, CONTAINS) {
    Set<int> set;

    set.insert(1);
    EXPECT_TRUE(set.contains(1));
    EXPECT_FALSE(set.contains(2));
}

TEST(SET, CONTAINS_WITH_COLISSIONS) {
    Set<int> set;

    set.insert(0);
    set.insert(101);

    EXPECT_TRUE(set.contains(0));
    EXPECT_TRUE(set.contains(101));
}

TEST(SET, RESIZE) {
    Set<int> set{2};

    set.insert(1);
    set.insert(2);
    set.insert(3);

    EXPECT_TRUE(set.contains(1));
    EXPECT_TRUE(set.contains(2));
    EXPECT_TRUE(set.contains(3));
}
