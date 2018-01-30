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
	
using scalar = single;
using vector_3s = idlib::vector<single, 3>;

/// @brief Assert the "Manhattan" norm is zero for a zero vector \f$\vec{1}\f$.
/// Assert for \f$(1,0,0)\f$, \f$(0,1,0)\f$, and \f$(0,0,1)\f$ it is one.
TEST(norm, manhattan)
{
	ASSERT_EQ(idlib::manhattan_norm(vector_3s(1, 0, 0)), idlib::one<single>());
	ASSERT_EQ(idlib::manhattan_norm(vector_3s(0, 1, 0)), idlib::one<single>());
	ASSERT_EQ(idlib::manhattan_norm(vector_3s(0, 0, 1)), idlib::one<single>());
	ASSERT_EQ(idlib::manhattan_norm(idlib::zero<vector_3s>()), idlib::zero<single>());
}

/// @brief Assert the "Euclidean" norm is zero for a zero vector.
/// Assert for \f$(1,0,0)\f$, \f$(0,1,0)\f$, and \f$(0,0,1)\f$ it is one.
TEST(norm, euclidean)
{
	ASSERT_EQ(idlib::euclidean_norm(vector_3s(1, 0, 0)), idlib::one<single>());
	ASSERT_EQ(idlib::euclidean_norm(vector_3s(0, 1, 0)), idlib::one<single>());
	ASSERT_EQ(idlib::euclidean_norm(vector_3s(0, 0, 1)), idlib::one<single>());
	ASSERT_EQ(idlib::euclidean_norm(idlib::zero<vector_3s>()), idlib::zero<single>());
}

/// @brief Assert the squared "Euclidean" norm is zero for a zero vector.
/// Assert for \f$(1,0,0)\f$, \f$(0,1,0)\f$, and \f$(0,0,1)\f$ it is one.
TEST(norm, squared_euclidean)
{
	ASSERT_EQ(idlib::squared_euclidean_norm(vector_3s(1, 0, 0)), idlib::one<single>());
	ASSERT_EQ(idlib::squared_euclidean_norm(vector_3s(0, 1, 0)), idlib::one<single>());
	ASSERT_EQ(idlib::squared_euclidean_norm(vector_3s(0, 0, 1)), idlib::one<single>());
	ASSERT_EQ(idlib::squared_euclidean_norm(idlib::zero<vector_3s>()), idlib::zero<single>());
}

/// @brief Assert the maximum norm is zero for a zero vector.
/// Assert for \f$(1,0,0)\f$, \f$(0,1,0)\f$, and \f$(0,0,1)\f$ it is one.
TEST(norm, maximum)
{
	ASSERT_EQ(idlib::euclidean_norm(vector_3s(1, 0, 0)), idlib::one<single>());
	ASSERT_EQ(idlib::euclidean_norm(vector_3s(0, 1, 0)), idlib::one<single>());
	ASSERT_EQ(idlib::euclidean_norm(vector_3s(0, 0, 1)), idlib::one<single>());
	ASSERT_EQ(idlib::maximum_norm(idlib::zero<vector_3s>()), idlib::zero<single>());
}

} } } // namespace idlib::math::tests
