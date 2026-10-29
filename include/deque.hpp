#pragma once

#include "iterators.hpp"
#include "list.hpp"
#include "memory.hpp"
#include "vector.hpp"

namespace CTCI {

template <typename T> struct DNode {
    SharedPtr<DNode> prev = nullptr;
    SharedPtr<DNode> next = nullptr;
    T val = T{};

    DNode() = default;
    DNode(T val) : val(std::move(val)) {};
    DNode(T val, SharedPtr<DNode> next, SharedPtr<DNode> prev) // NOLINT
        : Node<T>(std::move(val), std::move(next)), prev(std::move(prev)) {};
};

template <typename T> struct Deque {
    using ValueType = T;
    using NodeType = DNode<T>;
    using Pointer = SharedPtr<NodeType>;
    Pointer head = nullptr;
    Pointer tail = nullptr;

    Deque() = default;

    Deque(std::initializer_list<T> list) {
        for (auto el : list)
            push(el);
    }

    Deque(const Vector<T> &vec) {
        for (auto el : vec)
            push(el);
    }

    ~Deque() {
        while (head) {
            head->prev = nullptr;
            head = head->next;
        }
    }

    [[nodiscard]] bool empty() const { return head == nullptr; }

    void push(T val) {
        auto ptr = CTCI::make_shared<NodeType>(std::move(val));
        push(std::move(ptr));
    }

    void push(Pointer ptr) {
        if (empty()) {
            head = ptr;
            tail = ptr;
            return;
        }

        tail->next = ptr;
        ptr->prev = tail;
        tail = ptr;
    }

    void popFront() {
        head = head->next;

        if (head) {
            head->prev = nullptr;
        } else {
            tail = nullptr;
        }
    }

    void popBack() {
        tail = tail->prev;
        if (tail) {
            tail->next = nullptr;
        } else {
            head = nullptr;
        }
    }

    void popMiddle(Pointer &ptr) {
        auto &prev = ptr->prev;
        auto &next = ptr->next;

        prev->next = next;
        next->prev = prev;
    }

    void pop(Pointer &ptr) {
        if (ptr == head)
            return popFront();

        if (ptr == tail)
            return popBack();

        return popMiddle(ptr);
    }

    using ConstForwardIterator = iterators::HeapIteratorImpl</**isConst=*/true, Pointer, ValueType>;
    using ForwardIterator = iterators::HeapIteratorImpl</**isConst=*/false, Pointer, ValueType>;

    ConstForwardIterator begin() const { return ConstForwardIterator{head}; }
    ForwardIterator begin() { return ForwardIterator{head}; }

    ConstForwardIterator end() const { return ConstForwardIterator{nullptr}; }
    ForwardIterator end() { return ForwardIterator{nullptr}; }
};

} // namespace CTCI
