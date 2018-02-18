#pragma once

#pragma push_macro("IDLIB_PRIVATE")

#if !defined(IDLIB_PRIVATE)
#define IDLIB_PRIVATE (1)
#endif

#include "idlib/math/vector.hpp"
#include "idlib/math/matrix.hpp"

#pragma pop_macro("IDLIB_PRIVATE")

namespace idlib {

/**
 * @brief Get a translation matrix.
 * @param t the translation vector
 * @remark The \f$4 \times 4\f$ translation matrix for the translation vector $\left(t_x,t_y,t_z\right)$ is defined as
 * \f[
 * \left[\begin{matrix}
 * 1 & 0 & 0 & t_x \\
 * 0 & 1 & 0 & t_y \\
 * 0 & 0 & 1 & t_z \\
 * 0 & 0 & 0 & 1   \\
 * \end{matrix}\right]
 * \f]
 */
matrix<single, 4, 4> translation(const vector<single, 3>& t);

} // namespace idlib
