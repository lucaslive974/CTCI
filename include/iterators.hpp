#pragma once

#include <iterator>

namespace CTCI::iterators {

template <bool IsConst, typename Ty> class ContiguousIteratorImpl {
    Ty *data = nullptr;
    size_t pos = 0;

  public:
    using iterator_category = std::random_access_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = Ty;
    using pointer = std::conditional_t<IsConst, const Ty *, Ty *>;
    using reference = std::conditional_t<IsConst, const Ty &, Ty &>;

    ContiguousIteratorImpl() = default;
    ContiguousIteratorImpl(Ty *data, size_t pos) : data(data), pos(pos) {};

    /* Input & Output */
    reference operator*() { return data[pos]; }
    reference operator*() const { return data[pos]; }
    pointer operator->() { return &data[pos]; }
    pointer operator->() const { return &data[pos]; }

    friend bool operator==(const ContiguousIteratorImpl &a, const ContiguousIteratorImpl &b) { return a.pos == b.pos; }
    friend bool operator!=(const ContiguousIteratorImpl &a, const ContiguousIteratorImpl &b) { return !(a == b); }

    /* Forward */
    ContiguousIteratorImpl &operator++() {
        ++pos;
        return *this;
    }

    ContiguousIteratorImpl operator++(int) {
        auto tmp = *this;
        ++(*this);
        return tmp;
    }

    /* Bidirectional */
    ContiguousIteratorImpl &operator--() {
        --pos;
        return *this;
    }

    ContiguousIteratorImpl operator--(int) {
        auto tmp = *this;
        --(*this);
        return tmp;
    }

    /* Random Access */
    friend bool operator<(const ContiguousIteratorImpl &a, const ContiguousIteratorImpl &b) { return a.pos < b.pos; }
    friend bool operator<=(const ContiguousIteratorImpl &a, const ContiguousIteratorImpl &b) { return a.pos <= b.pos; }
    friend bool operator>(const ContiguousIteratorImpl &a, const ContiguousIteratorImpl &b) { return a.pos > b.pos; }
    friend bool operator>=(const ContiguousIteratorImpl &a, const ContiguousIteratorImpl &b) { return a.pos >= b.pos; }

    ContiguousIteratorImpl &operator+=(difference_type n) {
        pos += n;
        return *this;
    }

    ContiguousIteratorImpl &operator-=(difference_type n) {
        pos -= n;
        return *this;
    }

    friend difference_type operator-(const ContiguousIteratorImpl &a, const ContiguousIteratorImpl &b) {
        return a.pos - b.pos;
    }

    reference operator[](difference_type n) const { return data[pos + n]; }

    friend ContiguousIteratorImpl operator+(const ContiguousIteratorImpl &a, const difference_type n) {
        return ContiguousIteratorImpl{a.data, a.pos + n};
    }
    friend ContiguousIteratorImpl operator+(const difference_type n, const ContiguousIteratorImpl &a) {
        return ContiguousIteratorImpl{a.data, a.pos + n};
    }
    friend ContiguousIteratorImpl operator-(const ContiguousIteratorImpl &a, const difference_type n) {
        return ContiguousIteratorImpl{a.data, a.pos - n};
    }
};
} // namespace CTCI::iterators
