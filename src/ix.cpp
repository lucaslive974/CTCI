#include "chapters.hpp"
#include <cstring>
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