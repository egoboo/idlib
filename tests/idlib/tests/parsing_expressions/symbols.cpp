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
