#pragma once
#include "chapter.hpp"

namespace CTCI {
class IX : public Chapter {
  public:
    IX(std::string name = "CTCI::IX::Exercises");
    static auto isUnique(const std::string &s) -> bool;
    static auto checkPermutation(const std::string &s1, const std::string &s2) -> bool;
    static auto urlify(std::string s, size_t length) -> std::string;
    static auto palindromePerm(const std::string &s) -> bool;
    static auto oneAway(std::string &s1, std::string &s2) -> bool;
};
} // namespace CTCI
