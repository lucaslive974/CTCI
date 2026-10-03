#include <vector>

namespace CTCI {

template <typename T> using Matrix = std::vector<std::vector<T>>;
// Just for better nomenclature when initializing a Matrix(a.k.a std::vector<std::vector<T>)
template <typename T> using Row = std::vector<T>;

} // namespace CTCI
