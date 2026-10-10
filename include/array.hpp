#pragma once

#include "iterators.hpp"

#include <cassert>
#include <cstddef>
#include <initializer_list>

namespace CTCI {

template <typename Ty, size_t Size> class Array {
    Ty data[Size]; // NOLINT

  public:
    Array() = default;
    constexpr Array(std::initializer_list<Ty> list) {
        size_t npos = 0;
        for (auto &el : list)
            data[npos++] = el;
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
