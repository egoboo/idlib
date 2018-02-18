#include "idlib/math/translation.hpp"

namespace idlib {

matrix<single, 4, 4> translation(const vector<single, 3>& t)
{
	return matrix<single, 4, 4>(1, 0, 0, t.x(),
			                    0, 1, 0, t.y(),
			                    0, 0, 1, t.z(),
			                    0, 0, 0, 1);
}

} // namespace idlib