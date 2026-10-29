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
