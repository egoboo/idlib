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

namespace id { namespace math { namespace tests {
	
using scalar = single;
using vector_3s = id::vector<single, 3>;

/// @brief Assert the "Manhattan" norm is zero for a zero vector \f$\vec{1}\f$.
/// Assert for \f$(1,0,0)\f$, \f$(0,1,0)\f$, and \f$(0,0,1)\f$ it is one.
TEST(norm, manhattan)
{
	ASSERT_EQ(id::manhattan_norm(vector_3s(1, 0, 0)), id::one<single>());
	ASSERT_EQ(id::manhattan_norm(vector_3s(0, 1, 0)), id::one<single>());
	ASSERT_EQ(id::manhattan_norm(vector_3s(0, 0, 1)), id::one<single>());
	ASSERT_EQ(id::manhattan_norm(id::zero<vector_3s>()), id::zero<single>());
}

/// @brief Assert the "Euclidean" norm is zero for a zero vector.
/// Assert for \f$(1,0,0)\f$, \f$(0,1,0)\f$, and \f$(0,0,1)\f$ it is one.
TEST(norm, euclidean)
{
	ASSERT_EQ(id::euclidean_norm(vector_3s(1, 0, 0)), id::one<single>());
	ASSERT_EQ(id::euclidean_norm(vector_3s(0, 1, 0)), id::one<single>());
	ASSERT_EQ(id::euclidean_norm(vector_3s(0, 0, 1)), id::one<single>());
	ASSERT_EQ(id::euclidean_norm(id::zero<vector_3s>()), id::zero<single>());
}

/// @brief Assert the squared "Euclidean" norm is zero for a zero vector.
/// Assert for \f$(1,0,0)\f$, \f$(0,1,0)\f$, and \f$(0,0,1)\f$ it is one.
TEST(norm, squared_euclidean)
{
	ASSERT_EQ(id::squared_euclidean_norm(vector_3s(1, 0, 0)), id::one<single>());
	ASSERT_EQ(id::squared_euclidean_norm(vector_3s(0, 1, 0)), id::one<single>());
	ASSERT_EQ(id::squared_euclidean_norm(vector_3s(0, 0, 1)), id::one<single>());
	ASSERT_EQ(id::squared_euclidean_norm(id::zero<vector_3s>()), id::zero<single>());
}

/// @brief Assert the maximum norm is zero for a zero vector.
/// Assert for \f$(1,0,0)\f$, \f$(0,1,0)\f$, and \f$(0,0,1)\f$ it is one.
TEST(norm, maximum)
{
	ASSERT_EQ(id::euclidean_norm(vector_3s(1, 0, 0)), id::one<single>());
	ASSERT_EQ(id::euclidean_norm(vector_3s(0, 1, 0)), id::one<single>());
	ASSERT_EQ(id::euclidean_norm(vector_3s(0, 0, 1)), id::one<single>());
	ASSERT_EQ(id::maximum_norm(id::zero<vector_3s>()), id::zero<single>());
}

} } } // namespace id::math::tests
