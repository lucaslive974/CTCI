#include "utils.hpp"
#include <iostream>
#include <string>

namespace CTCI::utils {
void printTitle(std::string msg) { std::cout << std::format("[{}]\n", msg); }
void breakLine() { std::cout << "\n\n"; }
} // namespace CTCI::utils
  