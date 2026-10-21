#include "array.hpp"

#include <algorithm>
#include <concepts>
#include <cstddef>
#include <initializer_list>
#include <ranges>

namespace CTCI {

template <std::integral Ty, size_t Size> class BitSetImpl {
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
    BitSetImpl() = default;

    template <std::integral T> BitSetImpl(T value) : _data(0) {
        constexpr auto bits = sizeof(T) * 8;
        static_assert(bits <= Size * (sizeof(Ty) * 8), "Input type size greater than capacity");

        for (auto i : std::views::iota(0UZ, bits)) {
            auto info = calculateBucket(i);
            auto bit = static_cast<bool>(value & (1 << i));

            _data[info.bucket] |= (bit << info.idx);
        }
    };

    BitSetImpl(std::initializer_list<Ty> list) {
        for (auto [data, value] : std::views::zip(_data, list))
            data |= value;
    }

    template <std::ranges::range R>
        requires(std::integral<typename R::value_type>)
    BitSetImpl(R &&rng) {}

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
        static_assert(sizeof(U) <= Size * sizeof(Ty), "Data size greater than destination type");

        U ret = 0;
        for (auto [i, value] : std::views::enumerate(_data))
            ret |= value << (i * sizeof(Ty) * 8);

        return ret;
    }

    operator bool() const {
        return std::ranges::any_of(_data, [](const auto &value) { return static_cast<bool>(value); });
    }

    BitSetImpl &operator~() {
        for (auto &value : _data)
            value = ~value;
        return *this;
    }

    BitSetImpl &operator&=(const BitSetImpl &rhs) {
        for (auto [self, other] : std::views::zip(_data, rhs._data))
            self &= other;

        return *this;
    }

    BitSetImpl &operator|=(const BitSetImpl &rhs) {
        for (auto [self, other] : std::views::zip(_data, rhs._data))
            self |= other;

        return *this;
    }

    friend BitSetImpl operator&(const BitSetImpl &lhs, const BitSetImpl &rhs) { return BitSetImpl(lhs) &= rhs; }
    friend BitSetImpl operator|(const BitSetImpl &lhs, const BitSetImpl &rhs) { return BitSetImpl(lhs) |= rhs; }

    friend bool operator==(const BitSetImpl &lhs, const BitSetImpl &rhs) {
        return std::ranges::all_of(std::views::zip(lhs._data, rhs._data),
                                   [](const auto &pair) { return std::get<0>(pair) == std::get<1>(pair); });
    }

    friend bool operator!=(const BitSetImpl &lhs, const BitSetImpl &rhs) { return !(lhs == rhs); }
};

template <size_t Size> using BitSet = BitSetImpl<unsigned char, Size>;

template <size_t Size> using SmallBitSet = BitSetImpl<unsigned int, Size>;

template <size_t Size> using LargeBitSet = BitSetImpl<unsigned long long, Size>;

} // namespace CTCI
