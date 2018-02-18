#pragma once

namespace idlib {

/// @brief Functor computing the inverse of a matrix.
/// @tparam T the matrix type
/// @tparam Enabled for SFINAE
template <typename T, typename Enabled = void>
struct inverse_functor;

template <typename T>
auto inverse(const T& v) -> decltype(inverse_functor<T>()(v))
{ return inverse_functor<T>()(v); }

} // namespace idlib
