#include "memory.hpp"
#include "concepts.hpp"

#include <cmath>
#include <gtest/gtest.h>
#include <ranges>

using namespace CTCI;

TEST(ALLOCATOR, STATELESS_ALLOCATOR) {
    static_assert(concepts::Allocator<Allocator<int>>);
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

class SMART_PTR_TEST : public testing::Test {
  protected:
    struct Base {
        int value;
        Base(int val) : value(val) {};
        virtual ~Base() = default;

        [[nodiscard]] virtual int calculate() const { return value * 2; }
    };

    struct Derived : public Base {
        char name = 'd';
        Derived(int val) : Base(val) {};
        ~Derived() = default;

        [[nodiscard]] int calculate() const override { return value * 3; };
    };

    struct Math {
        int value = 0;
        Math(int val) : value(val) {};
        virtual ~Math() = default;
        [[nodiscard]] virtual double calculate() const = 0;
    };

    struct Square : Math {
        Square(int val) : Math(val) {};
        ~Square() = default;
        [[nodiscard]] double calculate() const override { return pow(value, 2); }
    };

    struct Cubic : public Math {
        Cubic(int val) : Math(val) {};
        ~Cubic() = default;
        [[nodiscard]] double calculate() const override { return pow(value, 3); }
    };
};

TEST_F(SMART_PTR_TEST, LIFECYCLE_MANAGING) {
    auto a = CTCI::makeUnique<Base>(1);
    EXPECT_EQ((*a).value, 1);
}

TEST_F(SMART_PTR_TEST, HERITAGE) {
    auto a = CTCI::makeUnique<Derived>(1);
    EXPECT_NE(dynamic_cast<Base *>(a.get()), nullptr);

    EXPECT_EQ(a->value, 1);
    EXPECT_EQ(a->name, 'd');
}

TEST_F(SMART_PTR_TEST, RTTI_CONVERSIONS) {
    auto a = CTCI::makeShared<Derived>(1);
    EXPECT_EQ(a->name, 'd');

    SharedPtr<Base> b = dynamicPointerCast<Base>(a);
    EXPECT_NE(b, nullptr);
    EXPECT_EQ(b->value, 1);

    SharedPtr<Derived> c = staticPointerCast<Derived>(a);
    EXPECT_EQ(c->name, 'd');

    EXPECT_EQ(a.useCount(), 3);

    auto d = CTCI::makeShared<Base>(2);
    auto e = dynamicPointerCast<Derived>(d);
    EXPECT_EQ(nullptr, e);
}

TEST_F(SMART_PTR_TEST, POLYMORPHISM) {
    std::vector<SharedPtr<Math>> vec{CTCI::makeShared<Square>(2), CTCI::makeShared<Cubic>(2)};

    std::vector ans{4, 8};
    for (auto [el, val] : std::views::zip(vec, ans))
        EXPECT_EQ(el->calculate(), val);
}

TEST(SHARED_PTR_TRIVIAL, CORRECT_INITIALIZATION) {
    auto a = CTCI::makeShared<int>(1);

    EXPECT_EQ(*a, 1);
    EXPECT_EQ(a.useCount(), 1);

    {

        auto b = a; // NOLINT
        EXPECT_EQ(*b, 1);
        EXPECT_EQ(a, b);
        EXPECT_EQ(b.useCount(), 2);
    }

    EXPECT_EQ(a.useCount(), 1);
    EXPECT_TRUE(a);
};

TEST(SHARED_PTR_TRIVIAL, MOVE_INITIALIZATION) {
    auto a = CTCI::makeShared<int>(1);

    EXPECT_EQ(*a, 1);
    EXPECT_EQ(a.useCount(), 1);

    {

        auto b = std::move(a); // NOLINT
        EXPECT_EQ(*b, 1);
        EXPECT_EQ(b.useCount(), 1);
        EXPECT_NE(b, nullptr);
    }

    EXPECT_TRUE(!a);
    EXPECT_EQ(a, nullptr);
};

TEST(SHARED_PTR_TRIVIAL, MOVE_ASSIGMENT) {
    SharedPtr<int> a;
    auto b = CTCI::makeShared<int>(1);

    a = b;
    EXPECT_EQ(a.useCount(), 2);
    EXPECT_EQ(*a, 1);
}

TEST(UNIQUE_PTR_TRIVIAL, CORRECT_INITIALIZATION) {
    auto a = CTCI::makeUnique<int>(1);
    EXPECT_EQ(*a, 1);
}

TEST(UNIQUE_PTR_TRIVIAL, MOVE_OPERATIONS) {
    auto a = CTCI::makeUnique<int>(2);
    UniquePtr<int> b;

    EXPECT_EQ(*a, 2);
    EXPECT_EQ(nullptr, b);

    b = std::move(a);
    EXPECT_EQ(a, nullptr);
    EXPECT_EQ(*b, 2);

    EXPECT_FALSE(a);
    EXPECT_TRUE(b);
}

TEST(UNIQUE_PTR_TRIVIAL, RELEASE) {
    auto a = CTCI::makeUnique<int>(2);
    EXPECT_EQ(*a, 2);

    UniquePtr<int> b{a.release()};
    EXPECT_EQ(a, nullptr);
    EXPECT_EQ(*b, 2);
}

TEST(SMART_PTR, STL_COMPATIBILITY) {
    auto a = CTCI::make_unique<int>(1);
    auto b = CTCI::make_shared<int>(2);

    EXPECT_EQ(*a, 1);
    EXPECT_EQ(*b, 2);
}
