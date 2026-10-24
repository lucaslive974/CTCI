#include "chapters.hpp"

#include <ranges>

using namespace CTCI;

auto VI::theHeavyPill(double measureWeight) -> uint { return static_cast<uint>((measureWeight - 210) / 0.1); }

auto VI::poison(const Array<Soda, 1000> &bottles) -> size_t {
    struct TestStrip {
        bool isTainted = false;

        void test(const Soda &soda) {
            if (soda.isPoisoned)
                isTainted = true;
        }
    };

    Array<TestStrip, 10> strips;

    for (auto [i, bottle] : std::views::enumerate(bottles)) {
        const uint idx = i + 1;
        for (auto bit : std::views::iota(0U, 10U))
            if (static_cast<bool>(idx & (1U << bit)))
                strips[bit].test(bottle);
    }

    Bitset<2> res;
    for (const auto [i, strip] : std::views::enumerate(strips))
        if (strip.isTainted)
            res.set(i);

    return res;
}
