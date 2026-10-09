#include "memory.hpp"

#include <gtest/gtest.h>

using namespace CTCI;

TEST(ALLOCATOR, STATELESS_ALLOCATOR) {
    Allocator<int> a1;
    Allocator<int> a2;

    EXPECT_TRUE(a1 == a2);
    EXPECT_FALSE(a1 != a2);
}

TEST(ALLOCATOR, TRIVIAL_TYPE_ALLOCATOR) {
    Allocator<int> alloc;

    auto *ptr = alloc.allocate(1);

    alloc.construct(ptr, 1);
    EXPECT_EQ(*ptr, 1);

    alloc.construct(ptr, 2);
    EXPECT_EQ(*ptr, 2);

    alloc.deallocate(ptr, 1);
}

TEST(ALLOCATOR, NON_TRIVIAL_TYPE_ALLOCATOR) {
    struct NonTrivialTy {
        int value = 0;

        NonTrivialTy(int value) : value(value) {};
        ~NonTrivialTy() { value = 0; };
    };

    Allocator<NonTrivialTy> alloc;

    auto *ptr = alloc.allocate(1);
    alloc.construct(ptr, 5);

    EXPECT_EQ(ptr->value, 5);

    alloc.destroy(ptr);
    EXPECT_EQ(ptr->value, 0);

    alloc.deallocate(ptr, 1);
}

TEST(ALLOCATOR, ALLOCATOR_REQUIREMENTS) {
    std::vector<int, Allocator<int>> vec{0, 1};

    EXPECT_EQ(vec[0], 0);
    EXPECT_EQ(vec[1], 1);

    vec.push_back(2);
    EXPECT_EQ(vec[2], 2);

    EXPECT_NO_THROW(vec.clear());
}
