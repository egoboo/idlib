#include "idlib/math/orthographic.hpp"

namespace idlib {
	
matrix<single, 4, 4> orthographic(const single left, const single right, const single bottom, const single top, const single z_near, const single z_far)
{
	single dx = right - left, dy = top - bottom, dz = z_far - z_near;
	IDLIB_DEBUG_ASSERT(dx != 0.0f && dy != 0.0f && dz != 0.0f);
	single tx = -(right + left) / dx, ty = -(top + bottom) / dy, tz = -(z_far + z_near) / (dz);

	return matrix<single, 4, 4>(2.0f / dx, 0.0f,       0.0f,      tx,
								0.0f,      2.0f / dy,  0.0f,      ty,
								0.0f,      0.0f,      -2.0f / dz, tz,
								0.0f,      0.0f,       0.0f,      1.0f);
}
	
} // namespace idlib
