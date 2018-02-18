#pragma once

namespace idlib {

/// @brief Functor computing the identity of a matrix.
/// @tparam T the type of the value to compute the trace of
/// @tparam Enabled for SFINAE
template <typename T, typename Enabled = void>
struct identity_functor;

template <typename T>
auto identity() -> decltype(identity_functor<T>()())
{ return identity_functor<T>()(); }

} // namespace idlib
