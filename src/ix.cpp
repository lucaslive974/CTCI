#include "chapters.hpp"
#include <algorithm>
#include <cstring>
#include <format>
#include <memory>
#include <stdexcept>
#include <unistd.h>
#include <unordered_map>
#include <unordered_set>

using namespace CTCI;

IX::IX(std::string name) : Chapter(std::move(name)) {};

auto IX::isUnique(const std::string &s) -> bool {
    // Default
    std::unordered_set<char> characters;
    for (const auto &c : s) {
        if (characters.contains(c))
            return false;

        characters.insert(c);
    }

    return true;
};

auto IX::checkPermutation(const std::string &s1, const std::string &s2) -> bool {
    std::unordered_map<char, unsigned int> freq1;
    for (const auto &c : s1)
        ++freq1[c];

    std::unordered_map<char, unsigned int> freq2;
    for (const auto &c : s2)
        ++freq2[c];

    if (freq1.size() != freq2.size())
        return false;

    for (auto [s1Char, s1Freq] : freq1) {
        const auto &s2Freq = freq2[s1Char];
        if (s1Freq != s2Freq)
            return false;
    }

    return true;
}

auto IX::urlify(std::string s, size_t length) -> std::string {
    size_t write = s.size() - 1;
    for (int i = static_cast<int>(length) - 1; i >= 0; --i) {
        if (std::isspace(s[i]) == 0) {
            s[write--] = s[i];
            continue;
        }

        std::memcpy(&s[write - 2], "%20\0", 3);
        write -= 3;
    }

    return s;
}

auto IX::palindromePerm(const std::string &s) -> bool {
    std::unordered_map<char, unsigned int> freq;
    size_t n = 0;
    for (const auto &c : s) {
        if (std::isspace(c) != 0)
            continue;
        freq[static_cast<char>(std::tolower(c))]++;
        ++n;
    }

    bool isEvenSize = n % 2 == 0;
    bool oddFreqFound = false;

    for (const auto [key, value] : freq) {
        bool isOddFreq = value % 2 != 0;

        if (isEvenSize && isOddFreq)
            return false;

        if (!isEvenSize && oddFreqFound && isOddFreq)
            return false;

        if (isOddFreq)
            oddFreqFound = true;
    }

    return true;
}

auto IX::oneAway(std::string &s1, std::string &s2) -> bool {
    auto sizeDiff = static_cast<long long>(s1.size() - s2.size());
    auto [gs, ss] = sizeDiff < 0 ? std::make_pair(s2, s1) : std::make_pair(s1, s2);

    bool foundDiff = false;
    for (int i = 0, j = 0; i < gs.size() && i < ss.size(); ++i, ++j) {
        if (gs[i] == ss[j])
            continue;

        if (foundDiff)
            return false;

        foundDiff = true;
        if (std::abs(sizeDiff) > 0)
            --j;
    }

    return std::abs(sizeDiff) <= 1;
}

auto IX::stringCompression(const std::string &s1) -> std::string {
    if (s1.empty())
        return s1;

    std::string res;

    char aCh = s1.front();
    int count = 1;

    int idx = 1;
    while (idx < s1.size()) {
        if (aCh == s1[idx]) {
            count++;
        } else {
            res += aCh + std::to_string(count);
            aCh = s1[idx];
            count = 1;
        }
        ++idx;
    }

    res += aCh + std::to_string(count);

    return res.size() < s1.size() ? res : s1;
};

namespace internal {
auto rotateMatrixNonSquare(std::vector<std::vector<int>> &matrix, size_t n, size_t m) -> void {
    std::vector<std::vector<int>> newMatrix(m, std::vector(n, 0));
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < m; ++j) {
            newMatrix[j][n - 1 - i] = matrix[i][j];
        }
    }

    matrix = std::move(newMatrix);
}

auto rotateMatrixSquare(std::vector<std::vector<int>> &matrix, size_t size) -> void {
    for (size_t i = 0; i < size; ++i)
        for (size_t j = i + 1; j < size; ++j)
            std::swap(matrix[i][j], matrix[j][i]);

    for (auto &row : matrix)
        std::ranges::reverse(row);
}
} // namespace internal

auto IX::rotateMatrix(std::vector<std::vector<int>> &matrix) -> void {
    if (matrix.empty() || matrix.front().empty())
        return;

    size_t n = matrix.size();
    size_t m = matrix.front().size();

    if (n == m)
        internal::rotateMatrixSquare(matrix, n);
    else
        internal::rotateMatrixNonSquare(matrix, n, m);
}

