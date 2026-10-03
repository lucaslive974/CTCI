#pragma once

#include "list.hpp"

#include <memory>
#include <vector>

namespace CTCI {

template <typename T> struct TNode {
    using NodeType = TNode<T>;

  public:
    std::shared_ptr<NodeType> left = nullptr;
    std::shared_ptr<NodeType> right = nullptr;
    size_t depth = 1;
    T val = T{};

    TNode() = default;
    TNode(T val) : val(std::move(val)) {};
    TNode(T val, size_t depth) : val(std::move(val)), depth(depth) {};
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

        queue.append(root);
        while (!queue.empty()) {
            auto node = queue.front();
            queue.pop();

            if (node == nullptr)
                continue;

            queue.append({node->left, node->right});
            node->left = nullptr;
            node->right = nullptr;
        }
    }

    [[nodiscard]] auto empty() const -> bool { return root == nullptr; }

    Pointer append(T value) { return append(root, std::move(value)); }

    Pointer append(Pointer &node, T value, size_t ndepth = 1) {
        if (node == nullptr) {
            node = std::make_shared<NodeType>(value, ndepth);
            depth = std::max(depth, ndepth);
            return node;
        }

        Pointer ret = nullptr;
        if (value < node->val)
            ret = append(node->left, std::move(value), node->depth + 1);
        else
            ret = append(node->right, std::move(value), node->depth + 1);

        return ret;
    }
};

} // namespace CTCI
