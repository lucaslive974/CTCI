#pragma once

#include <cassert>

#include <cstddef>
#include <initializer_list>
#include <iterator>
#include <type_traits>

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

    template <bool IsConst> class Iterator {
        Ty *data = nullptr;
        size_t pos = Size;

      public:
        using iterator_category = std::random_access_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = Ty;
        using pointer = std::conditional_t<IsConst, const Ty *, Ty *>;
        using reference = std::conditional_t<IsConst, const Ty &, Ty &>;

        Iterator() : data(nullptr), pos(Size) {};
        Iterator(Ty *data, size_t pos) : data(data), pos(pos) {};

        /* Input & Output */
        reference operator*() { return data[pos]; }
        reference operator*() const { return data[pos]; }
        pointer operator->() { return &data[pos]; }
        pointer operator->() const { return &data[pos]; }

        friend bool operator==(const Iterator &a, const Iterator &b) { return a.pos == b.pos; }
        friend bool operator!=(const Iterator &a, const Iterator &b) { return !(a == b); }

        /* Forward */
        Iterator &operator++() {
            ++pos;
            return *this;
        }

        Iterator operator++(int) {
            auto tmp = *this;
            ++(*this);
            return tmp;
        }

        /* Bidirectional */
        Iterator &operator--() {
            --pos;
            return *this;
        }

        Iterator operator--(int) {
            auto tmp = *this;
            --(*this);
            return tmp;
        }

        /* Random Access */
        friend bool operator<(const Iterator &a, const Iterator &b) { return a.pos < b.pos; }
        friend bool operator<=(const Iterator &a, const Iterator &b) { return a.pos <= b.pos; }
        friend bool operator>(const Iterator &a, const Iterator &b) { return a.pos > b.pos; }
        friend bool operator>=(const Iterator &a, const Iterator &b) { return a.pos >= b.pos; }

        Iterator &operator+=(difference_type n) {
            pos += n;
            return *this;
        }

        Iterator &operator-=(difference_type n) {
            pos -= n;
            return *this;
        }

        friend difference_type operator-(const Iterator &a, const Iterator &b) { return a.pos - b.pos; }

        reference operator[](difference_type n) const { return data[pos + n]; }

        friend Iterator operator+(const Iterator &a, const difference_type n) { return Iterator{a.data, a.pos + n}; }
        friend Iterator operator+(const difference_type n, const Iterator &a) { return Iterator{a.data, a.pos + n}; }
        friend Iterator operator-(const Iterator &a, const difference_type n) { return Iterator{a.data, a.pos - n}; }
    };

    using BidirectionalIterator = Iterator<false>;
    using ConstBidirectionalIterator = Iterator<true>;

    BidirectionalIterator begin() { return {data, 0UZ}; }
    BidirectionalIterator end() { return {data, Size}; }

    ConstBidirectionalIterator begin() const { return {const_cast<Ty *>(data), 0UZ}; }
    ConstBidirectionalIterator end() const { return {const_cast<Ty *>(data), Size}; }
};

} // namespace CTCI
