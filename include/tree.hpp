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
    T val = T{};

    TNode() = default;
    TNode(T val) : val(std::move(val)) {};
};

template <typename T> struct Tree {
    using NodeType = TNode<T>;

    std::shared_ptr<NodeType> root = nullptr;
    size_t rank = 0;

    Tree() = default;
    Tree(std::initializer_list<T> list) : Tree(std::vector<T>{list.begin(), list.end()}) {};
    template <std::ranges::range R> Tree(R &&rng) {
        for (auto &ent : rng)
            append(ent);
    };
    ~Tree() noexcept {
        if (empty())
            return;

        Queue<std::shared_ptr<NodeType>> queue;

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

    void append(T value) { append(root, std::move(value)); }

  private:
    void append(std::shared_ptr<NodeType> &node, T value, size_t nrank = 1) {
        if (node == nullptr) {
            node = std::make_shared<NodeType>(value);
            rank = std::max(rank, nrank);
            return;
        }

        if (value < node->val)
            append(node->left, std::move(value), nrank + 1);
        else
            append(node->right, std::move(value), nrank + 1);
    }
};

} // namespace CTCI
