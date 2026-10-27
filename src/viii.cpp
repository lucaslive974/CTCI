#include "chapters.hpp"

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
