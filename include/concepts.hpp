#pragma once
#include <functional>
#include <utility>

namespace CTCI::concepts {
    template <typename T>
    concept Hashable = requires(T a) {
        { std::hash<T>{}(a) } -> std::same_as<std::size_t>;
    } && std::equality_comparable<T>;

    template <typename Alloc, typename... Args>
    concept Allocator = requires(Alloc alloc, Args... args) {
        { alloc.allocate(1) } -> std::same_as<typename Alloc::pointer>;
        { alloc.construct(std::declval<typename Alloc::pointer>(), args...) } -> std::same_as<void>;
        { alloc.destroy(std::declval<typename Alloc::pointer>()) } -> std::same_as<void>;
        { alloc.deallocate(std::declval<typename Alloc::pointer>(), 1) } -> std::same_as<void>;
    };
} // namespace CTCI::Concepts
