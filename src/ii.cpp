#include "chapters.hpp"
#include <unordered_map>
#include <unordered_set>
#include <format>

using namespace CTCI;

auto II::removeDups(CTCI::List<int> &list) -> void {
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

auto II::kthLast(const List<int> &list, size_t k) -> int {
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

auto II::deleteMiddleNode(std::shared_ptr<Node<int>> &node) -> void {
    if (node == nullptr)
        return;

    const auto &head = node;
    head->val = head->next->val;
    head->next = head->next->next;
}

auto II::partition(List<int> &list, int x) -> void {
    if (list.empty())
        return;

    CTCI::List<int> left;
    CTCI::List<int> right;

    auto head = list.head;
    while (head != nullptr) {
        if (head->val < x) {
            left.push(head->val);
        } else {
            right.push(head->val);
        }
        head = head->next;
    }

    if (left.empty()) {
        list = std::move(right);
        return;
    }

    left.push(std::move(right));
    list = std::move(left);
};

auto II::sumLists(List<int> &a, List<int> &b) -> List<int> { // NOLINT
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

        res.push(digit);
    };

    return res;
}

auto II::palindrome(List<char> &list) -> bool {
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

auto II::intersection(List<int> &a, List<int> &b) -> std::shared_ptr<Node<int>> { // NOLINT
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

auto II::loopDetection(List<int> &list) -> std::shared_ptr<Node<int>> {
    auto slow = list.head;
    auto fast = list.head;

    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;

        if (fast == slow)
            break;
    }

    if (fast == nullptr || fast->next == nullptr)
        return nullptr;

    slow = list.head;
    while (slow != fast) {
        slow = slow->next;
        fast = fast->next;
    }

    return slow;
};
