#include "array.hpp"

#include <algorithm>
#include <concepts>
#include <cstddef>
#include <initializer_list>
#include <ranges>

namespace CTCI {

template <std::integral Ty, size_t Size> class BitsetImpl {
    Array<Ty, Size> _data;

    struct BitInfo {
        size_t bucket;
        size_t idx;
    };

    constexpr BitInfo calculateBucket(size_t idx) {
        return {
            .bucket = idx / (sizeof(Ty) * 8),
            .idx = idx % (sizeof(Ty) * 8),
        };
    }

  public:
    BitsetImpl() = default;

    template <std::integral T> BitsetImpl(T value) : _data(0) {
        constexpr auto bits = sizeof(T) * 8;
        static_assert(bits <= Size * (sizeof(Ty) * 8), "Input type size greater than capacity");

        for (auto i : std::views::iota(0UZ, bits)) {
            auto info = calculateBucket(i);
            auto bit = static_cast<bool>(value & (1 << i));

            _data[info.bucket] |= (bit << info.idx);
        }
    };

    BitsetImpl(std::initializer_list<Ty> list) {
        for (auto [data, value] : std::views::zip(_data, list))
            data |= value;
    }

    template <std::ranges::range R>
        requires(std::integral<typename R::value_type>)
    BitsetImpl(R &&rng) {}

    constexpr bool get(size_t idx) {
        auto info = calculateBucket(idx);
        return _data[info.bucket] & (1 << info.idx);
    }

    constexpr void set(size_t idx) {
        auto info = calculateBucket(idx);
        _data[info.bucket] |= (1 << info.idx);
    }

    constexpr void clear(size_t idx) {
        auto info = calculateBucket(idx);
        _data[info.bucket] &= ~(1 << info.idx);
    }

    [[nodiscard]] size_t size() { return Size * (sizeof(Ty) * 8); }

    template <std::integral U> operator U() const {
        static_assert(Size * sizeof(Ty) <= sizeof(U), "Data size greater than destination type");

        U ret = 0;
        for (auto [i, value] : std::views::enumerate(_data))
            ret |= value << (i * sizeof(Ty) * 8);

        return ret;
    }

    operator bool() const {
        return std::ranges::any_of(_data, [](const auto &value) { return static_cast<bool>(value); });
    }

    BitsetImpl operator~() {
        BitsetImpl tmp;
        for (auto [self, other] : std::views::zip(tmp._data, _data))
            self = ~other;
        return tmp;
    }

    BitsetImpl &operator&=(const BitsetImpl &rhs) {
        for (auto [self, other] : std::views::zip(_data, rhs._data))
            self &= other;

        return *this;
    }

    BitsetImpl &operator|=(const BitsetImpl &rhs) {
        for (auto [self, other] : std::views::zip(_data, rhs._data))
            self |= other;

        return *this;
    }
    
    friend BitsetImpl operator&(const BitsetImpl &lhs, const BitsetImpl &rhs) { return BitsetImpl(lhs) &= rhs; }
    friend BitsetImpl operator|(const BitsetImpl &lhs, const BitsetImpl &rhs) { return BitsetImpl(lhs) |= rhs; }

    friend bool operator==(const BitsetImpl &lhs, const BitsetImpl &rhs) {
        return std::ranges::all_of(std::views::zip(lhs._data, rhs._data),
                                   [](const auto &pair) { return std::get<0>(pair) == std::get<1>(pair); });
    }

    template <std::integral U> friend bool operator==(const BitsetImpl &lhs, U rhs) { return static_cast<U>(lhs) == rhs; }

    friend bool operator!=(const BitsetImpl &lhs, const BitsetImpl &rhs) { return !(lhs == rhs); }

    template <std::integral T> BitsetImpl &operator<<=(T shift) {
        if (shift >= size())
            return *this = BitsetImpl(0x0);

        if (shift == 0)
            return *this;

        auto rest = size() - shift;
        for (auto i : std::views::iota(0UZ, rest) | std::views::reverse) {
            if (get(i))
                set(shift + i);
            else
                clear(shift + i);
        }

        for (auto i : std::views::iota(static_cast<T>(0), shift))
            clear(i);

        return *this;
    }

    template <std::integral T> BitsetImpl &operator>>=(T shift) {
        if (shift >= size())
            return *this = BitsetImpl(0x0);

        if (shift == 0)
            return *this;

        constexpr size_t last = (Size * (sizeof(Ty) * 8)) - 1;
        auto rest = size() - shift;

        for (auto i : std::views::iota(0UZ, rest) | std::views::reverse) {
            if (get(last - i))
                set(last - shift - i);
            else
                clear(last - shift - i);
        }

        for (auto i : std::views::iota(size() - shift, size()))
            clear(i);

        return *this;
    }

    template <std::integral T> BitsetImpl operator<<(T shift) { return BitsetImpl(*this) <<= shift; }
    template <std::integral T> BitsetImpl operator>>(T shift) { return BitsetImpl(*this) >>= shift; }
};

template <size_t Size> using Bitset = BitsetImpl<unsigned char, Size>;

template <size_t Size> using SmallBitset = BitsetImpl<unsigned int, Size>;

template <size_t Size> using LargeBitset = BitsetImpl<unsigned long long, Size>;

} // namespace CTCI
