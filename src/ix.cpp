#include "chapters.hpp"
#include <algorithm>
#include <bitset>
#include <cstring>
#include <iostream>
#include <unordered_map>
#include <unordered_set>

using namespace CTCI;

void isUnique() {
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

void checkPermutation() {
    auto checkPermutationDefault = [](const std::string &s1, const std::string &s2) {
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
    };

    constexpr const char *placeholder = "{} and {} are permutations: {}\n";
    std::string s1{"lucas"};
    std::string s2{"scalu"};
    std::string s3{"sunfire-spear"};
    std::string s4{"pears-firesuns"};

    std::cout << std::format(placeholder, s1, s2, checkPermutationDefault(s1, s2));
    std::cout << std::format(placeholder, s3, s4, checkPermutationDefault(s3, s4));
}

void urlify() {
    auto urlifyDefault = [](std::string s, size_t length) {
        size_t write = s.size() - 1;
        for (int i = length - 1; i >= 0; --i) {
            if (!std::isspace(s[i])) {
                s[write--] = s[i];
                continue;
            }

            std::memcpy(&s[write - 2], "%20\0", 3);
            write -= 3;
        }

        return s;
    };
    constexpr const char *placeholder = "\"{}\" urlified: \"{}\"\n";

    std::string s1 = "Mr John Smith    ";
    std::string s2 = "  www.youtube    ";
    std::cout << std::format(placeholder, s1, urlifyDefault(s1, 13));
    std::cout << std::format(placeholder, s2, urlifyDefault(s2, 13));
}

IX::IX(std::string name) : Chapter(std::move(name)) {
    tasks = std::vector<Task>{{"isUnique", isUnique}, {"Check permutation", checkPermutation}, {"URLify", urlify}};
}
