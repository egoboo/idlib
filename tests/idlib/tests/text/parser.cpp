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

namespace idlib { namespace tests {

/// String which consists only of separator symbols.
TEST(text_parser_testing, separators_only)
{
	size_t expected_value_index = 0;
	static const std::vector<std::string> expected_values = { "a", "b", "c" };
	idlib::text_parser<char> p;
	p("abc",
	[](char x)
	{
		return x == 'a' || x == 'b' || x == 'c';
	},
	[&expected_value_index](auto string_start, auto string_end, auto substring_start, auto substring_end)
	{
		ASSERT_LT(expected_value_index, expected_values.size());
		ASSERT_EQ(std::string(substring_start, substring_end), expected_values[expected_value_index]);
		expected_value_index++;
	});
	ASSERT_EQ(expected_values.size(), expected_value_index);
}

/// String which is empty.
TEST(text_parser_testing, empty_string)
{
	size_t expected_value_index = 0;
	static const std::vector<std::string> expected_values = {};
	idlib::text_parser<char> p;
	p("",
		[](char x)
	{
		return x == 'a' || x == 'b' || x == 'c';
	},
	[&expected_value_index](auto string_start, auto string_end, auto substring_start, auto substring_end)
	{
		ASSERT_LT(expected_value_index, expected_values.size());
		ASSERT_EQ(std::string(substring_start, substring_end), expected_values[expected_value_index]);
		expected_value_index++;
	});
	ASSERT_EQ(expected_values.size(), expected_value_index);
}

} } // namespace idlib::tests
