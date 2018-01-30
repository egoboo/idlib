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
	using transform_iterator_type = idlib::transform_iterator<unary_functor, std::vector<char>::const_iterator>;
	for (auto it = transform_iterator_type(sources.cbegin(), unary_functor{});
		 it != transform_iterator_type(sources.cend(), unary_functor{}); ++it)
	{ 
		ASSERT_EQ(*it, *it.get_it() * 2);
	}
}
