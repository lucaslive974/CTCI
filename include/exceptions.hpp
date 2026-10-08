#pragma once

#include <stdexcept>

namespace CTCI {
class OutOfRange : public std::out_of_range {
  public:
    OutOfRange(const char *msg) : std::out_of_range(msg) {}
};
} // namespace CTCI
