#pragma once

#include "chapter.hpp"
#include "data_structures.hpp"
#include <functional>
#include <random>
#include <stdexcept>

namespace CTCI {

class I : public Chapter {
  public:
    I(std::string name = "CTCI::I::Arrays and Strings");
    static auto isUnique(const std::string &s) -> bool;
    static auto checkPermutation(const std::string &s1, const std::string &s2) -> bool;
    static auto urlify(std::string s, size_t length) -> std::string;
    static auto palindromePerm(const std::string &s) -> bool;
    static auto oneAway(std::string &s1, std::string &s2) -> bool;
    static auto stringCompression(const std::string &s1) -> std::string;
    static auto rotateMatrix(Vector<Vector<int>> &matrix) -> void;
    static auto zeroMatrix(Vector<Vector<int>> &matrix) -> void;
    static auto stringRotation(std::string s1, const std::string &s2) -> bool;
};

class II : public Chapter {
  public:
    II(std::string name = "CTCI::II::Linked Lists");
    static auto removeDups(List<int> &list) -> void;
    static auto kthLast(const List<int> &list, size_t k) -> int;
    static auto deleteMiddleNode(SharedPtr<Node<int>> &node) -> void;
    static auto partition(List<int> &list, int x) -> void;
    static auto sumLists(List<int> &a, List<int> &b) -> List<int>;
    static auto palindrome(List<char> &list) -> bool;
    static auto intersection(List<int> &a, List<int> &b) -> SharedPtr<Node<int>>;
    static auto loopDetection(List<int> &list) -> SharedPtr<Node<int>>;
};

class III : public Chapter {
  public:
    III(std::string name = "CTCI::III::Stacks and Queues");
    static auto sortStack(Stack<int> &stack) -> void;

    template <typename T> class SetOfStacks {
        Vector<Stack<T>> stacks;
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

        struct AnimalStorage {
            UniquePtr<Animal> animal;
            size_t seq;
        };

        void enqueue(UniquePtr<Animal> &&ptr);
        auto dequeueAny() -> UniquePtr<Animal>;
        auto dequeueDog() -> UniquePtr<Dog>;
        auto dequeueCat() -> UniquePtr<Cat>;

        bool empty();

      private:
        CTCI::Queue<AnimalStorage> dogs;
        CTCI::Queue<AnimalStorage> cats;

        size_t seq = 0;
    };
};

class IV : public Chapter {
    template <typename T> using Node = SharedPtr<GNode<T>>;

  public:
    IV(std::string name = "Trees and Graphs");
    static bool routeBetweenNodes(const Node<int> &orig, const Node<int> &dest);
    static auto minimalTree(const Vector<int> &nodes) -> Tree<int>;

    template <typename T> using ListNode = List<SharedPtr<TNode<T>>>;
    static auto listOfDepths(const Tree<int> &tree) -> Vector<ListNode<int>>;
    static auto checkBalanced(const Tree<int> &tree) -> bool;
    static auto validateBST(const Tree<int> &tree) -> bool;
    static auto sucessor(const Tree<int>::Pointer &node) -> Tree<int>::Pointer;

    class CircularReferenceError : public std::runtime_error {
      public:
        CircularReferenceError(const char *msg) : std::runtime_error(msg) {};
    };

    using Project = char;
    struct BuildInfo {
        List<Project> projects;
        List<std::pair<Project, Project>> dependencies;
    };
    static auto buildOrder(const BuildInfo &info) -> List<Project>;

    using TreeNode = Tree<int>::Pointer;
    static auto findCommonAncestor(TreeNode &a, TreeNode &b) -> TreeNode;
    static auto BSTSequences(const Tree<int>::Pointer &node) -> Vector<Vector<int>>;
    static auto BSTSequences(const Tree<int> &tree) -> Vector<Vector<int>>;
    static auto checkSubtree(const Tree<int> &t1, const Tree<int> &t2) -> bool;

    template <std::uniform_random_bit_generator Context>
    static auto getRandomNode(const Tree<int> &tree, Context &ctx) -> Tree<int>::Pointer {
        if (tree.empty())
            return nullptr;

        auto uniformDistribution = std::uniform_int_distribution<size_t>{1UZ, tree.size()};
        return tree.find(uniformDistribution(ctx));
    };

    static auto pathsWithSum(const Tree<int> &tree, int target) -> size_t;
};

class V : public Chapter {
    template <typename T> using Node = SharedPtr<GNode<T>>;

  public:
    V(std::string name = "Bit Manipulation");

    struct InsertionData {
        uint M;
        uint N;
        size_t i;
        size_t j;
    };
    static auto insertion(InsertionData &info) -> uint;
    static auto flipBitToWin(uint data) -> size_t;
    static auto nextNumber(uint data) -> std::pair<uint, uint>;
    static auto conversion(uint a, uint b) -> size_t;
    static auto pairwiseSwap(const uint &input) -> uint;

    template <size_t ScreenSize> struct Screen {
        Bitset<ScreenSize / 8> buffer;
        uint width;
        Screen(uint width) : width(width) {};
    };
    struct ScreenCoord {
        size_t x;
        size_t y;
    };

    static auto calculateIdx(ScreenCoord &coord, uint width) -> uint { return (coord.x * width) + coord.y; };
    template <size_t Size> static auto drawLine(Screen<Size> &screen, ScreenCoord a1, ScreenCoord a2) {
        auto start = calculateIdx(a1, screen.width);
        auto end = calculateIdx(a2, screen.width);

        for (; start <= end; ++start)
            screen.buffer.set(start);
    }
};

class VI : public Chapter {
  public:
    VI(std::string name = "Math and Logic Puzzles");

    static auto theHeavyPill(double measureWeight) -> uint;
    template <std::uniform_random_bit_generator URBG> static auto theApocalypse(URBG &urbg) -> std::pair<double, double> {
        std::uniform_int_distribution<uint> dist{0, 1};

        double boys = 0;
        double girls = 0;

        size_t familyIdx = 0;
        while (familyIdx < 10'000) {
            bool isGirl = dist(urbg) == 1;

            if (isGirl) {
                ++girls;
                ++familyIdx;
            } else {
                ++boys;
            }
        }

        const double total = boys + girls;
        return {boys / total, girls / total};
    };

    struct Soda {
        bool isPoisoned;
    };
    static auto poison(const Array<Soda, 1'000> &bottles) -> size_t;
};

class VIII : Chapter {
  public:
    VIII(std::string name = "Recursion and Dynamic Programming");
    static auto tripleSteps(size_t steps) -> size_t;

    struct Spot {
        size_t x;
        size_t y;

        friend bool operator==(const Spot &a, const Spot &b) { return a.x == b.x && a.y == b.y; }
    };
    struct GridInfo {
        size_t rowSize;
        size_t colSize;
    };

    static auto robotInAGrid(const GridInfo &info, const Vector<Spot> &offLimits = {}) -> Vector<Spot>;
    static auto magicIndex(const Vector<int> &arr) -> int;
};

} // namespace CTCI
