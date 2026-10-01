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