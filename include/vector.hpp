#pragma once

#include "concepts.hpp"
#include "exceptions.hpp"
#include "iterators.hpp"
#include "memory.hpp"

#include <algorithm>
#include <concepts>
#include <cstring>
#include <initializer_list>
#include <ranges>
#include <type_traits>

namespace CTCI {

template <typename Ty, concepts::Allocator Allocator = Allocator<Ty>>
    requires std::movable<Ty> && std::copyable<Ty> ||
                 std::is_trivially_move_constructible_v<Ty> && std::is_trivially_copy_constructible_v<Ty>
                 class Vector {
    using RandomAccessIterator = iterators::ContiguousIteratorImpl<false, Ty>;
    using ConstRandomAccessIterator = iterators::ContiguousIteratorImpl<true, Ty>;

    Ty *_data = nullptr;
    size_t _capacity = 64;
    size_t _size = 0;
    Allocator _alloc;

    void adjustCapacity(size_t size) {
        while (_capacity <= size)
            _capacity <<= 1;
    }

    void transferData(Ty *src, Ty *dest, size_t size) {
        if constexpr (std::is_trivially_move_constructible_v<Ty>) {
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

        if constexpr (std::is_trivially_move_constructible_v<Ty>) {
            size_t offset = it - begin();
            if (it != end())
                std::memmove(_data + offset + insertingSize, _data + offset, sizeInBytes(_size - offset));
            std::memmove(_data + offset, values._data, sizeInBytes(insertingSize));
        } else {
            auto head = values.begin();
            auto left = it;
            auto right = end();

            *right = *left;
            *left = *head;

            (++head, ++left, ++right);
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

    Vector(size_t size) : _size(size) {
        adjustCapacity(_size);
        _data = _alloc.allocate(_capacity);
    }

    static size_t sizeInBytes(size_t size) { return size * sizeof(Ty); }

  public:
    Vector() : Vector(0) {};
    Vector(std::initializer_list<Ty> list) : Vector(std::ranges::subrange(list.begin(), list.end())) {}
    template <std::ranges::range R> Vector(R &&rng) : Vector(rng.size()) {
        for (auto [i, el] : std::views::enumerate(rng))
            _alloc.construct(_data + i, el);
    }
    Vector(size_t size, Ty value) : Vector(size) {
        for (auto i : std::views::iota(0UZ, size))
            _alloc.construct(_data + i, value);
    }
    template <typename... Args>
        requires(sizeof...(Args) > 0)
    Vector(size_t size, Args &&...args) : Vector(size) {
        for (auto i : std::views::iota(0UZ, size))
            _alloc.construct(_data + i, std::forward<Args>(args)...);
    }
    Vector(Vector &other) {
        _data = _alloc.allocate(other._capacity);
        _size = other._size;
        _capacity = other._capacity;
        _alloc = other._alloc;
        if constexpr (std::is_trivially_copy_constructible_v<Ty>) {
            std::memcpy(_data, other._data, sizeInBytes(other._size));
        } else {
            for (auto [actual, other] : std::views::zip(*this, other))
                actual = other;
        }
    }
    Vector(Vector &&other) noexcept {
        _data = other._data;
        _size = other._size;
        _capacity = other._capacity;
        _alloc = other._alloc;

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

    Ty at(size_t idx) {
        if (idx >= _size)
            throw OutOfRange{"[Index out of index bounds]"};
        return _data[idx];
    }

    Ty &operator[](size_t idx) { return _data[idx]; }

    void pushBack(Ty value) { insert(end(), {std::move(value)}); }
    void popBack() {
        destroyData(_data + _size - 1, 1);
        --_size;
    }

    void insert(RandomAccessIterator it, Ty value) { insertData(it, Vector<Ty>{std::move(value)}); }
    void insert(RandomAccessIterator it, std::initializer_list<Ty> list) { insertData(it, list); }
    template <std::ranges::range R> void insert(RandomAccessIterator it, R &&rng) { insertData(it, rng); }
    template <typename... Args> void emplaceBack(Args... args) { insertData(end(), Vector<Ty>{Ty{args...}}); }

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
                _data[startOffset++] = _data[endOffset++];
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

    [[nodiscard]] Ty front() const { return _data[0]; }
    [[nodiscard]] Ty back() const { return _data[_size - 1]; }

    RandomAccessIterator begin() { return {_data, 0UZ}; }
    RandomAccessIterator end() { return {_data, _size}; }

    ConstRandomAccessIterator begin() const { return {_data, 0UZ}; }
    ConstRandomAccessIterator end() const { return {_data, _size}; }

    /* STL Compatibility */
    void push_back(Ty value) { pushBack(std::move(value)); }
    void pop_back() { popBack(); }
    template <typename... Args> void emplace_back(Args... args) { emplaceBack(args...); }
};
} // namespace CTCI
