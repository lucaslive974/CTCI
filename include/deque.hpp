#pragma once

#include "list.hpp"
#include <memory>
#include <vector>

namespace CTCI {

template <typename T> struct DNode {
    std::shared_ptr<DNode> prev = nullptr;
    std::shared_ptr<DNode> next = nullptr;
    T val = T{};

    DNode() = default;
    DNode(T val) : val(std::move(val)) {};
    DNode(T val, std::shared_ptr<DNode> next, std::shared_ptr<DNode> prev) // NOLINT
        : Node<T>(std::move(val), std::move(next)), prev(std::move(prev)) {};
};

template <typename T> struct Deque {
    using nodeType = DNode<T>;
    using nodePtr = std::shared_ptr<nodeType>;
    nodePtr head = nullptr;
    nodePtr tail = nullptr;

    Deque() = default;
    Deque(std::initializer_list<T> list) { append(list); }
    Deque(std::vector<T> vec) { append(vec); }
    ~Deque() {
        while (head) {
            head->prev = nullptr;
            head = head->next;
        }
    }
    [[nodiscard]] bool empty() const { return head == nullptr; }

    void append(T &&val) {
        auto ptr = std::make_shared<nodeType>(std::forward<T &&>(val));
        append(ptr);
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

    void append(std::initializer_list<T> list) {
        for (auto el : list)
            append(std::move(el));
    }

    void append(std::vector<T> vec) {
        for (auto el : vec)
            append(el);
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
