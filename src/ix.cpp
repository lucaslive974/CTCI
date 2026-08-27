#include "chapters.hpp"
#include "utils.hpp"
#include <algorithm>
#include <bitset>
#include <iostream>
#include <unordered_set>

using namespace CTCI;

IX::IX(std::string name) : Chapter(std::move(name)) { tasks = std::vector<Task>{{"isUnique", isUnique}}; };

void IX::isUnique() {
    // Default
    auto isUniqueDefault = [](const std::string &s) -> bool {
        std::unordered_set<char> characters;
        for (const auto &c : s) {
            if (characters.contains(c))
                return false;

            characters.insert(c);
        }

        return true;
    };

    auto isUniqueBitVector = [](const std::string &s) -> bool {
        std::bitset<256> characters(false);
        for (const auto &c : s) {
            if (characters.test(c))
                return false;

            characters[c] = true;
        }

        return true;
    };

    auto isUniqueO1Space = [](std::string s) {
        // Quicksort inplace
        // The quicksort algorithm will be a whole chapter to it.
        std::ranges::sort(s);
        for (int i = 1; i < s.size(); ++i) {
            if (s[i] == s[i - 1])
                return false;
        }
        return true;
    };

    constexpr const char *placeholder = "{} has all unique characters: {}\n";
    std::string unique{"abcdefg"};
    std::string nonUnique{"abccdef"};
    std::string largeS{"abcdefghijklmnopqrstuvywz"};
    std::string largeS2{"abcdefghijklmnopqrstuvywza"};

    std::cout << std::format(placeholder, unique, isUniqueDefault(unique));
    std::cout << std::format(placeholder, nonUnique, isUniqueBitVector(nonUnique));
    std::cout << std::format(placeholder, largeS, isUniqueO1Space(largeS));
    std::cout << std::format(placeholder, largeS2, isUniqueO1Space(largeS2));
};
