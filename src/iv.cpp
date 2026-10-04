#include "chapters.hpp"
#include "unordered_set"

using namespace CTCI;

auto IV::routeBetweenNodes(const Node<int> &orig, const Node<int> &dest) -> bool { // NOLINT
    if (orig == nullptr || dest == nullptr)
        return false;

    if (orig == dest)
        return true;

    Queue<Node<int>> queue;
    queue.append(orig);

    std::unordered_set<Node<int>> visited{orig};

    while (!queue.empty()) {
        auto node = queue.front();
        queue.pop();

        for (auto &neighbor : node->neighbors) {
            if (visited.contains(neighbor))
                continue;

            if (neighbor == dest)
                return true;

            queue.append(neighbor);
            visited.insert(neighbor);
        }
    }

    return false;
};

auto IV::minimalTree(const std::vector<int> &nodes) -> Tree<int> {
    Tree<int> tree;
    auto minTree = [&tree, &nodes](this auto const &self, Tree<int>::Pointer &subTree, size_t start, size_t end) {
        if (start >= end)
            return;
        size_t middle = ((end - start) / 2) + start;

        auto nSubTree = tree.append(subTree, nodes[middle]);

        self(nSubTree, start, middle);
        self(nSubTree, middle + 1, end);
    };

    minTree(tree.root, 0, nodes.size());
    return tree;
};

auto IV::listOfDepths(const Tree<int> &tree) -> std::vector<ListNode<int>> {
    if (tree.empty())
        return {};

    std::vector<ListNode<int>> res{ListNode<int>{tree.root}};
    auto makeListOfDepths = [&tree, &res](this auto &self, const ListNode<int> &parents) -> void {
        ListNode<int> children;
        for (const auto &parent : parents) {
            if (parent->left != nullptr)
                children.append(parent->left);

            if (parent->right != nullptr)
                children.append(parent->right);
        }

        if (children.empty())
            return;

        res.push_back(children);
        self(children);
    };

    makeListOfDepths(res.front());
    return res;
};

static auto treeHeight(const Tree<int>::Pointer &node) -> int {
    if (node == nullptr)
        return 0;

    auto left = treeHeight(node->left);
    auto right = treeHeight(node->right);

    return std::max(left, right) + 1;
}

static auto checkBalanced(const Tree<int>::Pointer &subTree) -> bool {
    auto fb = treeHeight(subTree->right) - treeHeight(subTree->left);
    return abs(fb) <= 1;
}

auto IV::checkBalanced(const Tree<int> &tree) -> bool {
    if (tree.empty())
        return true;

    return ::checkBalanced(tree.root);
};
