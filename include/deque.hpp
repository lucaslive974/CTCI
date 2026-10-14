#pragma once

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
    using nodeType = DNode<T>;
    using nodePtr = SharedPtr<nodeType>;
    nodePtr head = nullptr;
    nodePtr tail = nullptr;

    Deque() = default;

    Deque(std::initializer_list<T> list) {
        for (auto el : list)
            append(el);
    }

    Deque(const Vector<T> &vec) {
        for (auto el : vec)
            append(el);
    }

    ~Deque() {
        while (head) {
            head->prev = nullptr;
            head = head->next;
        }
    }

    [[nodiscard]] bool empty() const { return head == nullptr; }

    void append(T val) {
        auto ptr = CTCI::make_shared<nodeType>(std::move(val));
        append(std::move(ptr));
    }

    void append(nodePtr ptr) {
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

    void popMiddle(nodePtr &ptr) {
        auto &prev = ptr->prev;
        auto &next = ptr->next;

        prev->next = next;
        next->prev = prev;
    }

    void pop(nodePtr &ptr) {
        if (ptr == head)
            return popFront();

        if (ptr == tail)
            return popBack();

        return popMiddle(ptr);
    }
};

} // namespace CTCI
