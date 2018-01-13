///////////////////////////////////////////////////////////////////////////////////////////////////
//
// Idlib: A C++ utility library
// Copyright (C) 2017-2018 Michael Heilmann
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
///////////////////////////////////////////////////////////////////////////////////////////////////

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
