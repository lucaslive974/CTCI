#include "associative_containers.hpp"
#include "chapters.hpp"

using namespace CTCI;

auto IV::routeBetweenNodes(const Node<int> &orig, const Node<int> &dest) -> bool { // NOLINT
    if (orig == nullptr || dest == nullptr)
        return false;

    if (orig == dest)
        return true;

    Queue<Node<int>> queue;
    queue.push(orig);

    Set<Node<int>> visited{orig};

    while (!queue.empty()) {
        auto node = queue.front();
        queue.pop();

        for (auto &neighbor : node->neighbors) {
            if (visited.contains(neighbor))
                continue;

            if (neighbor == dest)
                return true;

            queue.push(neighbor);
            visited.insert(neighbor);
        }
    }

    return false;
};

auto IV::minimalTree(const Vector<int> &nodes) -> Tree<int> {
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

auto IV::listOfDepths(const Tree<int> &tree) -> Vector<ListNode<int>> {
    if (tree.empty())
        return {};

    Vector<ListNode<int>> res{ListNode<int>{tree.root}};
    auto makeListOfDepths = [&tree, &res](this auto &self, const ListNode<int> &parents) -> void {
        ListNode<int> children;
        for (const auto &parent : parents) {
            if (parent->left != nullptr)
                children.push(parent->left);

            if (parent->right != nullptr)
                children.push(parent->right);
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
    return std::ranges::all_of(tree, [](const auto &node) { return ::checkBalanced(node); });
};

static bool checkBST(const Tree<int>::Pointer &node) {
    if (node == nullptr)
        return true;

    auto &val = node->val;
    auto &left = node->left;
    auto &right = node->right;

    bool leftIsEqualGreater = left && left->val >= val;
    bool rightIsLesser = right && right->val < val;

    if (leftIsEqualGreater || rightIsLesser)
        return false;

    return checkBST(left) && checkBST(right);
}

auto IV::validateBST(const Tree<int> &tree) -> bool { return checkBST(tree.root); };

auto IV::sucessor(const Tree<int>::Pointer &node) -> Tree<int>::Pointer { return Tree<int>::sucessor(node); };

auto IV::buildOrder(const BuildInfo &info) -> List<Project> {
    Graph<Project> graph{info.projects};

    HashMap<Project, size_t> inDegree;
    for (const auto &dependencie : info.dependencies) {
        graph.appendEdge(dependencie);
        inDegree[dependencie.second]++;
    }

    Queue<Project> qready;
    for (const auto &project : info.projects) {
        if (inDegree[project] == 0)
            qready.push(project);
    }

    List<Project> buildList;
    while (!qready.empty()) {
        auto project = qready.front();
        qready.pop();

        buildList.push(project);

        for (const auto &dependent : graph.getNode(project)->neighbors) {
            if (--inDegree[dependent->val] == 0)
                qready.push(dependent->val);
        }
    }

    if (buildList.size != info.projects.size)
        throw CircularReferenceError{"[Circular reference found on build graph]"};

    return buildList;
}

auto IV::findCommonAncestor(TreeNode &a, TreeNode &b) -> TreeNode { // NOLINT
    Set<TreeNode> path;

    auto head = a;
    while (head != nullptr) {
        path.insert(head);
        head = head->parent;
    }

    head = b;
    TreeNode ans = nullptr;

    while (head != nullptr) {
        if (path.contains(head))
            return head;

        head = head->parent;
    }

    return ans;
}

struct WeaveVectorInfo {
    const Vector<int> &vec;
    size_t start = 0;
};

auto weaveVectors(const WeaveVectorInfo left, const WeaveVectorInfo right, Vector<int> &prefix, Vector<Vector<int>> &results)
    -> void {
    if (left.start == left.vec.size() || right.start == right.vec.size()) {
        Vector<int> result = prefix;
        for (auto idx : std::views::iota(left.start, left.vec.size()))
            result.push_back(left.vec[idx]);
        for (auto idx : std::views::iota(right.start, right.vec.size()))
            result.push_back(right.vec[idx]);
        results.push_back(std::move(result));
        return;
    }

    prefix.push_back(left.vec[left.start]);
    weaveVectors(/*left=*/{.vec = left.vec, .start = left.start + 1},
                 /*right=*/{.vec = right.vec, .start = right.start}, prefix, results);
    prefix.pop_back();

    prefix.push_back(right.vec[right.start]);
    weaveVectors(/*left=*/{.vec = left.vec, .start = left.start},
                 /*right=*/{.vec = right.vec, .start = right.start + 1}, prefix, results);
    prefix.pop_back();
};

auto IV::BSTSequences(const Tree<int>::Pointer &node) -> Vector<Vector<int>> {
    if (node == nullptr)
        return {{}};

    Vector<Vector<int>> result;
    Vector<int> prefix{node->val};

    auto leftSeq = BSTSequences(node->left);
    auto rightSeq = BSTSequences(node->right);

    for (const auto &left : leftSeq) {
        for (const auto &right : rightSeq) {
            Vector<Vector<int>> weaved;
            weaveVectors(/*left=*/{.vec = left}, /*right=*/{.vec = right}, prefix, weaved);
            result.insert(result.end(), weaved);
        }
    }

    return result;
};

auto IV::BSTSequences(const Tree<int> &tree) -> Vector<Vector<int>> { return BSTSequences(tree.root); }
