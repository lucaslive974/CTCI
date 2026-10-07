#pragma once
#include <functional>

template <typename T>
concept Hashable = requires(T a) {
    { std::hash<T>{}(a) } -> std::same_as<std::size_t>;
} && std::equality_comparable<T>;
