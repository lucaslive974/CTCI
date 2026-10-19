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
    BitSet<4> bits(data);
    Vector<size_t> sequences(1, 0);

    for (auto i : std::views::iota(0UZ, bits.size())) {
        if (bits.get(i)) {
            sequences.back()++;
            continue;
        }

        sequences.emplace_back(0);
    }

    if (sequences.size() == 1)
        return sequences.front();

    size_t longest = 1;
    for (auto [first, second] : sequences | std::views::adjacent<2>)
        longest = std::max(longest, first + second + 1);

    return longest;
}