#pragma once

#include "chapter.hpp"
#include "data_structures.hpp"
#include <memory>
#include <vector>

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

class IV : public Chapter {
    template <typename T> using Node = std::shared_ptr<GNode<T>>;

  public:
    static bool routeBetweenNodes(const Node<int> &orig, const Node<int> &dest);
    static auto minimalTree(const std::vector<int> &nodes) -> Tree<int>;

    template <typename T> using ListNode = List<std::shared_ptr<TNode<T>>>;
    static auto listOfDepths(const Tree<int> &tree) -> std::vector<ListNode<int>>;
    static auto checkBalanced(const Tree<int> &tree) -> bool;
    static auto validateBST(const Tree<int> &tree) -> bool;

    static auto sucessor(const Tree<int>::Pointer &node) -> Tree<int>::Pointer;
};
} // namespace CTCI
