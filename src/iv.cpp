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
    auto minTree = [&tree, &nodes](this auto const &self, size_t start, size_t end) {
        if (start >= end)
            return;
        size_t middle = ((end - start) / 2) + start;

        tree.append(nodes[middle]);

        self(start, middle);
        self(middle + 1, end);
    };

    minTree(0, nodes.size());
    return tree;
};