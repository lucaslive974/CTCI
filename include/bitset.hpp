#include "array.hpp"

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
    BitSetImpl(long long data) : _data(data) {};

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

    [[nodiscard]] size_t size() const { return Size * sizeof(Ty); }
};

template <size_t Size> using BitSet = BitSetImpl<unsigned char, Size>;

template <size_t Size> using SmallBitSet = BitSetImpl<unsigned int, Size>;

template <size_t Size> using LargeBitSet = BitSetImpl<unsigned long long, Size>;

} // namespace CTCI
