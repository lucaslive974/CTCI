#include "chapters.hpp"
#include <gtest/gtest.h>

namespace internal {
template <typename T> void testMatrixIsEqual(std::vector<std::vector<T>> &a, std::vector<std::vector<T>> &b) { // NOLINT
    size_t m = a.size();
    size_t n = a.front().size();
    for (size_t i = 0; i < m; ++i) {
        for (size_t j = 0; j < n; ++j) {
            EXPECT_EQ(a[i][j], b[i][j]);
        }
    }
}

template <typename T> void testListIsEqual(const CTCI::List<T> &a, const CTCI::List<T> &b) { // NOLINT
    auto headA = a.head;
    auto headB = b.head;
    while (headA != nullptr && headB != nullptr) {
        EXPECT_EQ(headA->val, headB->val);
        headA = headA->next;
        headB = headB->next;
    }

    if (headA == nullptr && headB != nullptr)
        FAIL() << "List A ended while B yet have nodes";

    if (headB == nullptr && headA != nullptr)
        FAIL() << "List B ended while A yet have nodes";
}

} // namespace internal
