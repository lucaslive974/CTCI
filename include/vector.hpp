#pragma once

#include "concepts.hpp"
#include "exceptions.hpp"
#include "iterators.hpp"
#include "memory.hpp"

#include <algorithm>
#include <concepts>
#include <cstring>
#include <initializer_list>
#include <iterator>
#include <ranges>
#include <type_traits>

namespace CTCI {

template <typename Ty, concepts::Allocator Allocator = Allocator<Ty>>
    requires concepts::Movable<Ty> || concepts::Copyable<Ty>
class Vector {
    using RandomAccessIterator = iterators::ContiguousIteratorImpl<false, Ty>;
    using ConstRandomAccessIterator = iterators::ContiguousIteratorImpl<true, Ty>;

    Ty *_data = nullptr;
    size_t _capacity = 64;
    size_t _size = 0;
    [[no_unique_address]] Allocator _alloc;

    void adjustCapacity(size_t size) {
        while (_capacity <= size)
            _capacity <<= 1;
    }

    void transferData(Ty *src, Ty *dest, size_t size) {
        if constexpr (std::is_trivially_copyable_v<Ty>) {
            std::memmove(dest, src, sizeInBytes(size));
        } else {
            for (auto i : std::views::iota(0UZ, size))
                dest[i] = std::move(src[i]);
        }
    }

    void destroyData(Ty *data, size_t size) {
        if constexpr (!std::is_trivially_destructible_v<Ty>) {
            for (auto i : std::views::iota(0UZ, size))
                _alloc.destroy(data + i);
        }
    }

    void insertData(RandomAccessIterator it, Vector<Ty> values) {
        auto insertingSize = values.size();
        if (_capacity <= _size + insertingSize) {
            resize(_capacity + insertingSize);
            it = RandomAccessIterator{_data, static_cast<size_t>(it - begin())};
        }

        if constexpr (std::is_trivially_copyable_v<Ty>) {
            size_t offset = it - begin();
            if (it != end())
                std::memmove(_data + offset + insertingSize, _data + offset, sizeInBytes(_size - offset));
            std::memmove(_data + offset, values._data, sizeInBytes(insertingSize));
        } else {
            auto left = it - begin();
            auto right = end() - begin();

            for (auto idx : std::views::iota(0UZ, values.size())) {
                _alloc.construct(_data + right + idx, std::move(*(_data + left + idx)));
                _alloc.construct(_data + left + idx, std::move(values[idx]));
            }
        }

        _size += values.size();
    }

    void resize(size_t newSize) {
        adjustCapacity(newSize);
        Ty *dest = _alloc.allocate(_capacity);
        transferData(_data, dest, _size);
        destroyData(_data, _size);
        _alloc.deallocate(_data, _size);
        _data = dest;
    }

    void _init(size_t size) {
        adjustCapacity(size);
        _data = _alloc.allocate(_capacity);
        _size = size;
    }

    static size_t sizeInBytes(size_t size) { return size * sizeof(Ty); }

  public:
    Vector() { _init(0); };

    Vector(const Vector &other)
        requires concepts::Copyable<Ty>
    {
        _data = _alloc.allocate(other._capacity);
        _size = other._size;
        _capacity = other._capacity;

        if constexpr (std::is_trivially_copyable_v<Ty>) {
            std::memcpy(_data, other._data, sizeInBytes(other._size));
        } else {
            for (auto idx : std::views::iota(0UZ, other.size()))
                _alloc.construct(_data + idx, other[idx]);
        }
    }

    Vector(Vector &&other) noexcept {
        _data = other._data;
        _size = other._size;
        _capacity = other._capacity;

        other._data = nullptr;
        other._size = 0;
        other._capacity = 64;
    }

    Vector &operator=(Vector other) {
        using std::swap;
        swap(_data, other._data);
        swap(_size, other._size);
        swap(_capacity, other._capacity);
        swap(_alloc, other._alloc);
        return *this;
    }

    ~Vector() {
        destroyData(_data, _size);
        _alloc.deallocate(_data, _capacity);
    }

    Vector(std::initializer_list<Ty> list) : Vector(list.begin(), list.end(), list.size()) {}

    template <std::ranges::bidirectional_range R>
        requires(!std::same_as<std::remove_cvref_t<R>, Vector> && !std::ranges::sized_range<R>)
    Vector(R &&rng) : Vector(rng.begin(), rng.end(), rng.end() - rng.begin()) {}

