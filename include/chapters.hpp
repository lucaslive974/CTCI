#pragma once
#include "chapter.hpp"
#include <vector>

namespace CTCI {

template <typename T> using Matrix = std::vector<std::vector<T>>;
// Just for better nomenclature when initializing a Matrix(a.k.a std::vector<std::vector<T>)
template <typename T> using Row = std::vector<int>;

class IX : public Chapter {
  public:
    IX(std::string name = "CTCI::IX::Exercises");
    static auto isUnique(const std::string &s) -> bool;
    static auto checkPermutation(const std::string &s1, const std::string &s2) -> bool;
    static auto urlify(std::string s, size_t length) -> std::string;
    static auto palindromePerm(const std::string &s) -> bool;
    static auto oneAway(std::string &s1, std::string &s2) -> bool;
    static auto stringCompression(const std::string &s1) -> std::string;
    static auto rotateMatrix(std::vector<std::vector<int>> &matrix) -> void;
    static auto zeroMatrix(std::vector<std::vector<int>> &matrix) -> void;
};
} // namespace CTCI
