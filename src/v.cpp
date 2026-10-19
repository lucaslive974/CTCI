#include "chapters.hpp"

using namespace CTCI;

auto V::insertion(InsertionData &info) -> int {
    int output = info.N;

    int maskLeft = static_cast<int>(~0U << (info.j + 1));
    int maskRight = static_cast<int>(~0U >> (32 - info.i));
    int mask = maskLeft | maskRight;

    output &= mask;
    output |= (info.M << info.i);

    return output;
}
