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
 * @brief Get a viewing transformation (~ world space -> camera space) matrix.
 * @param eye the position of the eye point
 * @param center the position of the reference point
 * @param up the direction of the up vector
 * @return the matrix
 * @pre eye != center
 *      up  != 0
 */
matrix<single, 4, 4> look_at_matrix(const vector<single, 3>& eye, const vector<single, 3>& center, const vector<single, 3>& up);
	
} // namespace idlib
