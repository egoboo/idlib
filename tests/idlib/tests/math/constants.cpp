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

TEST(constants, pi_s)
{
    auto x = id::pi<single>();
	ASSERT_TRUE(!std::isnan(x));
	ASSERT_TRUE(!std::isinf(x));
	ASSERT_FLOAT_EQ(x, 3.1415926535897932384626433832795f);
}

TEST(constants, two_pi_s)
{
    auto x = id::two_pi<single>();
	ASSERT_TRUE(!std::isnan(x));
	ASSERT_TRUE(!std::isinf(x));
	ASSERT_FLOAT_EQ(x, 2.0f * 3.1415926535897932384626433832795f);
}

TEST(constants, inv_pi_s)
{
    auto x = id::inv_pi<single>();
	ASSERT_TRUE(!std::isnan(x));
	ASSERT_TRUE(!std::isinf(x));
	ASSERT_FLOAT_EQ(x, 1.0f / 3.1415926535897932384626433832795f); // GoogleTest tolerance is four ULP, ours was two ULP.
}

TEST(constants, inv_two_pi_s)
{
    auto x = id::inv_two_pi<single>();
	ASSERT_TRUE(!std::isnan(x));
	ASSERT_TRUE(!std::isinf(x));
	ASSERT_FLOAT_EQ(x, 1.0f / (2.0f * 3.1415926535897932384626433832795f));
}

TEST(constants, pi_over_two_s)
{
    auto x = id::pi_over<single, 2>();
	ASSERT_TRUE(!std::isnan(x));
	ASSERT_TRUE(!std::isinf(x));
	ASSERT_FLOAT_EQ(x, 3.1415926535897932384626433832795f / 2.0f);
}

TEST(constants, pi_over_four_s)
{
    auto x = id::pi_over<single, 4>();
	ASSERT_TRUE(!std::isnan(x));
	ASSERT_TRUE(!std::isinf(x));
	ASSERT_FLOAT_EQ(x, 3.1415926535897932384626433832795f / 4.0f);
}

TEST(constants, pi_d)
{
    auto x = id::pi<double>();
	ASSERT_TRUE(!std::isnan(x));
	ASSERT_TRUE(!std::isinf(x));
	ASSERT_FLOAT_EQ(x, 3.1415926535897932384626433832795);
}

TEST(constants, two_pi_d)
{
    auto x = id::two_pi<double>();
	ASSERT_TRUE(!std::isnan(x));
	ASSERT_TRUE(!std::isinf(x));
	ASSERT_FLOAT_EQ(x, 2.0 * 3.1415926535897932384626433832795);
}

TEST(constants, inv_pi_d)
{
    auto x = id::inv_pi<double>();
	ASSERT_TRUE(!std::isnan(x));
	ASSERT_TRUE(!std::isinf(x));
	ASSERT_FLOAT_EQ(x, 1.0 / 3.1415926535897932384626433832795);
}

TEST(constants, inv_two_pi_d)
{
    auto x = id::inv_two_pi<double>();
	ASSERT_TRUE(!std::isnan(x));
	ASSERT_TRUE(!std::isinf(x));
	ASSERT_FLOAT_EQ(x, 1.0 / (2.0 * 3.1415926535897932384626433832795));
}

TEST(constants, pi_over_two_d)
{
    auto x = id::pi_over<double, 2>();
	ASSERT_TRUE(!std::isnan(x));
	ASSERT_TRUE(!std::isinf(x));
	ASSERT_FLOAT_EQ(x, 3.1415926535897932384626433832795 / 2.0);
}

TEST(constants, pi_over_four_d)
{
    auto x = id::pi_over<double, 4>();
    ASSERT_TRUE(!std::isnan(x));
	ASSERT_TRUE(!std::isinf(x));
	ASSERT_FLOAT_EQ(x, 3.1415926535897932384626433832795 / 4.0);
}

TEST(constants, sqrt_two_s)
{
    auto x = id::sqrt_two<single>();
	ASSERT_TRUE(!std::isnan(x));
	ASSERT_TRUE(!std::isinf(x));
	ASSERT_FLOAT_EQ(x, std::sqrt(2.0f));
}

TEST(constants, inv_sqrt_two_s)
{
    auto x = id::inv_sqrt_two<single>();
    auto y = 1.0f / std::sqrt(2.0f);
	ASSERT_TRUE(!std::isnan(x) && !std::isnan(y));
	ASSERT_TRUE(!std::isinf(x) && !std::isinf(y));
	ASSERT_TRUE(0.0 < x && 0.0 < y);
	ASSERT_FLOAT_EQ(x, y);
}

TEST(constants, sqrt_two_d)
{
    auto x = id::sqrt_two<double>();
    auto y = std::sqrt(2.0);
	ASSERT_TRUE(!std::isnan(x) && !std::isnan(y));
	ASSERT_TRUE(!std::isinf(x) && !std::isinf(y));
	ASSERT_TRUE(0.0 < x && 0.0 < y);
	ASSERT_FLOAT_EQ(x, y);
}

TEST(constants, inv_sqrt_two_d)
{
    double x = id::inv_sqrt_two<double>();
    double y = 1.0 / std::sqrt(2.0);
	ASSERT_TRUE(!std::isnan(x) && !std::isnan(y));
	ASSERT_TRUE(!std::isinf(x) && !std::isinf(y));
	ASSERT_TRUE(0.0 < x && 0.0 < y);
	ASSERT_FLOAT_EQ(x, y);
}
  
} } } // namespace id::math::test
