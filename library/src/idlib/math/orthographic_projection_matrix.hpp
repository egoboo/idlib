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
 * @brief Get an orthographic projection (~ camera space -> normalized device coordinate space) matrix.
 * @param left, right the coordinates of the left and right vertical clipping planes
 * @param bottom, top the coordinates of the bottom and top horizontal clipping planes
 * @param z_near, z_far the distance to the nearer and farther depth clipping planes.
 * If a plane's distance is negative, then the plane is to be behind the viewer.
 * @return the matrix
 * @remark
 * The orthographic projection matrix is
 * \f[
 * \left[\begin{matrix}
 * \frac{2}{right-left} & 0                    &   0                          & t_x \\
 * 0                    & \frac{2}{top-bottom} &   0                          & t_y \\
 * 0                    & 0                    &  \frac{-2}{z_{far}-z_{near}} & t_z \\
 * 0                    & 0                    &   0                          & 1 \\
 * \end{matrix}\right]
 * \f]
 * where \f$t_x = -\frac{right+left}{right-left}\f$,
 *       \f$t_y = -\frac{top+bottom}{top-bottom}\f$,
 *       \f$t_z = -\frac{z_{far}+z_{near}}{z_{far}-z_{near}}\f$.
 */
matrix<single, 4, 4> orthographic_projection_matrix(const single left, const single right, const single bottom, const single top, const single z_near, const single z_far);
	
} // namespace idlib
