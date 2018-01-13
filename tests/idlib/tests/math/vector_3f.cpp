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

TEST(vector_3i, addition)
{
    for (size_t i = 0; i < 1000; ++i)
	{
		auto interval = interval_i(-1000, +1000);
        auto a = id::random<vector_3i>(interval);
        auto b = id::random<vector_3i>(interval);
        auto c = a + b;
        ASSERT_TRUE((c - b) == a);
        ASSERT_TRUE((c - a) == b);
    }
}

TEST(vector_3i, subtraction)
{
    for (size_t i = 0; i < 1000; ++i)
	{
		auto interval = interval_i(-1000, +1000);
        auto a = id::random<vector_3i>(interval);
        auto b = id::random<vector_3i>(interval);
        auto c = a - b;
        ASSERT_TRUE((c + b) == a);
        ASSERT_TRUE(b == (a - c));
    }
}

TEST(vector_3i, scalar_product)
{
    for (size_t i = 0; i < 1000; ++i)
	{
		auto interval = interval_i(-1000, +1000);
        auto a = id::random<vector_3i>(interval);
        auto b = id::random<vector_3i>(interval);
        int s;
        do {
            s = id::random<int>(interval);
        } while (s == id::zero<int>());
        b = a * s;
        ASSERT_TRUE((b / s) == a);
    }
}

TEST(vector_3i, negation)
{
    for (size_t i = 0; i < 1000; ++i)
	{
		auto interval = interval_i(-1000, +1000);
        auto a = id::random<vector_3i>(interval);
        auto b = -a;
        auto c = -b;
        ASSERT_TRUE(a == c);
    }
}

TEST(vector_3i, equality)
{
    for (size_t i = 0; i < 1000; ++i)
	{
		auto interval = interval_i(-1000, +1000);
        vector_3i a = id::random<vector_3i>(interval);
        vector_3i b = a;
        ASSERT_EQ(a, b);
    }
}

TEST(vector_3i, zero)
{
    auto v = id::zero<vector_3i>();
    ASSERT_TRUE(v[0] == id::zero<int>() && v[1] == id::zero<int>() && v[2] == id::zero<int>());
}

TEST(vector_3i, one)
{
    auto v = id::one<vector_3i>();
    ASSERT_TRUE(v[0] == id::one<int>() && v[1] == id::one<int>() && v[2] == id::one<int>());
}

TEST(vector_3i, length)
{
    auto x = vector_3i::unit(0); 
    ASSERT_TRUE(id::squared_euclidean_norm(x) == id::one<int>());
    ASSERT_TRUE(x[1] == id::zero<int>() && x[2] == id::zero<int>());
    auto y = vector_3i::unit(1);
    ASSERT_TRUE(id::squared_euclidean_norm(y) == id::one<int>());
    ASSERT_TRUE(y[0] == id::zero<int>() && y[2] == id::zero<int>());
    auto z = vector_3i::unit(2);
    ASSERT_TRUE(id::squared_euclidean_norm(z) == id::one<int>());
    ASSERT_TRUE(z[0] == id::zero<int>() && z[1] == id::zero<int>());
}

/// @brief
/// - Assert all components of the one vector are one.
/// - Assert all components of the zero vector are zero.       
TEST(vector_3i, one_zero)
{
	using vector_type = vector_3i;
	using scalar_type = typename vector_3i::scalar_type;
	const auto os = id::one<scalar_type>(),
		       zs = id::zero<scalar_type>();
	const auto ov = id::one<vector_type>(),
		       zv = id::zero<vector_type>();
	ASSERT_TRUE(ov[0] == os && ov[1] == os && ov[2] == os);
	ASSERT_TRUE(zv[0] == zs && zv[1] == zs && zv[2] == zs);
}

} } } // namespace id::math::test
