#pragma once

#pragma push_macro("IDLIB_PRIVATE")
#undef IDLIB_PRIVATE
#define IDLIB_PRIVATE (1)

#include "idlib/math/angle-degrees-radians-turns.hpp"
#include "idlib/math/vector.hpp"
#include "idlib/math/matrix.hpp"

#undef IDLIB_PRIVATE
#pragma pop_macro("IDLIB_PRIVATE")

namespace idlib {

/**@{*/

/**
 * @brief Get a perspective projection (~ view space -> normalized device coordinate space) matrix.
 * @param fov_y the field of view angle in the y direction. The angle can be specified as degrees, radians, or turns.
 * @param aspect the aspect ratio in the x direction
 * @param z_near the distance of the viewer to the near clipping plane
 * @param z_far the distance of the viewer to the far clipping plane
 * @return the matrix
 * @pre @a z_near as well as @a z_far must be positive
 * @pre <tt>z_near - z_far</tt> must not be @a 0
 * @pre @a aspect must not be @a 0.
 * @remark The aspect ratio specifies the field of view in the x direction and is the ratio of the x (width) / y (height).
 * @remark The perspective projection matrix is
 * \f[
 * \left[\begin{matrix}
 * \frac{f}{aspect} & 0 &  0                                                 & 0 \\
 * 0                & f &  0                                                 & 0 \\
 * 0                & 0 &  \frac{(z_{far} + z_{near})}{(z_{near} - z_{far})} & \frac{(2 * z_{far} * z_{near})}{(z_{near} - z_{far})} \\
 * 0                & 0 & -1                                                 & 1 \\
 * \end{matrix}\right]
 * \f]
 * where \f$f = cot(0.5 fov_y)\f$.
 */
matrix<single, 4, 4> perspective_projection_matrix(const angle<single, degrees>& fov_y, const single aspect, const single z_near, const single z_far);

matrix<single, 4, 4> perspective_projection_matrix(const angle<single, turns>& fov_y, const single aspect, const single z_near, const single z_far);

matrix<single, 4, 4> perspective_projection_matrix(const angle<single, radians>& fov_y, const single aspect, const single z_near, const single z_far);

/**@}*/
	
} // namespace idlib
