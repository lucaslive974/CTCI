#pragma once
#include "chapter.hpp"
#include <algorithm>
#include <concepts>
#include <initializer_list>
#include <memory>
#include <ranges>
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

    List(List &other) {
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

    auto front() -> std::shared_ptr<node_type> { return head; }

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

class I : public Chapter {
  public:
    I(std::string name = "CTCI::I::Arrays and Strings");
    static auto isUnique(const std::string &s) -> bool;
    static auto checkPermutation(const std::string &s1, const std::string &s2) -> bool;
    static auto urlify(std::string s, size_t length) -> std::string;
    static auto palindromePerm(const std::string &s) -> bool;
    static auto oneAway(std::string &s1, std::string &s2) -> bool;
    static auto stringCompression(const std::string &s1) -> std::string;
    static auto rotateMatrix(std::vector<std::vector<int>> &matrix) -> void;
    static auto zeroMatrix(std::vector<std::vector<int>> &matrix) -> void;
    static auto stringRotation(std::string s1, const std::string &s2) -> bool;
};

class II : public Chapter {
  public:
    II(std::string name = "CTCI::II::Linked Lists");
    static auto removeDups(List<int> &list) -> void;
    static auto kthLast(const List<int> &list, size_t k) -> int;
    static auto deleteMiddleNode(std::shared_ptr<Node<int>> &node) -> void;
    static auto partition(List<int> &list, int x) -> void;
    static auto sumLists(List<int> &a, List<int> &b) -> List<int>;
    static auto palindrome(List<char> &list) -> bool;
    static auto intersection(List<int> &a, List<int> &b) -> std::shared_ptr<Node<int>>;
    static auto loopDetection(List<int> &list) -> std::shared_ptr<Node<int>>;
};

class III : public Chapter {
  public:
    III(std::string name = "CTCI::III::Stacks and Queues");
    static auto sortStack(Stack<int> &stack) -> void;

    template <typename T> class SetOfStacks {
        std::vector<Stack<T>> stacks;
        size_t threshold = 10;
        size_t totalSize = 0;

      public:
        SetOfStacks() = default;
        SetOfStacks(size_t threshold) : threshold(threshold) {}
        SetOfStacks(std::initializer_list<T> list, size_t threshold = 10) : threshold(threshold) { push(list); }

        void push(T val) {
            Stack<T> *stack = numberOfStacks() == 0 ? &stacks.emplace_back() : &stacks.back();
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
        Stack<T> frontStack;
        Stack<T> rearStack;

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

    class AnimalShelter {
      public:
        class Animal {
          public:
            virtual ~Animal() = default;
        };

        class Dog : public Animal {
          public:
            Dog() = default;
        };
        class Cat : public Animal {
          public:
            Cat() = default;
        };

        void enqueue(std::unique_ptr<Animal> &&ptr);
        auto dequeueAny() -> std::unique_ptr<Animal>;
        auto dequeueDog() -> std::unique_ptr<Animal>;
        auto dequeueCat() -> std::unique_ptr<Animal>;

        bool empty();

      private:
        CTCI::Deque<std::unique_ptr<Animal>> animals;
        template <typename T> auto dequeueAnimalOfType() -> std::unique_ptr<AnimalShelter::Animal> {
            if (empty())
                return nullptr;

            auto head = animals.head;
            while (head != nullptr) {
                if (dynamic_cast<T *>(head->val.get())) {
                    animals.pop(head);
                    auto ptr = std::unique_ptr<T>(static_cast<T *>(head->val.release()));
                    return ptr;
                }
                head = head->next;
            }

            return nullptr;
        };
    };
};

template <typename T> struct GNode {
    std::vector<std::shared_ptr<GNode>> neighbors;
    T val = T{};

    GNode(T val) : val(std::move(val)) {};
    void addNeighbor(std::shared_ptr<GNode> neighbor) { neighbors.push_back(std::move(neighbor)); }
};

template <typename T>
concept Hashable = requires(T a) {
    { std::hash<T>{}(a) } -> std::same_as<std::size_t>;
} && std::equality_comparable<T>;

template <Hashable T, bool Directed = true> class Graph {
    using ValueType = T;
    using NodeType = GNode<T>;
    std::unordered_map<ValueType, std::shared_ptr<NodeType>> nodes;

  public:
    Graph() = default;
    ~Graph() {
        for (auto &node : nodes) {
            auto entry = node.second;
            entry->neighbors.clear();
        }
        nodes.clear();
    };

    Graph(std::initializer_list<T> init) : Graph(std::vector<T>(init.begin(), init.end())) {}
    Graph(std::initializer_list<std::pair<T, T>> init) : Graph(std::vector<std::pair<T, T>>(init.begin(), init.end())) {};

    template <std::ranges::range R> Graph(const R &&rng) {
        for (const auto &el : rng)
            append(el);
    }

    void append(const T &val) { appendNode(val); }

    void append(const std::pair<T, T> &pair) {
        auto &[a, b] = pair;

        appendNode(a);
        std::shared_ptr<NodeType> nodeA = getNode(std::move(a));

        appendNode(b);
        std::shared_ptr<NodeType> nodeB = getNode(std::move(b));

        appendEdge({nodeA, nodeB});
    }

    void appendNode(T val) {
        if (!nodes.contains(val)) {
            auto node = std::make_shared<NodeType>(val);
            nodes.insert({val, node});
        }
    }

    void appendEdge(const std::pair<std::shared_ptr<NodeType>, std::shared_ptr<NodeType>> &pair) {
        auto &[nodeA, nodeB] = pair;
        nodeA->neighbors.push_back(nodeB);
        if constexpr (!Directed)
            nodeB->neighbors.push_back(nodeA);
    }

    std::shared_ptr<NodeType> getNode(T val) {
        auto ptr = nodes.find(val);
        if (ptr == nodes.end())
            return nullptr;

        return ptr->second;
    }
};

class IV : public Chapter {
  public:
    static bool routeBetweenNodes();
};
} // namespace CTCI
