#include "chapters.hpp"
#include "data_structures.hpp"
#include <ranges>

using namespace CTCI;

auto V::insertion(InsertionData &info) -> uint {
    uint output = info.N;

    uint maskLeft = static_cast<int>(~0U << (info.j + 1));
    uint maskRight = static_cast<int>(~0U >> (32 - info.i));
    uint mask = maskLeft | maskRight;

    output &= mask;
    output |= (info.M << info.i);

    return output;
}

auto V::flipBitToWin(uint data) -> size_t {
    BitSet<4> bits(data);

    size_t longest = 1;

    size_t last = 0;
    size_t running = 0;

    for (auto i : std::views::iota(0UZ, bits.size())) {
        if (bits.get(i)) {
            ++running;
            continue;
        }

        longest = std::max(longest, last + running + 1);
        last = running;
        running = 0;
    }

    if (running == 32)
        return running;

    return std::max(longest, running + last + 1);
}