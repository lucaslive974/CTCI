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

auto V::flipBitToWin(int data) -> size_t {
    struct Sequence {
        size_t size = 0;
        size_t start = 0;
        size_t end = 0;
        Sequence(size_t i) : start(i) {};
    };

    BitSet<4> bits(data);
    auto findNextOne = [&bits](size_t idx) -> size_t {
        while (idx < bits.size() && !bits.get(idx))
            ++idx;
        return idx;
    };

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
    
    if(running == 32)
        return running;

    return std::max(longest, running + last + 1);
}