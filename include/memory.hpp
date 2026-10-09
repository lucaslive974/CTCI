#pragma once

#include <cstddef>
#include <type_traits>

namespace CTCI {

template <typename T> struct Allocator {
    using value_type = T;
    using pointer = T *;
    using const_pointer = const T*;
    using void_pointer = void *;
    using size_type = std::size_t;

    Allocator() = default;
    ~Allocator() = default;

    [[nodiscard]] pointer allocate(size_type n) {
        auto *ptr = ::operator new(sizeof(T) * n);

        return static_cast<T *>(ptr);
    };
    void deallocate(pointer p, size_type n) { ::operator delete(p); };

    template <typename... Args> void construct(pointer xp, Args... args) { ::new (xp) T(args...); };
    void destroy(pointer xp) {
        if constexpr (!std::is_trivially_destructible_v<T>) {
            xp->~T();
        }
    };

    friend bool operator==(const Allocator &a, const Allocator &b) { return true; }
    friend bool operator!=(const Allocator &a, const Allocator &b) { return !(a == b); }
};
} // namespace CTCI
