#pragma once

namespace idlib {

/// @brief Functor computing the identity matrix.
/// @tparam T the type of the matrix
/// @tparam Enabled for SFINAE
template <typename T, typename Enabled = void>
struct identity_functor;

template <typename T>
auto identity() -> decltype(identity_functor<T>()())
{ return identity_functor<T>()(); }

} // namespace idlib
