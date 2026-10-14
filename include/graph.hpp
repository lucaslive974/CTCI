#include "associative_containers.hpp"
#include "memory.hpp"

#include <concepts.hpp>
#include <concepts>

namespace CTCI {

template <typename T> struct GNode {
    Vector<SharedPtr<GNode>> neighbors;
    T val = T{};

    GNode(T val) : val(std::move(val)) {};
    void addNeighbor(SharedPtr<GNode> neighbor) { neighbors.push_back(std::move(neighbor)); }
};

template <concepts::Hashable T, bool Directed = true> class Graph {
    using ValueType = T;
    using NodeType = GNode<T>;
    HashMap<ValueType, SharedPtr<NodeType>> nodes;

  public:
    Graph() = default;
    ~Graph() {
        for (auto &node : nodes) {
            auto entry = node.second;
            entry->neighbors.clear();
        }
        nodes.clear();
    };

    Graph(std::initializer_list<T> init) : Graph(Vector<T>(init.begin(), init.end())) {}
    Graph(std::initializer_list<std::pair<T, T>> init) : Graph(Vector<std::pair<T, T>>(init.begin(), init.end())) {};

    template <std::ranges::range R> Graph(R &&rng) {
        for (const auto &el : rng)
            append(el);
    }

    void append(const T &val) { appendNode(val); }

    void append(const std::pair<T, T> &pair) { appendEdge(pair); }

    void appendNode(T val) {
        if (!nodes.contains(val)) {
            auto node = CTCI::make_shared<NodeType>(val);
            nodes.insert({val, node});
        }
    }

    template <typename _ = void>
    void appendEdge(const std::pair<T, T> &pair)
        requires(!std::same_as<T, SharedPtr<NodeType>>)
    {
        auto &[a, b] = pair;

        appendNode(a);
        SharedPtr<NodeType> nodeA = getNode(std::move(a));

        appendNode(b);
        SharedPtr<NodeType> nodeB = getNode(std::move(b));

        appendEdge({nodeA, nodeB});
    }

    void appendEdge(const std::pair<SharedPtr<NodeType>, SharedPtr<NodeType>> &pair) {
        auto &[nodeA, nodeB] = pair;
        nodeA->neighbors.push_back(nodeB);
        if constexpr (!Directed)
            nodeB->neighbors.push_back(nodeA);
    }

    SharedPtr<NodeType> getNode(T val) const {
        auto ptr = nodes.find(val);
        if (ptr == nodes.end())
            return nullptr;

        return ptr->second;
    }
};

} // namespace CTCI
