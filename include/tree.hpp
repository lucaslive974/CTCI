#pragma once

#include "list.hpp"
#include "memory.hpp"
#include "vector.hpp"

#include <initializer_list>
#include <iterator>

namespace CTCI {

template <typename T> struct TNode {
    using NodeType = TNode<T>;

  public:
    SharedPtr<NodeType> parent = nullptr;
    SharedPtr<NodeType> left = nullptr;
    SharedPtr<NodeType> right = nullptr;
    size_t depth = 1;
    size_t size = 1;
    T val = T{};

    TNode() = default;
    TNode(T val) : val(std::move(val)) {};
    TNode(T val, size_t depth) : val(std::move(val)), depth(depth) {};
    TNode(T val, size_t depth, SharedPtr<NodeType> parent) : val(std::move(val)), depth(depth), parent(std::move(parent)) {}
};

template <typename T> struct Tree {
    using NodeType = TNode<T>;
    using Pointer = SharedPtr<NodeType>;

    Pointer root = nullptr;
    size_t depth = 0;

    Tree() = default;
    Tree(std::initializer_list<T> list) : Tree(Vector<T>{list.begin(), list.end()}) {};
    template <std::ranges::range R> Tree(R &&rng) {
        for (auto &ent : rng)
            append(ent);
    };
    ~Tree() noexcept {
        if (empty())
            return;

        Queue<Pointer> queue;

        queue.push(root);
        while (!queue.empty()) {
            auto node = queue.front();
            queue.pop();

            if (node == nullptr)
                continue;

            queue.push({node->left, node->right});
            node->parent = nullptr;
            node->left = nullptr;
            node->right = nullptr;
        }
    }

    [[nodiscard]] auto empty() const -> bool { return root == nullptr; }

    Pointer append(T value) { return append(root, std::move(value)); }

    Pointer append(Pointer &node, T value, size_t ndepth = 1, Pointer parent = nullptr) { // NOLINT
        if (node == nullptr) {
            node = CTCI::make_shared<NodeType>(value, ndepth, std::move(parent));
            depth = std::max(depth, ndepth);
            return node;
        }

        ++(node->size);
        Pointer ret = nullptr;
        if (value < node->val) {
            ret = append(/**node=*/node->left, std::move(value), node->depth + 1, /**parent=*/node);
        } else {
            ret = append(/**node=*/node->right, std::move(value), node->depth + 1, /**parent=*/node);
        }

        return ret;
    }

    static auto sucessor(const Pointer &node) -> Pointer {
        if (node == nullptr)
            return nullptr;

        if (node->right != nullptr) {
            auto next = node->right;
            while (next->left != nullptr)
                next = next->left;

            return next;
        }

        auto child = node;
        auto parent = node->parent;
        while (parent && parent->right == child) {
            child = parent;
            parent = parent->parent;
        }

        return parent;
    };

    template <bool IsConst> class IteratorImpl {
        Pointer node = nullptr;

      public:
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = Pointer;
        using pointer = std::conditional_t<IsConst, const Pointer, Pointer>;
        using reference = std::conditional_t<IsConst, const Pointer &, Pointer &>;

        IteratorImpl() = default;
        IteratorImpl(std::nullptr_t _) : node(nullptr) {};
        IteratorImpl(pointer ptr) : node(ptr) {};

        IteratorImpl &operator++() {
            node = sucessor(node);
            return *this;
        }

        IteratorImpl operator++(int) {
            auto tmp = *this;
            ++(*this);
            return tmp;
        }

        reference operator*() { return node; }
        pointer operator->() { return &node; }

        reference operator*() const { return node; }
        pointer operator->() const { return &node; }

        friend bool operator==(const IteratorImpl &a, const IteratorImpl &b) { return a.node == b.node; }
        friend bool operator!=(const IteratorImpl &a, const IteratorImpl &b) { return !(a == b); }
    };

    using ForwardIterator = IteratorImpl<false>;
    using ConstForwardIterator = IteratorImpl<true>;

    ConstForwardIterator begin() const {
        if (empty())
            return nullptr;

        auto head = root;
        while (head->left != nullptr)
            head = head->left;

        return ConstForwardIterator{head};
    }

    ConstForwardIterator end() const { return nullptr; }
};

} // namespace CTCI
