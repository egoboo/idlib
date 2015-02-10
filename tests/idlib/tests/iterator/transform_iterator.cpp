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
#include "idlib/iterator.hpp"

#include "idlib/iterator/header.in"
#include "idlib/iterator/footer.in"

TEST(transform_iterator_test, test_transform_iterator)
{
	struct unary_functor
	{
		int operator()(int x) const
		{
			return x * 2;
		}
	};
	std::vector<char> sources;
	for (auto i = 1; i <= 10; ++i)
	{
		sources.push_back(i);
	}
	using transform_iterator_type = id::transform_iterator<unary_functor, std::vector<char>::const_iterator>;
	for (auto it = transform_iterator_type(sources.cbegin(), unary_functor{});
		 it != transform_iterator_type(sources.cend(), unary_functor{}); ++it)
	{ 
		ASSERT_EQ(*it, *it.get_it() * 2);
	}
}
