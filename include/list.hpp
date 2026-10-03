#pragma once

#include <memory>
#include <vector>

namespace CTCI {

template <typename T> struct Node {
    std::shared_ptr<Node> next = nullptr;
    T val = T{};

    Node() = default;
    Node(T val) : val(std::move(val)) {};
    Node(T val, std::shared_ptr<Node> next) : Node(std::move(val)), next(std::move(next)) {};
};

template <typename T> struct List {
    using value_type = T;
    using node_type = Node<value_type>;

    std::shared_ptr<node_type> head = nullptr;
    std::shared_ptr<node_type> tail = nullptr;
    List(std::shared_ptr<node_type> node = nullptr) : head(node), tail(node) {}
    List(std::initializer_list<T> list) { append(list); }
    List(std::vector<T> &list) { append(list); }
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
            append(el->val);
    }

    List(List &&other) noexcept {
        head = other.head;
        tail = other.tail;

        other.head = nullptr;
        other.tail = nullptr;
    }

    List &operator=(List other) noexcept {
        swap(head, other.head);
        swap(tail, other.tail);
        return *this;
    }

    void append(T val) {
        auto node = std::make_shared<node_type>(val);
        append(node);
    }

    void append(std::initializer_list<T> list) {
        for (T item : list) {
            append(item);
        }
    }

    void append(std::vector<T> &list) {
        for (T &item : list) {
            append(item);
        }
    }

    void append(std::shared_ptr<node_type> &node) {
        if (!head) {
            head = node;
            tail = node;
            return;
        }

        tail->next = node;
        tail = node;
    }

    void append(List &&other) {
        if (other.empty())
            return;

        tail->next = other.head;
        tail = other.tail;

        other.head = nullptr;
        other.tail = nullptr;
    }

    void pop() {
        head = head->next;
        if (empty())
            tail = nullptr;
    }

    auto front() -> T { return head->val; }

    [[nodiscard]] bool empty() const { return !head; }
};

template <typename T> using Queue = List<T>;

template <typename T> auto revertLinkedList(std::shared_ptr<Node<T>> &node) -> void {
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
