#pragma once

#include <cstddef>
#include <iterator>
#include <memory>
#include <type_traits>
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
    using ValueType = T;
    using NodeType = Node<ValueType>;
    using Pointer = std::shared_ptr<NodeType>;
    using ConstPointer = std::shared_ptr<const NodeType>;

    Pointer head = nullptr;
    Pointer tail = nullptr;
    size_t size = 0;

    List(Pointer node = nullptr) : head(node), tail(node) {}
    List(std::initializer_list<T> list) { push(list); }
    List(std::vector<T> &list) { push(list); }
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
        auto node = std::make_shared<NodeType>(val);
        push(node);
    }

    void push(std::initializer_list<T> list) {
        for (T item : list) {
            push(item);
        }
    }

    void push(std::vector<T> &list) {
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

    auto front() -> T { return head->val; }

    [[nodiscard]] bool empty() const { return !head; }

    template <bool isConst> class Iterator {
        std::conditional_t<isConst, ConstPointer, Pointer> node;

      public:
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = ValueType;
        using pointer = std::conditional_t<isConst, const ValueType *, ValueType *>;
        using reference = std::conditional_t<isConst, const ValueType &, ValueType &>;

        Iterator() : node(nullptr) {}
        explicit Iterator(std::conditional_t<isConst, ConstPointer, Pointer> node) : node(node) {}

        reference operator*() const { return node->val; }
        reference operator*() { return node->val; }

        pointer operator->() const { return &node->val; }
        pointer operator->() { return &node->val; }

        Iterator &operator++() {
            node = node->next;
            return *this;
        }

        Iterator &operator++(int) {
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        friend bool operator==(const Iterator &a, const Iterator &b) { return a.node == b.node; }
        friend bool operator!=(const Iterator &a, const Iterator &b) { return a.node != b.node; }
    };

    using ConstForwardIterator = Iterator</**isConst=*/true>;
    using ForwardIterator = Iterator</**isConst=*/false>;

    ConstForwardIterator begin() const { return ConstForwardIterator{head}; }
    ForwardIterator begin() { return ForwardIterator{head}; }

    ConstForwardIterator end() const { return ConstForwardIterator{nullptr}; }
    ForwardIterator end() { return ForwardIterator{nullptr}; }
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
