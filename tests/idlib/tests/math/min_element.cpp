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

TEST(min_element, point_3i)
{
    for (size_t i = 0; i < 1000; ++i)
	{
		auto interval = interval_i(-1000, +1000);
        auto a = id::random<point_3i>(interval);
		// Explicitly find the minimal element.
		auto e = a[0];
		for (size_t i = 1, n = point_3i::dimensionality(); i < n; ++i)
		{
			if (a[i] < e) e = a[i];
		}
        ASSERT_TRUE(e == id::min_element(a));
    }
}

TEST(min_element, vector_3i)
{
    for (size_t i = 0; i < 1000; ++i)
	{
		auto interval = interval_i(-1000, +1000);
        auto a = id::random<vector_3i>(interval);
		// Explicitly find the minimal element.
		auto e = a[0];
		for (size_t i = 1, n = point_3i::dimensionality(); i < n; ++i)
		{
			if (a[i] < e) e = a[i];
		}
		ASSERT_TRUE(e == id::min_element(a));
    }
}

} } } // namespace id::math::test
