#include "chapters.hpp"
#include "data_structures.hpp"
#include <limits>
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

extern BitSet<4> nextNumber(BitSet<4> bits, uint8_t target) {
    size_t idx = 0;

    int opposite = 0;
    while (bits.get(idx) != static_cast<bool>(target)) {
        ++opposite;
        ++idx;
    }

    int same = 0;
    while (idx < bits.size() && bits.get(idx) == static_cast<bool>(target)) {
        ++same;
        ++idx;
    }

    if (idx == bits.size())
        return bits;

    using Operation = void (BitSet<4>::*)(size_t);
    std::pair<Operation, Operation> op = static_cast<bool>(target) ? std::make_pair(&BitSet<4>::set, &BitSet<4>::clear)
                                                                   : std::make_pair(&BitSet<4>::clear, &BitSet<4>::set);
    auto &[first, second] = op;

    BitSet<4> output = bits;
    (output.*first)(idx);

    output &= BitSet<4>(~0) << idx;

    idx = 0;
    while (same > 1) {
        (output.*first)(idx++);
        --same;
    }

    while (opposite + 1 > 0) {
        (output.*second)(idx++);
        --opposite;
    }

    return output;
}

auto V::nextNumber(uint data) -> std::pair<uint, uint> {
    if (std::numeric_limits<uint>::max() == data || data == 0)
        return {data, data};

    auto next = ::nextNumber(/*bits=*/BitSet<4>(data), /*target=*/1);
    auto prev = ::nextNumber(/*bits=*/BitSet<4>(data), /*target=*/0);
    return {next, prev};
}

auto V::conversion(uint a, uint b) -> size_t { // NOLINT
    BitSet<4> aBits(a);
    BitSet<4> bBits(b);

    size_t res = 0;
    for (auto i : std::views::iota(0UZ, 32UZ))
        res += static_cast<size_t>(aBits.get(i) ^ bBits.get(i));

    return res;
};

auto V::pairwiseSwap(const uint &input) -> uint {
    BitSet<4> bits(input);

    for (auto i = 0; i < bits.size() - 1; i += 2) {
        auto tmp = bits.get(i);
        auto value = bits.get(i + 1);

        if (value)
            bits.set(i);
        else
            bits.clear(i);

        if (tmp)
            bits.set(i + 1);
        else
            bits.clear(i + 1);
    }

    return bits;
}