    template <std::ranges::range R>
        requires(!std::same_as<std::remove_cvref_t<R>, Vector> && std::ranges::sized_range<R>)
    Vector(R &&rng) : Vector(rng.begin(), rng.end(), std::ranges::size(rng)) {}

    template <typename Iterator>
        requires std::input_iterator<Iterator>
    Vector(Iterator begin, Iterator end) : Vector(begin, end, end - begin) {}

    template <typename Iterator>
        requires std::input_iterator<Iterator>
    Vector(Iterator begin, Iterator end, size_t size) {
        _init(size);

        size_t i = 0;
        while (begin != end) {
            _alloc.construct(_data + i, std::move(*begin));
            (++i, ++begin);
        }
    }

    Vector(size_t size) {
        _init(size);
        for (auto i : std::views::iota(0UZ, size))
            _alloc.construct(_data + i, std::move(Ty{}));
    }

    Vector(size_t size, const Ty value) {
        _init(size);
        for (auto i : std::views::iota(0UZ, size))
            _alloc.construct(_data + i, value);
    }

    template <typename... Args>
    Vector(size_t size, Args &&...args)
        requires(sizeof...(Args) > 0)
    {
        _init(size);
        for (auto i : std::views::iota(0UZ, size))
            _alloc.construct(_data + i, std::forward<Args>(args)...);
    }

    Ty &at(size_t idx) const {
        if (idx >= _size)
            throw OutOfRange{"[Index out of index bounds]"};
        return _data[idx];
    }

    Ty &operator[](size_t idx) const { return _data[idx]; }

    void pushBack(Ty value) { emplaceBack(std::move(value)); }
    void popBack() {
        destroyData(_data + _size - 1, 1);
        --_size;
    }

    void insert(RandomAccessIterator it, Ty value) { insertData(it, Vector<Ty>{std::move(value)}); }
    void insert(RandomAccessIterator it, std::initializer_list<Ty> list) { insertData(it, list); }
    template <std::ranges::range R> void insert(RandomAccessIterator it, R &&rng) { insertData(it, std::forward<R>(rng)); }
    template <typename... Args> Ty &emplaceBack(Args &&...args) {
        if (_size + 1 >= _capacity)
            resize(_capacity);
        _alloc.construct(_data + _size, std::forward<Args>(args)...);
        ++_size;

        return back();
    }

    void erase(RandomAccessIterator first) { erase(first, first); }
    void erase(RandomAccessIterator first, RandomAccessIterator second) {
        auto startOffset = first - begin();
        auto endOffset = (second - begin()) + 1;
        auto amount = second - first + 1;

        destroyData(_data + startOffset, amount);
        if constexpr (std::is_trivially_move_constructible_v<Ty>) {
            std::memmove(_data + startOffset, _data + endOffset, end() - second);
        } else {
            while (endOffset < size())
                _alloc.construct(_data + startOffset++, std::move(_data[endOffset++]));
        }

        _size -= amount;
    }

    void clear() {
        destroyData(_data, _size);
        _size = 0;
    }

    /* Equality */
    friend bool operator==(const Vector &a, const Vector &b) {
        return !std::ranges::any_of(std::views::zip(a, b), [](auto tuple) {
            auto [va, vb] = tuple;
            return va != vb;
        });
    }
    friend bool operator!=(const Vector &a, const Vector &b) { return !(a == b); }

    [[nodiscard]] size_t size() const { return _size; }
    [[nodiscard]] size_t capacity() const { return _capacity; }
    [[nodiscard]] bool empty() const { return _size == 0; }

    [[nodiscard]] Ty *data() { return _data; }
    [[nodiscard]] const Ty *cdata() { return _data; }

    [[nodiscard]] Ty &front() const { return _data[0]; }
    [[nodiscard]] Ty &back() const { return _data[_size - 1]; }

    RandomAccessIterator begin() { return {_data, 0UZ}; }
    RandomAccessIterator end() { return {_data, _size}; }

    ConstRandomAccessIterator begin() const { return {_data, 0UZ}; }
    ConstRandomAccessIterator end() const { return {_data, _size}; }

    /* STL Compatibility */
    void push_back(Ty value) { pushBack(std::move(value)); }
    void pop_back() { popBack(); }
    template <typename... Args> Ty &emplace_back(Args &&...args) { return emplaceBack(std::forward<Args>(args)...); }
};
} // namespace CTCI
