#include "chapters.hpp"

#include <ranges>

using namespace CTCI;

auto VI::theHeavyPill(const Array<Bottle, 20> &bottles) -> uint {
    double measureWeight = 0;

    for (auto [i, bottle] : bottles | std::views::enumerate)
        measureWeight += bottle.weight * static_cast<float>(i + 1);

    return static_cast<uint>((measureWeight - 210) / 0.1);
}
