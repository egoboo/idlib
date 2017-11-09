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

namespace id { namespace tests {

/// String which consists only of separator symbols.
TEST(text_parser_testing, separators_only)
{
	size_t expected_value_index = 0;
	static const std::vector<std::string> expected_values = { "a", "b", "c" };
	id::text_parser<char> p;
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
	id::text_parser<char> p;
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

} } // namespace id::tests
