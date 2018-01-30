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

using symbol = char;
using string = std::basic_string<symbol>;

TEST(repetition_testing, test_repetition)
{
    auto p = idlib::parsing_expressions::repetition(idlib::parsing_expressions::sym('x'));
    const std::vector<string> words
    {
        "x",
        "xx",
        "xxx"
    };
    for (const auto& word : words)
    {
        auto s = word.cbegin();
        auto e = word.cend();
        ASSERT_TRUE(parse(p, s, e));
        ASSERT_EQ(parse(p, s, e).range().end(), word.cend());
    }
}

#include "idlib/tests/parsing_expressions/footer.in"
