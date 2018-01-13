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

TEST(period_expression_testing, test_period_expression)
{
    auto p = id::parsing_expressions::sym<char>('.');
    std::string w;
    std::string::const_iterator s, e;
    //
    w = std::string(".");
    s = w.cbegin(); e = w.cend();
    ASSERT_TRUE(parse(p, s, e));
    ASSERT_EQ(parse(p, s,e).range().end(), e);
    ASSERT_FALSE(parse(p, parse(p,s,e).range().end(), e));
}

TEST(whitespace_expression_testing, test_whitespace_expression)
{
    auto p = id::parsing_expressions::whitespace<char>();
    std::string w;
    std::string::const_iterator s, e;
    //
    w = std::string(" ");
    s = w.cbegin(); e = w.cend();
    ASSERT_TRUE(parse(p, s, e));
    ASSERT_EQ(parse(p, s,e).range().end(), e);
    ASSERT_FALSE(parse(p, parse(p, s,e).range().end(), e));
    //
    w = std::string("\t");
    s = w.cbegin(); e = w.cend();
    ASSERT_TRUE(parse(p, s, e));
    ASSERT_EQ(parse(p, s,e).range().end(), e);
    ASSERT_FALSE(parse(p, parse(p,s,e).range().end(), e));
}

TEST(newline_expression_testing, test_newline_expression)
{
    auto p = id::parsing_expressions::newline<char>();
    std::string w;
    std::string::const_iterator s, e;
    //
    w = std::string("\n");
    s = w.cbegin(); e = w.cend();
    ASSERT_TRUE(p(s, e));
    ASSERT_EQ(p(s,e).range().end(), e);
    ASSERT_FALSE(p(p(s,e).range().end(), e));
    //
    w = std::string("\r");
    s = w.cbegin(); e = w.cend();
    ASSERT_TRUE(p(s, e));
    ASSERT_EQ(p(s,e).range().end(), e);
    ASSERT_FALSE(p(p(s,e).range().end(), e));
}

TEST(digit_symbol_testing, test_digit_expression)
{
    auto p = id::parsing_expressions::digit<char>();
    for (char symbol = '0'; symbol <= '9'; ++symbol)
    {
        auto w = std::string(1, symbol);
        auto s = w.cbegin(), e = w.cend();
        ASSERT_TRUE(p(s, e));
        ASSERT_EQ(p(s,e).range().end(), e);
        ASSERT_FALSE(p(p(s,e).range().end(), e));
    }
}
    
TEST(alpha_lowercase_expression_testing, test_alpha_lowercase_expression)
{
    auto p = id::parsing_expressions::alpha_lowercase<char>();
    for (char symbol = 'a'; symbol <= 'z'; ++symbol)
    {
        auto w = std::string(1, symbol);
        auto s = w.cbegin(), e = w.cend();
        ASSERT_TRUE(p(s, e));
        ASSERT_EQ(p(s,e).range().end(), e);
        ASSERT_FALSE(p(p(s,e).range().end(), e));
    }
}

TEST(alpha_uppercase_expression_testing, test_alpha_uppercase_expression)
{
    auto p = id::parsing_expressions::alpha_uppercase<char>();
    for (char symbol = 'A'; symbol <= 'Z'; ++symbol)
    {
        auto w = std::string(1, symbol);
        auto s = w.cbegin(), e = w.cend();
        ASSERT_TRUE(p(s, e));
        ASSERT_EQ(p(s,e).range().end(), e);
        ASSERT_FALSE(p(p(s,e).range().end(), e));
    }
}

TEST(single_symbol_testing, test_single_symbol)
{
    //
    for (char symbol = 'a'; symbol <= 'z'; ++symbol)
    {
        auto p = id::parsing_expressions::sym(symbol);
        auto w = std::string(1, symbol);
        auto s = w.cbegin(), e = w.cend();
        ASSERT_TRUE(p(s, e));
        ASSERT_EQ(p(s, e).range().end(), e);
        ASSERT_FALSE(p(p(s, e).range().end(), e));
    }
    //
    for (char symbol = 'A'; symbol <= 'Z'; ++symbol)
    {
        auto p = id::parsing_expressions::sym(symbol);
        auto w = std::string(1, symbol);
        auto s = w.cbegin(), e = w.cend();
        ASSERT_TRUE(p(s, e));
        ASSERT_EQ(p(s, e).range().end(), e);
        ASSERT_FALSE(p(p(s, e).range().end(), e));
    }
}

TEST(alpha_expression_testing, test_alpha_expression)
{
    auto p = id::parsing_expressions::alpha<char>();
    //
    for (char symbol = 'a'; symbol <= 'z'; ++symbol)
    {
        auto w = std::string(1, symbol);
        auto s = w.cbegin(), e = w.cend();
        ASSERT_TRUE(p(s, e));
        ASSERT_EQ(p(s,e).range().end(), e);
        ASSERT_FALSE(p(p(s,e).range().end(), e));
    }
    //
    for (char symbol = 'A'; symbol <= 'Z'; ++symbol)
    {
        auto w = std::string(1, symbol);
        auto s = w.cbegin(), e = w.cend();
        ASSERT_TRUE(p(s, e));
        ASSERT_EQ(p(s,e).range().end(), e);
        ASSERT_FALSE(p(p(s,e).range().end(), e));
    }
}

#include "idlib/tests/parsing_expressions/footer.in"
