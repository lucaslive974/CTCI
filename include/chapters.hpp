#pragma once
#include "chapter.hpp"

namespace CTCI {
class IX : public Chapter {
  public:
    IX(std::string name = "CTCI::IX::Exercises");
    static void isUnique();
};
} // namespace CTCI
