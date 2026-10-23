#include "chapters.hpp"

#include <ranges>

using namespace CTCI;

auto VI::theHeavyPill(double measureWeight) -> uint { return static_cast<uint>((measureWeight - 210) / 0.1); }
