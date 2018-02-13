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

namespace idlib { namespace math { namespace tests {

TEST(emtpy_arithmetic_array_2d_test, binary_plus)
{
	idlib::arithmetic_array_2d<int, 0, 0, idlib::zero_functor<int>> x{}, y{};
	ASSERT_EQ(x + y, x);
	ASSERT_EQ(x + y, y);
	ASSERT_EQ(y + x, x);
	ASSERT_EQ(y + x, y);
}

TEST(empty_arithmetic_array_2d_test, binary_minus)
{
	idlib::arithmetic_array_2d<int, 0, 0, idlib::zero_functor<int>> x{}, y{};
	ASSERT_EQ(x - y, x);
	ASSERT_EQ(x - y, y);
	ASSERT_EQ(y - x, x);
	ASSERT_EQ(y - x, y);
}

TEST(empty_arithmetic_array_2d_test, binary_star)
{
	idlib::arithmetic_array_2d<int, 0, 0, idlib::zero_functor<int>> x{}, y{};
	auto s = 3;
	ASSERT_EQ(x * s, x);
	ASSERT_EQ(y * s, y);
}

TEST(empty_arithmetic_array_2d_test, binary_slash)
{
	idlib::arithmetic_array_2d<int, 0, 0, idlib::zero_functor<int>> x{}, y{};
	auto s = 3;
	ASSERT_EQ(x / s, x);
	ASSERT_EQ(y / s, y);
}

TEST(empty_arithmetic_array_2d_test, unary_plus)
{
	idlib::arithmetic_array_2d<int, 0, 0, idlib::zero_functor<int>> x{}, y{};
	ASSERT_EQ(+x, x);
	ASSERT_EQ(+y, y);
	ASSERT_EQ(+x, y);
	ASSERT_EQ(+y, x);
}

TEST(empty_arithmetic_array_2d_test, unary_minus)
{
	idlib::arithmetic_array_2d<int, 0, 0, idlib::zero_functor<int>> x{}, y{};
	ASSERT_EQ(-x, x);
	ASSERT_EQ(-y, y);
	ASSERT_EQ(-x, y);
	ASSERT_EQ(-y, x);
}

} } } // namespace idlib::math::tests
