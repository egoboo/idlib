#pragma once

#pragma push_macro("IDLIB_PRIVATE")
#undef IDLIB_PRIVATE
#define IDLIB_PRIVATE (1)

#include "idlib/math/vector.hpp"
#include "idlib/math/matrix.hpp"

#undef IDLIB_PRIVATE
#pragma pop_macro("IDLIB_PRIVATE")

namespace idlib {

/**
 * @brief Get a uniform scaling matrix.
 * @param s the scaling scalar
 * @return the matrix
 * @remark
 * The expression
 * @code
 * scaling(s)
 * @endcode
 * is equivalent to the expression
 * @code
 * scaling(one<vector<single, 3>>() * s)
 * @endcode call
 * @see idlib::scaling<const vector<single, 3>&)
 */
matrix<single, 4, 4> scaling_matrix(single s);

/**
 * @brief Get a non-uniform scaling scaling matrix.
 * @param s the scaling vector
 * @return the matrix
 * @remark
 * The scaling matrix is defined as
 * \f[
 * \left[\begin{matrix}
 * s_x &  0   & 0   & 0 \\
 * 0   &  s_y & 0   & 0 \\
 * 0   &  0   & s_z & 0 \\
 * 0   &  0   & 0   & 1 \\
 * \end{matrix}\right]
 * \f]
 */
matrix<single, 4, 4> scaling_matrix(const vector<single, 3>& s);

} // namespace idlib
