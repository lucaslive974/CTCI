#pragma once

#include "concepts.hpp"
#include "iterators.hpp"
#include "memory.hpp"

#include <cassert>
#include <cstddef>
#include <initializer_list>
#include <ranges>
#include <type_traits>

namespace CTCI {

template <typename Ty, size_t Size, concepts::Allocator Allocator = Allocator<Ty>> class Array {
    Ty data[Size]; // NOLINT
    [[no_unique_address]] Allocator _alloc;

    template <typename... Args> void _init(Args &&...args) {
        for (auto i : std::views::iota(0UZ, Size))
            _alloc.construct(data + i, std::forward<Args>(args)...);
    }

  public:
    Array() { _init(); };
    Array(Ty value) { _init(value); }
    constexpr Array(std::initializer_list<Ty> list) {
        size_t npos = 0;
        for (auto &el : list)
            data[npos++] = el;
    }

    ~Array() {
        if constexpr (!std::is_trivially_destructible_v<Ty>)
            for (auto i : std::views::iota(0UZ, Size))
                _alloc.destroy(data + i);
    }

    Ty &operator[](size_t idx) { return data[idx]; }

    constexpr size_t size() { return Size; }

    using RandomAccessIterator = iterators::ContiguousIteratorImpl<false, Ty>;
    using ConstRandomAccessIterator = iterators::ContiguousIteratorImpl<true, Ty>;

    RandomAccessIterator begin() { return {data, 0UZ}; }
    RandomAccessIterator end() { return {data, Size}; }

    ConstRandomAccessIterator begin() const { return {const_cast<Ty *>(data), 0UZ}; }
    ConstRandomAccessIterator end() const { return {const_cast<Ty *>(data), Size}; }
};

} // namespace CTCI
