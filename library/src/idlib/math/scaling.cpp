#include "idlib/math/scaling.hpp"

#include "idlib/math/floating_point.hpp"

namespace idlib {

matrix<single, 4, 4> scaling(single s)
{ return scaling(one<vector<single, 3>>() * s); }

matrix<single, 4, 4> scaling(const vector<single, 3>& s)
{
	return matrix<single, 4, 4>(s[0], 0,    0,    0,
								0,    s[0], 0,    0,
								0,    0,    s[0], 0,
								0,    0,    0,    1);
}

} // namespace idlib
