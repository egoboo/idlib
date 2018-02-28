#include "idlib/math/scaling_matrix.hpp"

#include "idlib/math/floating_point.hpp"

namespace idlib {

matrix<single, 4, 4> scaling_matrix(single s)
{ return scaling_matrix(one<vector<single, 3>>() * s); }

matrix<single, 4, 4> scaling_matrix(const vector<single, 3>& s)
{
	return matrix<single, 4, 4>(s[0], 0,    0,    0,
								0,    s[1], 0,    0,
								0,    0,    s[2], 0,
								0,    0,    0,    1);
}

} // namespace idlib
