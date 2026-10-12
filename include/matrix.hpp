#include "vector.hpp"

namespace CTCI {

template <typename T> using Matrix = Vector<Vector<T>>;
// Just for better nomenclature when initializing a Matrix(a.k.a Vector<Vector<T>)
template <typename T> using Row = Vector<T>;

} // namespace CTCI
