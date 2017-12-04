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

TEST(point_3i, addition)
{
    for (size_t i = 0; i < 1000; ++i)
	{
		auto interval = interval_i(-1000, +1000);
        // b = a + t0
        // t1 = a - b = a - (a + t0) = -t0
        point_3i a = id::random<point_3i>(interval);
        vector_3i t0 = id::random<vector_3i>(interval);
        point_3i b = a + t0;
        vector_3i t1 = a - b;
        ASSERT_TRUE(-t0 == t1);
    }
}

TEST(point_3i, subtraction)
{
    for (size_t i = 0; i < 1000; ++i)
	{
		auto interval = interval_i(-1000, +1000);
        // b = a - t0
        // t1 = b - a = (a - t0) - a = -t0
        point_3i a = id::random<point_3i>(interval);
        vector_3i t0 = id::random<vector_3i>(interval);
        point_3i b = a - t0;
        vector_3i t1 = b - a;
        ASSERT_TRUE(-t0 == t1);
    }
}

TEST(point_3i, zero)
{
    auto v = id::zero<point_3i>();
    ASSERT_TRUE(v[0] == id::zero<int>() && v[1] == id::zero<int>() && v[2] == id::zero<int>());
}

} } } // namespace id::math::test
