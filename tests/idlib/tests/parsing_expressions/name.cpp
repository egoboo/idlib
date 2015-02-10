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
#include "idlib/parsing_expressions.hpp"

#include "idlib/tests/parsing_expressions/header.in"

using string = std::basic_string<char>;

/// @brief Regression test.
/// @code{'x.'} was accepted.
TEST(name_expression_regression_testing, test_name_expression_regression)
{
	using namespace id::parsing_expressions;
    auto p = name<char>();
    const std::vector<string> words
    {
        "x.",
    };
    for (const auto& word : words)
    {
        auto s = word.cbegin();
        auto e = word.cend();
        ASSERT_TRUE(parse(p, s, e));
        ASSERT_TRUE(parse(p, s, e).range().end() < word.cend());
    }
}

TEST(name_expression_testing, test_name_expression)
{
    const std::vector<string> words{"org","org_","_1", "_0", "a0"};
    auto p = id::parsing_expressions::name<char>();
    for (const auto& word : words)
    {
        auto s = word.cbegin(),
			 e = word.cend();
		auto m = p(s, e);
        ASSERT_TRUE(m);
		ASSERT_EQ(m.range().begin(), s);
        ASSERT_EQ(m.range().end(), e);
        ASSERT_FALSE(parse(p, m.range().end(), e));
    }
}

#include "idlib/tests/parsing_expressions/footer.in"
