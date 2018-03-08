#pragma once

namespace idlib {

/// @brief Functor computing the trace of a matrix.
/// @tparam T the matrix type
/// @tparam Enabled for SFINAE
template <typename T, typename Enabled = void>
struct trace_functor;

template <typename T>
auto trace(const T& v) -> decltype(trace_functor<T>()(v))
{ return trace_functor<T>()(v); }

} // namespace idlib
