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

TEST(arithmetic_tuple_test, binary_plus)
{
	id::arithmetic_tuple<int, 3, id::zero_functor<int>> x{1,2,3}, y{2,3,4};
	auto z = x + y;
	auto w = x;
	w += y;
	ASSERT_EQ(z, w);
}

TEST(arithmetic_tuple_test, binary_minus)
{
	id::arithmetic_tuple<int, 3, id::zero_functor<int>> x{1,2,3}, y{2,3,4};
	auto z = x - y;
	auto w = x;
	w -= y;
	ASSERT_EQ(z, w);
}

TEST(arithmetic_tuple_test, binary_star)
{
	int s = 2;
	id::arithmetic_tuple<int, 3, id::zero_functor<int>> x{1,2,3}, y{2,4,6};
	auto z = x * s;
	auto w = x;
	w *= s;
	ASSERT_EQ(z, w);
}

} } } // namespace id::math::tests
