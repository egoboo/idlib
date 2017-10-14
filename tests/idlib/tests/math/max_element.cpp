// Copyright Michael Heilmann 2016, 2017.
//
// This file is part of Idlib.
//
// Idlib is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Idlib is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Idlib. If not, see <http://www.gnu.org/licenses/>.

#include "gtest/gtest.h"
#include "idlib/idlib.hpp"

namespace id { namespace math { namespace test {
	
using interval_i = id::interval<int>;
using vector_3i = id::vector<int, 3>;
using point_3i = id::point<vector_3i>;

TEST(max_element, point_3i)
{
    for (size_t i = 0; i < 1000; ++i)
	{
		id::random r;
		auto interval = interval_i(-1000, +1000);
        auto a = point_3i(r.next(interval), r.next(interval), r.next(interval));
		// Explicitly find the maximal element.
		auto e = a[0];
		for (size_t i = 1, n = point_3i::dimensionality(); i < n; ++i)
		{
			if (a[i] > e) e = a[i];
		}
        ASSERT_TRUE(e == id::max_element(a));
    }
}

TEST(max_element, vector_3i)
{
    for (size_t i = 0; i < 1000; ++i)
	{
		id::random r;
		auto interval = interval_i(-1000, +1000);
        auto a = vector_3i(r.next(interval), r.next(interval), r.next(interval));
		// Explicitly find the maximal element.
		auto e = a[0];
		for (size_t i = 1, n = point_3i::dimensionality(); i < n; ++i)
		{
			if (a[i] > e) e = a[i];
		}
        ASSERT_TRUE(e == id::max_element(a));
    }
}

} } } // namespace id::math::test
