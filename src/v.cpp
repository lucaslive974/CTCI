#include "chapters.hpp"
#include "data_structures.hpp"

using namespace CTCI;

auto V::insertion(InsertionData &info) -> int {
    int output = info.N;

    int maskLeft = static_cast<int>(~0U << (info.j + 1));
    int maskRight = static_cast<int>(~0U >> (32 - info.i));
    int mask = maskLeft | maskRight;

    output &= mask;
    output |= (info.M << info.i);

    return output;
}

auto V::flipBitToWin(int data) -> size_t {
    BitSet<4> bits(data);

    size_t longestSeq = 0;

    auto calculate = [&bits, &longestSeq](size_t start) {
        bool flipped = false;
        size_t actualSeq = 0;

        for (auto i = start; i < bits.size(); ++i) {
            auto bit = bits.get(i);

            if (!bit && flipped)
                break;

            if (!bit)
                flipped = true;

            ++actualSeq;
            longestSeq = std::max(longestSeq, actualSeq);
        }
    };

    for (auto i : std::views::iota(0UZ, bits.size()))
        calculate(i);

    return longestSeq;
}