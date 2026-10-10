#pragma once

#include "concepts.hpp"
#include "exceptions.hpp"
#include "iterators.hpp"
#include "memory.hpp"

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

    size_t sizeInBytes(size_t size) { return size * sizeof(Ty); }

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
                _alloc.destroy(_data + i);
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

  public:
    Vector(size_t size) : _size(size) {
        adjustCapacity(_size);
        _data = _alloc.allocate(_capacity);
    }

    Vector() : Vector(0) {};

    Vector(std::initializer_list<Ty> list) : Vector(std::ranges::subrange(list.begin(), list.end())) {}

    template <std::ranges::range R> Vector(R &&rng) : Vector(rng.size()) {
        for (auto [idx, el] : std::views::enumerate(rng))
            _data[idx] = el;
    }

    template <typename... Args> Vector(size_t size, Args &&...args) : Vector(size) {
        for (auto i : std::views::iota(0UZ, size))
            _alloc.construct(_data + i, std::forward<Args &&...>(args...));
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

    void insert(RandomAccessIterator it, Ty value) { insertData(it, Vector<Ty>{value}); }
    void insert(RandomAccessIterator it, std::initializer_list<Ty> list) { insertData(it, list); }
    template <std::ranges::range R> void insert(RandomAccessIterator it, R &&rng) { insertData(it, rng); }

    [[nodiscard]] size_t size() const { return _size; }
    [[nodiscard]] size_t capacity() const { return _capacity; }

    RandomAccessIterator begin() { return {_data, 0UZ}; }
    RandomAccessIterator end() { return {_data, _size}; }

    ConstRandomAccessIterator begin() const { return {_data, 0UZ}; }
    ConstRandomAccessIterator end() const { return {_data, _size}; }
};
} // namespace CTCI
