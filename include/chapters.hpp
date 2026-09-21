#pragma once
#include "chapter.hpp"
#include <initializer_list>
#include <memory>
#include <vector>

namespace CTCI {

template <typename T> using Matrix = std::vector<std::vector<T>>;
// Just for better nomenclature when initializing a Matrix(a.k.a std::vector<std::vector<T>)
template <typename T> using Row = std::vector<int>;

template <typename T> struct Node {
    std::shared_ptr<Node> next = nullptr;
    T val = T{};

    Node() = default;
    Node(T val) : val(val) {};
    Node(T val, std::shared_ptr<Node> next) : val(val), next(next) {};
};

template <typename T> struct List {
    using value_type = T;
    using node_type = Node<value_type>;

    std::shared_ptr<node_type> head = nullptr;
    std::shared_ptr<node_type> tail = nullptr;
    List(std::shared_ptr<node_type> head = nullptr) : head(head) {}
    List(std::initializer_list<T> list) { appendToTail(list); }
    List(std::vector<T> &list) { appendToTail(list); }
    ~List() {
        while (head)
            head = head->next;
    };

    List(List &list) {
        auto el = list.head;
        for (; el != nullptr; el = el->next)
            appendToTail(el->val);
    }

    List(List &&list) noexcept {
        head = list.head;
        tail = list.tail;

        list.head = nullptr;
        list.tail = nullptr;
    }

    List &operator=(List other) noexcept {
        swap(head, other.head);
        swap(tail, other.tail);
        return *this;
    }

    void appendToTail(T val) {
        auto node = std::make_shared<node_type>(val);
        appendToTail(node);
    }

    void appendToTail(std::initializer_list<T> list) {
        for (T item : list) {
            appendToTail(item);
        }
    }

    void appendToTail(std::vector<T> &list) {
        for (T &item : list) {
            appendToTail(item);
        }
    }

    void appendToTail(std::shared_ptr<node_type> &node) {
        if (!head) {
            head = node;
            tail = node;
            return;
        }

        tail->next = node;
        tail = node;
    }

    [[nodiscard]] bool empty() const { return !head; }
};

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

class IX : public Chapter {
  public:
    IX(std::string name = "CTCI::IX::Exercises");
    /* Arrays */
    static auto isUnique(const std::string &s) -> bool;
    static auto checkPermutation(const std::string &s1, const std::string &s2) -> bool;
    static auto urlify(std::string s, size_t length) -> std::string;
    static auto palindromePerm(const std::string &s) -> bool;
    static auto oneAway(std::string &s1, std::string &s2) -> bool;
    static auto stringCompression(const std::string &s1) -> std::string;
    static auto rotateMatrix(std::vector<std::vector<int>> &matrix) -> void;
    static auto zeroMatrix(std::vector<std::vector<int>> &matrix) -> void;
    static auto stringRotation(std::string s1, const std::string &s2) -> bool;

    /* Lists */
    static auto removeDups(List<int> &list) -> void;
    static auto kthLast(const List<int> &list, size_t k) -> int;
    static auto deleteMiddleNode(std::shared_ptr<Node<int>> &node) -> void;
    static auto partition(List<int> &list, int x) -> void;
    static auto sumLists(List<int> &a, List<int> &b) -> List<int>;
    static auto palindrome(List<char> &list) -> bool;
};
} // namespace CTCI
