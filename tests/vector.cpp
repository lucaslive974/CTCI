#include "vector.hpp"
#include "exceptions.hpp"

#include <gtest/gtest.h>

using namespace CTCI;

TEST(VECTOR, DEFAULT_CONSTRUCTOR) {
    Vector<int> vec;
    EXPECT_EQ(vec.size(), 0);
    EXPECT_EQ(vec.capacity(), 64);
}

TEST(VECTOR, SMALL_VECTOR_INIT) {
    Vector<int> vec{1, 2, 3};

    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 2);
    EXPECT_EQ(vec[2], 3);
    EXPECT_EQ(vec.size(), 3);
    EXPECT_EQ(vec.capacity(), 64);
}

TEST(VECTOR, GREAT_VECTOR_INIT) {
    Vector<int> vec(100, 1);

    EXPECT_EQ(vec[99], 1);
    EXPECT_EQ(vec.size(), 100);
    EXPECT_EQ(vec.capacity(), 128);
}

class VECTOR_NON_TRIVIAL_TYPE : public testing::Test {
  protected:
    struct NonTrivial {
        int value;
        NonTrivial() : value(0) {};
        NonTrivial(int value) : value(value) {}
        NonTrivial(const NonTrivial &other) { value = other.value; }
        NonTrivial(NonTrivial &&other) noexcept {
            value = other.value;
            other.value = 0;
        }
        NonTrivial &operator=(NonTrivial other) {
            using std::swap;
            swap(value, other.value);
            return *this;
        }
        ~NonTrivial() {};
    };

    VECTOR_NON_TRIVIAL_TYPE() = default;
};

TEST_F(VECTOR_NON_TRIVIAL_TYPE, NON_TRIVIAL_TYPE) {
    EXPECT_NO_FATAL_FAILURE({ Vector<NonTrivial> vec(2); });
}

TEST_F(VECTOR_NON_TRIVIAL_TYPE, NON_TRIVIAL_RESIZE) {
    Vector<NonTrivial> vec(63, 1);

    for (auto i : std::views::iota(0, 63))
        EXPECT_EQ(vec[i].value, 1);

    vec.pushBack(2);
    EXPECT_EQ(vec[63].value, 2);
    EXPECT_EQ(vec.size(), 64);
    EXPECT_EQ(vec.capacity(), 128);
}

TEST_F(VECTOR_NON_TRIVIAL_TYPE, NON_TRIVIAL_INSERT) {
    Vector<NonTrivial> vec{1, 3};

    vec.insert(vec.begin() + 1, 2);

    EXPECT_EQ(vec[0].value, 1);
    EXPECT_EQ(vec[1].value, 2);
    EXPECT_EQ(vec[2].value, 3);
    
    EXPECT_EQ(vec.size(), 3);
}

TEST(VECTOR, AT_SHOULD_VERIFY_BOUNDARIES) {
    Vector<int> vec{1, 2, 3};

    EXPECT_THROW(vec.at(-1), OutOfRange);
    EXPECT_THROW(vec.at(3), OutOfRange);

    EXPECT_NO_THROW(vec.at(2));
}

TEST(VECTOR, AUTO_RESIZING) {
    Vector<int> vec{std::views::iota(0, 63)};

    vec.pushBack(64);
    EXPECT_EQ(vec[63], 64);
    EXPECT_EQ(vec.size(), 64);
    EXPECT_EQ(vec.capacity(), 128);

    vec.pushBack(65);
    EXPECT_EQ(vec[64], 65);
    EXPECT_EQ(vec.size(), 65);
    EXPECT_EQ(vec.capacity(), 128);
}

TEST(VECTOR, INSERT_BEGINNING) {
    Vector<int> vec{1, 2, 3};

    vec.insert(vec.begin(), 1);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 1);
    EXPECT_EQ(vec[2], 2);
    EXPECT_EQ(vec[3], 3);
}

TEST(VECTOR, INSERT_MIDDLE) {
    Vector<int> vec{1, 2, 3};

    vec.insert(vec.begin() + 1, 4);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 4);
    EXPECT_EQ(vec[2], 2);
    EXPECT_EQ(vec[3], 3);
}

TEST(VECTOR, RANGE) {
    Vector<int> vec{1, 2, 3};

    for (const auto [el, val] : std::views::zip(vec, std::views::iota(1, 4)))
        EXPECT_EQ(el, val);

    EXPECT_EQ(vec.begin() + 3, vec.end());
}
