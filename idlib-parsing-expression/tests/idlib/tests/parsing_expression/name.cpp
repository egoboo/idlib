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
#include "idlib/parsing_expression.hpp"

#include "idlib/tests/parsing_expression/header.in"

using string = std::basic_string<char>;

/// @brief Regression test.
/// @code{'x.'} was accepted.
TEST(name_expression_regression_testing, test_name_expression_regression)
{
    using namespace idlib::parsing_expression;
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
    auto p = idlib::parsing_expression::name<char>();
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

#include "idlib/tests/parsing_expression/footer.in"
