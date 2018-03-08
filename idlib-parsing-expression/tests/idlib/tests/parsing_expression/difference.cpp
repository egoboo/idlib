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

TEST(parsing_expressions,test_difference)
{
    using namespace idlib::parsing_expression;
    using namespace std;
    auto p = difference(digit<char>(), 
                                    ordered_choice(sym('1'),
                                                sym('3'),
                                                sym('5'),
                                                sym('7'),
                                                sym('9')));
    const std::vector<std::pair<std::string, bool>> words
    {
        std::make_pair("0", true), // even. accept.
        std::make_pair("1", false), // odd. reject.
        std::make_pair("2", true),
        std::make_pair("3", false),
        std::make_pair("4", true),
        std::make_pair("5", false),
        std::make_pair("6", true),
        std::make_pair("7", false),
        std::make_pair("8", true),
        std::make_pair("9", false),
    };
    for (const auto& word : words)
    {
        auto s = word.first.cbegin(),
             e = word.first.cend();
        auto m = parse(p, s, e);
        ASSERT_EQ(word.second, static_cast<bool>(m));
        if (word.second)
        {
            ASSERT_EQ(m.range().begin(), s);
            ASSERT_EQ(m.range().end(), e);
        }
        else
        {
            ASSERT_EQ(m.range().begin(), s);
            ASSERT_EQ(m.range().end(), s);
        }
        ASSERT_FALSE(parse(p, m.range().end(), e));
    }
}

#include "idlib/tests/parsing_expression/footer.in"
