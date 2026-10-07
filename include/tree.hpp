#pragma once

#include "list.hpp"

#include <initializer_list>
#include <memory>
#include <vector>

namespace CTCI {

template <typename T> struct TNode {
    using NodeType = TNode<T>;

  public:
    std::shared_ptr<NodeType> parent = nullptr;
    std::shared_ptr<NodeType> left = nullptr;
    std::shared_ptr<NodeType> right = nullptr;
    size_t depth = 1;
    T val = T{};

    TNode() = default;
    TNode(T val) : val(std::move(val)) {};
    TNode(T val, size_t depth) : val(std::move(val)), depth(depth) {};
    TNode(T val, size_t depth, std::shared_ptr<NodeType> parent)
        : val(std::move(val)), depth(depth), parent(std::move(parent)) {}
};

template <typename T> struct Tree {
    using NodeType = TNode<T>;
    using Pointer = std::shared_ptr<NodeType>;

    Pointer root = nullptr;
    size_t depth = 0;

    Tree() = default;
    Tree(std::initializer_list<T> list) : Tree(std::vector<T>{list.begin(), list.end()}) {};
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
            node = std::make_shared<NodeType>(value, ndepth, std::move(parent));
            depth = std::max(depth, ndepth);
            return node;
        }

        Pointer ret = nullptr;
        if (value < node->val)
            ret = append(/**node=*/node->left, std::move(value), node->depth + 1, /**parent=*/node);
        else
            ret = append(/**node=*/node->right, std::move(value), node->depth + 1, /**parent=*/node);

        return ret;
    }
};

} // namespace CTCI
