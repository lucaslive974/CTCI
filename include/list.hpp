#pragma once

#include "iterators.hpp"
#include "memory.hpp"
#include "vector.hpp"

#include <cstddef>

namespace CTCI {

template <typename T> struct Node {
    SharedPtr<Node> next = nullptr;
    T val = T{};

    Node() = default;
    Node(T val) : val(std::move(val)) {};
    Node(T val, SharedPtr<Node> next) : Node(std::move(val)), next(std::move(next)) {};
};

template <typename T> struct List {
    using ValueType = T;
    using NodeType = Node<ValueType>;
    using Pointer = SharedPtr<NodeType>;
    using ConstPointer = SharedPtr<const NodeType>;

    Pointer head = nullptr;
    Pointer tail = nullptr;
    size_t size = 0;

    List(Pointer node = nullptr) : head(node), tail(node) {}
    List(std::initializer_list<T> list) { push(list); }
    List(Vector<T> &list) { push(list); }
    ~List() {
        if (empty())
            return;

        tail->next = nullptr;
        while (head != nullptr)
            head = head->next;
    };

    List(const List &other) {
        auto el = other.head;
        for (; el != nullptr; el = el->next)
            push(el->val);
    }

    List(List &&other) noexcept {
        head = other.head;
        tail = other.tail;
        size = other.size;

        other.head = nullptr;
        other.tail = nullptr;
        other.size = 0;
    }

    List &operator=(List other) noexcept {
        using std::swap;
        swap(head, other.head);
        swap(tail, other.tail);
        swap(size, other.size);
        return *this;
    }

    void push(T val) {
        auto node = CTCI::make_shared<NodeType>(std::move(val));
        push(node);
    }

    void push(std::initializer_list<T> list) {
        for (T item : list) {
            push(item);
        }
    }

    void push(Vector<T> &list) {
        for (T &item : list) {
            push(item);
        }
    }

    void push(Pointer &node) {
        ++size;

        if (!head) {
            head = node;
            tail = node;
            return;
        }

        tail->next = node;
        tail = node;
    }

    void push(List &&other) {
        if (other.empty())
            return;

        tail->next = other.head;
        tail = other.tail;
        size += other.size;

        other.head = nullptr;
        other.tail = nullptr;
        other.size = 0;
    }

    void pop() {
        --size;

        head = head->next;
        if (empty())
            tail = nullptr;
    }

    auto front() -> T & { return head->val; }

    [[nodiscard]] bool empty() const { return !head; }

    using ConstForwardIterator = iterators::HeapIteratorImpl</**isConst=*/true, Pointer, ValueType>;
    using ForwardIterator = iterators::HeapIteratorImpl</**isConst=*/false, Pointer, ValueType>;

    ConstForwardIterator begin() const { return ConstForwardIterator{head}; }
    ForwardIterator begin() { return ForwardIterator{head}; }

    ConstForwardIterator end() const { return ConstForwardIterator{nullptr}; }
    ForwardIterator end() { return ForwardIterator{nullptr}; }
};

template <typename T> using Queue = List<T>;

template <typename T> auto revertLinkedList(SharedPtr<Node<T>> &node) -> void {
    if (node == nullptr)
        return;

    auto p = node;
    auto m = p->next;

    p->next = nullptr;
    while (m != nullptr) {
        auto n = m->next;

        m->next = p;
        p = m;
        m = n;
    }
}

template <typename T> auto revertLinkedList(List<T> &list) -> void {
    revertLinkedList(list.head);
    std::swap(list.head, list.tail);
}

} // namespace CTCI
