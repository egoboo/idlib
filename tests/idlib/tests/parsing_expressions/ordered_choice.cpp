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
