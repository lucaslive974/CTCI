#include <concepts.hpp>

#include <memory>
#include <vector>

namespace CTCI {

template <typename T> struct GNode {
    std::vector<std::shared_ptr<GNode>> neighbors;
    T val = T{};

    GNode(T val) : val(std::move(val)) {};
    void addNeighbor(std::shared_ptr<GNode> neighbor) { neighbors.push_back(std::move(neighbor)); }
};

template <Hashable T, bool Directed = true> class Graph {
    using ValueType = T;
    using NodeType = GNode<T>;
    std::unordered_map<ValueType, std::shared_ptr<NodeType>> nodes;

  public:
    Graph() = default;
    ~Graph() {
        for (auto &node : nodes) {
            auto entry = node.second;
            entry->neighbors.clear();
        }
        nodes.clear();
    };

    Graph(std::initializer_list<T> init) : Graph(std::vector<T>(init.begin(), init.end())) {}
    Graph(std::initializer_list<std::pair<T, T>> init) : Graph(std::vector<std::pair<T, T>>(init.begin(), init.end())) {};

    template <std::ranges::range R> Graph(R &&rng) {
        for (const auto &el : rng)
            append(el);
    }

    void append(const T &val) { appendNode(val); }

    void append(const std::pair<T, T> &pair) { appendEdge(pair); }

    void appendNode(T val) {
        if (!nodes.contains(val)) {
            auto node = std::make_shared<NodeType>(val);
            nodes.insert({val, node});
        }
    }

    void appendEdge(const std::pair<T, T> &pair) {
        auto &[a, b] = pair;

        appendNode(a);
        std::shared_ptr<NodeType> nodeA = getNode(std::move(a));

        appendNode(b);
        std::shared_ptr<NodeType> nodeB = getNode(std::move(b));

        appendEdge({nodeA, nodeB});
    }

    void appendEdge(const std::pair<std::shared_ptr<NodeType>, std::shared_ptr<NodeType>> &pair) {
        auto &[nodeA, nodeB] = pair;
        nodeA->neighbors.push_back(nodeB);
        if constexpr (!Directed)
            nodeB->neighbors.push_back(nodeA);
    }

    std::shared_ptr<NodeType> getNode(T val) const {
        auto ptr = nodes.find(val);
        if (ptr == nodes.end())
            return nullptr;

        return ptr->second;
    }
};

} // namespace CTCI
