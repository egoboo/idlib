#include "idlib/math/perspective.hpp"

namespace idlib {
	
matrix<single, 4, 4> perspective(const angle<single, degrees>& fov_y, const single aspect, const single z_near, const single z_far)
{ return perspective(semantic_cast<angle<single, radians>>(fov_y), aspect, z_near, z_far); }

matrix<single, 4, 4> perspective(const angle<single, turns>& fov_y, const single aspect, const single z_near, const single z_far)
{ return perspective(semantic_cast<angle<single, radians>>(fov_y), aspect, z_near, z_far); }

matrix<single, 4, 4> perspective(const angle<single, radians>& fov_y, const single aspect, const single z_near, const single z_far)
{
	IDLIB_DEBUG_ASSERT(aspect != 0.0f);
	IDLIB_DEBUG_ASSERT(z_far > 0.0f && z_near > 0.0f);
	IDLIB_DEBUG_ASSERT((z_near - z_far) != 0.0f);

	single tan = std::tan(fov_y * 0.5f);
	IDLIB_DEBUG_ASSERT(tan != 0.0f);
	single f = 1 / tan;

	return matrix<single, 4, 4>(f / aspect, 0.0f,   0.0f,                                0.0f,
			                    0.0f,       f,      0.0f,                                0.0f,
			                    0.0f,       0.0f,   (z_far + z_near) / (z_near - z_far), (2.0f * z_far * z_near) / (z_near - z_far),
			                    0.0f,       0.0f,  -1.0f,                                1.0f);
}
	
} // namespace idlib
