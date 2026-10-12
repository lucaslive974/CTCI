#pragma once

#include "vector.hpp"

namespace CTCI {

template <typename T> class Stack {
    Vector<T> _data;

  public:
    Stack() = default;
    Stack(size_t capacity) : _data(capacity) {}
    Stack(std::initializer_list<T> list) : _data(list) {};
    Stack(Vector<T> vec) : _data(vec) {};

    void push(T val) { _data.push_back(val); }
    T peek() const { return _data.back(); }
    void pop() { _data.pop_back(); }
    [[nodiscard]] bool empty() const { return _data.empty(); }
    [[nodiscard]] size_t size() const { return _data.size(); }
};

} // namespace CTCI
