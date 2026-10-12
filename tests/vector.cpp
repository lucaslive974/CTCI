#include "vector.hpp"
#include "exceptions.hpp"

#include <algorithm>
#include <gtest/gtest.h>
#include <memory>

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
        ~NonTrivial() { value = 0; };
    };

    VECTOR_NON_TRIVIAL_TYPE() = default;
};

TEST_F(VECTOR_NON_TRIVIAL_TYPE, NON_TRIVIAL_TYPE) {
    EXPECT_NO_FATAL_FAILURE({ Vector<NonTrivial> vec(2, 1); });
}

TEST_F(VECTOR_NON_TRIVIAL_TYPE, NON_TRIVIAL_COPY_CONSTRUCT) {
    EXPECT_NO_FATAL_FAILURE({
        Vector<NonTrivial> a(1);
        Vector<NonTrivial> b = a; // NOLINT
    });
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

TEST_F(VECTOR_NON_TRIVIAL_TYPE, NON_TRIVIAL_COPY) {
    Vector<NonTrivial> vec{1, 2};
    auto vecCopy = vec;

    for (auto [entry, cpy] : std::views::zip(vec, vecCopy))
        EXPECT_EQ(entry.value, cpy.value);
}

TEST_F(VECTOR_NON_TRIVIAL_TYPE, NON_TRIVIAL_ERASE) {
    Vector<NonTrivial> vec{1, 2, 3, 4};

    vec.erase(vec.begin() + 1, vec.begin() + 2);
    EXPECT_EQ(vec.size(), 2);
    EXPECT_EQ(vec.front().value, 1);
    EXPECT_EQ(vec.back().value, 4);
}

class VECTOR_MOVE_ONLY_TYPE : public testing::Test {

  protected:
    struct MoveOnly {
        int value = 0;
        MoveOnly() = default;
        MoveOnly(int val) : value(val) {};
        MoveOnly(const MoveOnly &other) = delete; // NOLINT
        MoveOnly(MoveOnly &&other) noexcept {
            value = other.value;
            other.value = 0;
        }
        MoveOnly &operator=(MoveOnly &&other) noexcept {
            value = other.value;
            other.value = 0;
            return *this;
        };
    };
};

TEST_F(VECTOR_MOVE_ONLY_TYPE, MOVE_ONLY_TYPES) {
    Vector<MoveOnly> vec;

    vec.emplaceBack(1);
    EXPECT_EQ(vec.back().value, 1);

    vec.pushBack(MoveOnly{2});
    EXPECT_EQ(vec.back().value, 2);
    EXPECT_EQ(vec.size(), 2);
}

TEST(VECTOR, COPY_CONSTRUCTOR_AND_ASSIGNMENT_TRIVIAL) {
    Vector<int> vec{3, 2, 1};
    Vector<int> copy;
    copy = vec;
    for (auto [val, cpy] : std::views::zip(vec, copy))
        EXPECT_EQ(val, cpy);
}

TEST(VECTOR, MOVE_CONSTRUCTOR_AND_ASSIGNMENT) {
    Vector<int> vec{1, 2, 3};
    Vector<int> moved;
    moved = std::move(vec);

    EXPECT_EQ(vec.size(), 0);
    EXPECT_EQ(vec.capacity(), 64);

    EXPECT_EQ(moved.size(), 3);
    EXPECT_EQ(moved[0], 1);
    EXPECT_EQ(moved[1], 2);
    EXPECT_EQ(moved[2], 3);
}

TEST(VECTOR, AT_SHOULD_VERIFY_BOUNDARIES) {
    Vector<int> vec{1, 2, 3};

    EXPECT_THROW(vec.at(-1), OutOfRange);
    EXPECT_THROW(vec.at(3), OutOfRange);

    EXPECT_NO_THROW(vec.at(2));
}

TEST(VECTOR, AUTO_RESIZING) {
    auto view = std::views::iota(0, 63);
    Vector<int> vec{view.begin(), view.end()};

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

TEST(VECTOR, INSERT_RANGE) {
    Vector<int> vec;
    vec.insert(vec.end(), {0, 1, 2});
    EXPECT_EQ(vec.size(), 3);

    vec.insert(vec.end(), std::views::iota(3, 65));
    EXPECT_EQ(vec.size(), 65);
}

TEST(VECTOR, POP_BACK) {
    Vector<int> vec{1, 2, 3};

    vec.popBack();
    EXPECT_EQ(vec.size(), 2);
    EXPECT_EQ(vec.back(), 2);

    vec.popBack();
    EXPECT_EQ(vec.size(), 1);
    EXPECT_EQ(vec.back(), 1);

    vec.popBack();
    EXPECT_TRUE(vec.empty());
}

TEST(VECTOR, EMPTY) {
    Vector<int> vec;

    EXPECT_TRUE(vec.empty());

    vec.pushBack(1);
    EXPECT_FALSE(vec.empty());
}

TEST(VECTOR, ERASE) {
    Vector<int> vec{1, 2, 3};

    vec.erase(vec.begin() + 1);
    EXPECT_EQ(vec.size(), 2);
    EXPECT_EQ(vec.front(), 1);
    EXPECT_EQ(vec.back(), 3);

    vec.erase(vec.begin(), vec.begin() + 1);
    EXPECT_TRUE(vec.empty());
}

TEST(VECTOR, SIDES_ACCESS) {
    Vector<int> vec{3, 2, 1};

    EXPECT_EQ(vec.front(), 3);
    EXPECT_EQ(vec.back(), 1);
}

TEST(VECTOR, EMPLACE_BACK) {
    Vector<int> vec{1, 2};

    vec.emplaceBack(3);
    EXPECT_EQ(vec.size(), 3);
    EXPECT_EQ(vec.back(), 3);
}

TEST(VECTOR, EMPLACE_BACK_WITH_RESIZE) {
    Vector<int> vec{std::views::iota(0, 63)};

    EXPECT_NO_FATAL_FAILURE(vec.emplaceBack(63));
    EXPECT_EQ(vec.size(), 64);
    EXPECT_EQ(vec.back(), 63);
}

TEST(VECTOR, CLEAR) {
    Vector<int> vec{1, 2, 3};
    vec.clear();

    EXPECT_EQ(vec.size(), 0);

    vec.pushBack(1);
    EXPECT_EQ(vec.size(), 1);
    EXPECT_EQ(vec.front(), 1);
}

TEST(VECTOR, RAW_DATA) {
    Vector<int> vec{1, 2, 3};

    vec.data()[0] = 2;
    EXPECT_EQ(*vec.cdata(), 2);
}

TEST(VECTOR, EQUALITY) {
    Vector<int> a{1, 2, 3};
    Vector<int> b{1, 2, 3};

    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);

    std::ranges::reverse(b);
    EXPECT_FALSE(a == b);
    EXPECT_TRUE(a != b);
}

TEST(VECTOR, VECTOR_OF_VECTOR) {
    Vector<Vector<int>> vec(3, Vector<int>(3, 0));

    EXPECT_EQ(vec.size(), 3);
    EXPECT_EQ(vec.front().size(), 3);
}

TEST(VECTOR, STL_COMPATIBILITY) {
    Vector<int> vec{1, 2, 3};

    vec.push_back(4);
    vec.emplace_back(5);

    EXPECT_EQ(vec.size(), 5);
    EXPECT_EQ(vec[3], 4);
    EXPECT_EQ(vec[4], 5);

    vec.pop_back();
    EXPECT_EQ(vec.size(), 4);

    Vector<std::unique_ptr<int>> vecSmartPtr;
    vecSmartPtr.emplace_back(std::make_unique<int>(1));

    EXPECT_EQ(vecSmartPtr.size(), 1);
    EXPECT_EQ(*(vecSmartPtr.front()), 1);
}

TEST(VECTOR, RANGE) {
    Vector<int> vec{1, 2, 3};

    for (const auto [el, val] : std::views::zip(vec, std::views::iota(1, 4)))
        EXPECT_EQ(el, val);
    EXPECT_EQ(vec.begin() + 3, vec.end());

    const Vector<int> vecB;
    EXPECT_EQ(vecB.begin(), vecB.end());
}
