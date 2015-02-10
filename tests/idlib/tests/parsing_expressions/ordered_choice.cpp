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

TEST(choice_expression_testing, test_choice_expression_1)
{
	using namespace id::parsing_expressions;
    static const string w0 = "x", w1 = "y";
    static const auto p = ordered_choice
        (
            sym<char>('x'),
            sym<char>('y')
        );
    /*
    const vector<string> words_to_accept
    {
        "x",
        "y"
    };
    const std::vector<string> words_to_reject
    {
        "u",
        "v"
    };
    */
    //for (const auto& word : words_to_accept)
    {
        auto s = w0.cbegin();
        auto e = w0.cend();
        ASSERT_TRUE(parse(p, s, e));
        ASSERT_EQ(parse(p, s, e).range().end(), w0.cend());
    }
    //for (const auto& word : words_to_reject)
    {
        auto s = w1.cbegin();
        auto e = w1.cend();
        ASSERT_TRUE(parse(p, s, e));
        ASSERT_EQ(parse(p, s, e).range().end(), w1.cend());
    }
}

TEST(choice_expression_testing, test_choice_expression_2)
{
	using namespace id::parsing_expressions;
    auto p = ordered_choice
        (
            sequence
            (
                sym<char>('x'),
                sym<char>('x')
            ),
            sequence
            (
                sym<char>('y'),
                sym<char>('y')
            )
        );
    const std::vector<string> words_to_accept
    {
        "xx",
        "yy"
    };
    const std::vector<string> words_to_reject
    {
        "xy",
        "yx"
    };
    for (const auto& word : words_to_accept)
    {
        auto s = word.cbegin();
        auto e = word.cend();
        ASSERT_TRUE(parse(p, s, e));
        ASSERT_EQ(parse(p,s,e).range().end(), word.cend());
    }
    for (const auto& word : words_to_reject)
    {
        auto s = word.cbegin();
        auto e = word.cend();
        ASSERT_FALSE(parse(p, s, e));
        ASSERT_EQ(parse(p, s, e).range().end(), word.cbegin());
    }
}

#include "idlib/tests/parsing_expressions/footer.in"
