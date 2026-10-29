#include "associative_containers.hpp"
#include "exceptions.hpp"

#include <gtest/gtest.h>
#include <ranges>

using namespace CTCI;

TEST(MAP, INSERT) {
    HashMap<int, int> map;

    map.insert({1, 2});
    map.insert({2, 1});

    EXPECT_EQ(map.at(1), 2);
    EXPECT_EQ(map.at(2), 1);
}

TEST(MAP, INSERT_UPDATE) {
    HashMap<int, int> map{{1, 1}};

    map.insert({1, 2});
    EXPECT_EQ(map.at(1), 2);
}

TEST(MAP, INSERT_COLLISIONS) {
    HashMap<int, int> map{{0, 0}};

    map.insert({101, 101});

    EXPECT_EQ(map.at(0), 0);
    EXPECT_EQ(map.at(101), 101);
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

TEST(MAP, GET_INEXISTENT_VALUE_THROWS) {
    HashMap<int, int> map;
    EXPECT_THROW(map.at(1), CTCI::OutOfRange);
}

TEST(MAP, GET_WITH_COLLISIONS) {
    HashMap<int, int> map{{0, 0}, {101, 101}};

    EXPECT_EQ(map.at(0), 0);
    EXPECT_EQ(map.at(101), 101);
}

TEST(MAP, CONTAINS) {
    HashMap<int, int> map{{1, 1}, {2, 2}};

    EXPECT_TRUE(map.contains(1));
    EXPECT_TRUE(map.contains(2));
    EXPECT_FALSE(map.contains(3));
}

TEST(MAP, CONTAINS_WITH_COLLISIONS) {
    HashMap<int, int> map{{0, 0}};
    EXPECT_FALSE(map.contains(101));
}

TEST(MAP, RESIZE) {
    HashMap<int, int> map{/*size=*/3, /*list=*/{{1, 1}, {2, 2}, {3, 3}}};

    EXPECT_EQ(map.size(), 3);
    EXPECT_EQ(map.at(1), 1);
    EXPECT_EQ(map.at(2), 2);
    EXPECT_EQ(map.at(3), 3);
};

TEST(MAP, SIZE) {
    HashMap<int, int> map{{1, 1}};

    EXPECT_EQ(map.size(), 1);
    map.insert({2, 2});
    EXPECT_EQ(map.size(), 2);
}

TEST(MAP, CLEAR) {
    HashMap<int, int> map{{1, 1}};

    EXPECT_EQ(map.size(), 1);

    map.clear();
    EXPECT_EQ(map.size(), 0);
}

TEST(MAP, ERASE) {
    HashMap<int, int> map{{1, 1}, {2, 2}, {3, 3}};
    map.erase(2);

    EXPECT_EQ(map.size(), 2);
    for (auto [pair, exp] : std::views::zip(map, Vector<std::pair<int, int>>{{1, 1}, {3, 3}}))
        EXPECT_EQ(pair, exp);
}

TEST(MAP, ERASE_ON_COLLIDED_KEYS) {
    HashMap<int, int> map{{0, 0}, {101, 101}};
    map.erase(101);

    EXPECT_EQ(map.size(), 1);
    EXPECT_TRUE(map.contains(0));
}

TEST(MAP, ERASE_KEY_NON_INEXISTENT_DOES_NOTHING) {
    HashMap<int, int> map;
    EXPECT_NO_FATAL_FAILURE({ map.erase(1); });
}

TEST(MAP, FOR_RANGE_ITERATOR) {
    HashMap<int, int> map{{2, 2}, {105, 105}};

    Vector<int> ans{2, 105};
    for (const auto &[entry, val] : std::views::zip(map, ans)) {
        if (entry.second != val)
            FAIL();
    };
}

TEST(MAP, FOR_RANGE_ITERATOR_EMPTY_MAP) {
    HashMap<int, int> map;

    for (auto &entry : map)
        FAIL();
}

TEST(MAP, IT_POS_INCREMENT) {
    HashMap<int, int> map{{1, 1}, {2, 2}};

    auto begin = map.begin()++;
    EXPECT_EQ(begin->second, 2);
    EXPECT_EQ(++begin, map.end());
}

TEST(SET, INSERT_DUPLICATE) {
    Set<int> set{1};

    set.insert(1);
    EXPECT_TRUE(set.contains(1));
}

TEST(SET, CONTAINS) {
    Set<int> set{1};

    EXPECT_TRUE(set.contains(1));
    EXPECT_FALSE(set.contains(2));
}

TEST(SET, CONTAINS_WITH_COLISSIONS) {
    Set<int> set{0, 101};

    EXPECT_TRUE(set.contains(0));
    EXPECT_TRUE(set.contains(101));
}

TEST(SET, RESIZE) {
    Set<int> set{/*size=*/2, /*list=*/{1, 2, 3}};

    EXPECT_TRUE(set.contains(1));
    EXPECT_TRUE(set.contains(2));
    EXPECT_TRUE(set.contains(3));
}

TEST(SET, FIND) {
    const Set<int> set{1, 2, 102};

    EXPECT_NE(set.find(1), set.end());
    EXPECT_NE(set.find(102), set.end());
    EXPECT_EQ(set.find(3), set.end());
}

TEST(SET, ERASE) {
    Set<int> set{0, 1, 2};
    set.erase(2);

    EXPECT_EQ(set.size(), 2);

    for (auto [q, v] : std::views::zip(set, Vector{0, 1}))
        EXPECT_EQ(q, v);
}

TEST(SET, ERASE_ON_COLLIDED_KEYS) {
    Set<int> set{0, 101};

    set.erase(101);
    EXPECT_EQ(set.size(), 1);
    EXPECT_TRUE(set.contains(0));
}

TEST(SET, ERASE_KEY_NON_INEXISTENT_DOES_NOTHING) {
    Set<int> set{2, 3};
    EXPECT_NO_FATAL_FAILURE({ set.erase(1); });
}

TEST(SET, CONST_FOR_RANGE) {
    const Set<int> set{1, 2, 3};
    EXPECT_EQ(set.size(), 3);

    for (auto [q, v] : std::views::zip(set, std::views::iota(1, 4)))
        EXPECT_EQ(q, v);
}
