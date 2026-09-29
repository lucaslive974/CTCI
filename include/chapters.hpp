#pragma once
#include "chapter.hpp"
#include <algorithm>
#include <initializer_list>
#include <memory>
#include <unordered_map>
#include <vector>

namespace CTCI {

template <typename T> using Matrix = std::vector<std::vector<T>>;
// Just for better nomenclature when initializing a Matrix(a.k.a std::vector<std::vector<T>)
template <typename T> using Row = std::vector<T>;

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
    List(std::shared_ptr<node_type> node = nullptr) : head(node), tail(node) {}
    List(std::initializer_list<T> list) { appendToTail(list); }
    List(std::vector<T> &list) { appendToTail(list); }
    ~List() {
        if (empty())
            return;

        tail->next = nullptr;
        while (head != nullptr)
            head = head->next;
    };

    List(List &other) {
        auto el = other.head;
        for (; el != nullptr; el = el->next)
            appendToTail(el->val);
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

    void appendToTail(List &&other) {
        if (other.empty())
            return;

        tail->next = other.head;
        tail = other.tail;

        other.head = nullptr;
        other.tail = nullptr;
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

template <typename T> class Stack {
    std::vector<T> _data;

  public:
    Stack() = default;
    Stack(size_t capacity) : _data(capacity) {}
    Stack(std::initializer_list<T> list) : _data(list) {};
    Stack(std::vector<T> vec) : _data(vec) {};

    void push(T val) { _data.push_back(val); }
    T peek() const { return _data.back(); }
    void pop() { _data.pop_back(); }
    [[nodiscard]] bool empty() const { return _data.empty(); }
    [[nodiscard]] size_t size() const { return _data.size(); }
};

template <typename T> class SetOfStacks {
    std::vector<CTCI::Stack<T>> stacks;
    size_t threshold = 10;
    size_t totalSize = 0;

  public:
    SetOfStacks() = default;
    SetOfStacks(size_t threshold) : threshold(threshold) {}
    SetOfStacks(std::initializer_list<T> list, size_t threshold = 10) : threshold(threshold) { push(list); }

    void push(T val) {
        CTCI::Stack<T> *stack = numberOfStacks() == 0 ? &stacks.emplace_back() : &stacks.back();
        if (stack->size() >= threshold)
            stack = &stacks.emplace_back();

        stack->push(val);
        ++totalSize;
    }

    void push(std::initializer_list<T> list) {
        for (const T &el : list)
            push(el);
    }

    T peek() const { return stacks.back().peek(); }

    T peekAt(size_t index) const { return stacks[index].peek(); }

    void pop() {
        auto *stack = &stacks.back();
        stack->pop();
        --totalSize;

        while (stack->empty()) {
            stacks.pop_back();

            if (numberOfStacks() <= 0)
                break;
            stack = &stacks.back();
        }
    }

    void popAt(size_t index) {
        stacks[index].pop();
        --totalSize;

        if (stacks[index].empty())
            stacks.erase(stacks.begin() + index);
    }

    [[nodiscard]] size_t size() const { return totalSize; }

    [[nodiscard]] size_t sizeAt(size_t index) const { return stacks[index].size(); }

    [[nodiscard]] bool empty() const { return size() == 0; }

    [[nodiscard]] size_t numberOfStacks() const { return stacks.size(); };
};

template <typename T> class Queue {
    CTCI::Stack<T> frontStack;
    CTCI::Stack<T> rearStack;

  public:
    Queue() = default;
    Queue(std::initializer_list<T> list) {
        for (auto e : list)
            push(e);
    }
    T front() const { return frontStack.peek(); }
    bool empty() { return frontStack.empty(); }
    void push(T val) {
        if (empty())
            frontStack.push(val);
        else
            rearStack.push(std::move(val));
    }
    void pop() {
        frontStack.pop();

        if (frontStack.empty())
            while (!rearStack.empty()) {
                frontStack.push(rearStack.peek());
                rearStack.pop();
            }
    }
};

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
    static auto intersection(List<int> &a, List<int> &b) -> std::shared_ptr<Node<int>>;
    static auto loopDetection(List<int> &list) -> std::shared_ptr<Node<int>>;

    /* Stack */
    static auto sortStack(Stack<int> &stack) -> void;
};
} // namespace CTCI
