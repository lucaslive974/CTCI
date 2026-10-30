#include "chapters.hpp"

#include <ranges>

using namespace CTCI;

auto VIII::tripleSteps(size_t steps) -> size_t {
    static Array<size_t, 4> ans{0, 1, 2, 4};
    if (steps < 4)
        return ans[steps];

    size_t a = 1;
    size_t b = 2;
    size_t c = 4;

    for (auto i : std::views::iota(4U, steps + 1)) {
        size_t n = a + b + c;

        a = b;
        b = c;
        c = n;
    }

    return c;
}

auto VIII::robotInAGrid(const GridInfo &info, const Vector<Spot> &offLimits) -> Vector<Spot> {
    Vector<Spot> result;
    Vector<Vector<bool>> limits(info.colSize, Vector(info.rowSize, false));

    for (const auto &spot : offLimits)
        limits[spot.x][spot.y] = true;

    auto traverse = [&result, &info, &limits](this auto &self, const Spot &spot) -> bool {
        if (spot.x >= info.colSize || spot.y >= info.rowSize || limits[spot.x][spot.y])
            return false;

        result.pushBack({.x = spot.x, .y = spot.y});
        if (spot.x == info.colSize - 1 && spot.y == info.rowSize - 1)
            return true;

        if (self({spot.x + 1, spot.y}))
            return true;

        if (self({spot.x, spot.y + 1}))
            return true;

        result.popBack();
        limits[spot.x][spot.y] = true;
        return false;
    };

    traverse({.x = 0, .y = 0});
    return result;
}

auto findMagicIndex(const Vector<int> &arr, int start, int end) -> int {
    if (start > end)
        return -1;

    int middle = ((end - start) / 2) + start;

    auto &val = arr[middle];
    if (val == middle)
        return middle;

    if (val < middle)
        return findMagicIndex(arr, middle + 1, end);

    return findMagicIndex(arr, start, middle - 1);
}

auto VIII::magicIndex(const Vector<int> &arr) -> int { return findMagicIndex(arr, 0, static_cast<int>(arr.size()) - 1); }

auto VIII::powerSet(const UnorderedSet<int> &set) -> Vector<UnorderedSet<int>> {
    Vector<UnorderedSet<int>> res{{}};
    Vector<int> els{set};

    UnorderedSet<int> subset;
    auto recurse = [&res, &els, &subset](this auto &self, size_t el) -> void {
        subset.insert(els[el]);
        res.pushBack(subset);

        for (auto i : std::views::iota(el + 1, els.size()))
            self(i);

        subset.erase(els[el]);
    };

    for (auto i : std::views::iota(0UZ, set.size()))
        recurse(i);

    return res;
}

auto VIII::recursiveMultiply(int lhs, int rhs) -> int {
    if (lhs == 0 || rhs == 0)
        return 0;

    bool isNegative = (lhs < 0) ^ (rhs < 0);

    unsigned int absLhs = (lhs < 0) ? -static_cast<unsigned int>(lhs) : static_cast<unsigned int>(lhs);
    unsigned int absRhs = (rhs < 0) ? -static_cast<unsigned int>(rhs) : static_cast<unsigned int>(rhs);

    unsigned int smaller = std::min(absLhs, absRhs);
    unsigned int bigger = std::max(absLhs, absRhs);

    auto multiply = [&bigger](this auto &self, unsigned int count) -> unsigned int {
        if (count == 1)
            return bigger;

        unsigned int half = self(count >> 1);
        unsigned int sum = half + half;

        if (count & 1)
            sum += bigger;

        return sum;
    };

    unsigned int absResult = multiply(smaller);

    return isNegative ? -static_cast<int>(absResult) : static_cast<int>(absResult);
}
