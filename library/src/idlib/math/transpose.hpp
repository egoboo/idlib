#pragma once

namespace idlib {
	
/// @brief Functor computing the transpose of a matrix.
/// @tparam T the matrix type
/// @tparam Enabled for SFINAE
/// @remark The transpose \f$M^T\f$ of a matrix \f$M\f$ is defined as
/// \f[
/// M^T_{i, j} = M_{j, i}
/// \f]
/// @remark The transpose is also called the conjugate or the adjugate.
template <typename T, typename Enabled = void>
struct transpose_functor;

template <typename T>
auto transpose(const T& v) -> decltype(transpose_functor<T>()(v))
{ return transpose_functor<T>()(v); }
	
} // namespace idlib