auto IX::zeroMatrix(std::vector<std::vector<int>> &matrix) -> void {
    if (matrix.empty() || matrix.front().empty())
        return;

    size_t m = matrix.size();
    size_t n = matrix.front().size();

    auto fillZero = [&matrix, &m, &n](size_t row, size_t column) {
        for (size_t i = 0; i < m; ++i)
            matrix[i][column] = 0;
        for (size_t i = 0; i < n; ++i)
            matrix[row][i] = 0;
    };

    std::vector<std::pair<int, int>> zerosPos;
    for (size_t i = 0; i < m; ++i) {
        for (size_t j = 0; j < n; ++j) {
            if (matrix[i][j] == 0)
                zerosPos.emplace_back(i, j);
        }
    }

    for (auto &[row, col] : zerosPos)
        fillZero(row, col);
}

auto IX::stringRotation(std::string s1, const std::string &s2) -> bool { return (s1 += s1).contains(s2); }

auto IX::removeDups(CTCI::List<int> &list) -> void {
    if (list.empty())
        return;

    std::unordered_map<int, int> freq;

    auto head = list.head;
    while (head != nullptr) {
        freq[head->val]++;
        head = head->next;
    }

    head = list.head;
    while (head->next != nullptr) {
        if (freq[head->next->val] > 1) {
            freq[head->next->val]--;
            head->next = head->next->next;
            continue;
        }
        head = head->next;
    }
}

auto IX::kthLast(const List<int> &list, size_t k) -> int {
    if (list.empty())
        throw std::invalid_argument("Empty list");

    auto head = list.head;

    size_t listSize = 0;
    while (head != nullptr) {
        head = head->next;
        ++listSize;
    }

    if (k > listSize - 1)
        throw std::invalid_argument(std::format("The kth({}) is greater than the list", k));

    size_t elIdx = listSize - k;
    head = list.head;

    for (size_t i = 0; i < elIdx - 1; ++i)
        head = head->next;

    return head->val;
}

auto IX::deleteMiddleNode(std::shared_ptr<Node<int>> &node) -> void {
    if (node == nullptr)
        return;

    auto head = node;
    while (head->next != nullptr) {
        auto next = head->next;
        head->val = head->next->val;
        head->next = head->next->next;

        head = next;
    }
}

auto IX::partition(List<int> &list, int x) -> void {
    if (list.empty())
        return;

    CTCI::List<int> left;
    CTCI::List<int> right;

    auto head = list.head;
    while (head != nullptr) {
        (head->val < x ? left : right).appendToTail(head);
        head = head->next;
    }

    if (left.empty()) {
        list.head = right.head;
        return;
    }

    if (!right.empty())
        right.tail->next = nullptr;

    left.tail->next = right.head;
    list.head = left.head;
};

auto IX::sumLists(List<int> &a, List<int> &b) -> List<int> { // NOLINT
    List<int> res;

    auto headA = a.head;
    auto headB = b.head;
    int carry = 0;

    while (headA != nullptr || headB != nullptr || carry != 0) {
        int digit = 0;

        if (headA != nullptr) {
            digit += headA->val;
            headA = headA->next;
        }

        if (headB != nullptr) {
            digit += headB->val;
            headB = headB->next;
        }

        digit += carry;
        carry = digit / 10;
        digit %= 10;

        res.appendToTail(digit);
    };

    return res;
}

auto IX::palindrome(List<char> &list) -> bool {
    auto a = list;
    if (list.empty())
        return true;

    std::shared_ptr<Node<char>> middle;
    {
        auto fast = list.head;
        auto slow = list.head;

        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }

        middle = slow;
    }

    CTCI::revertLinkedList(middle);
    auto head = list.head;
    auto tail = list.tail;

    while (head != middle) {
        if (head->val != tail->val)
            return false;

        head = head->next;
        tail = tail->next;
    }

    CTCI::revertLinkedList(list.tail);
    return true;
}

auto IX::intersection(List<int> &a, List<int> &b) -> std::shared_ptr<Node<int>> { // NOLINT
    std::unordered_set<void *> existents;

    auto head = a.head;
    while (head != nullptr) {
        existents.insert(reinterpret_cast<void *>(head.get()));
        head = head->next;
    }

    head = b.head;
    while (head != nullptr) {
        if (existents.contains(reinterpret_cast<void *>(head.get())))
            return head;

        head = head->next;
    }

    return nullptr;
}
