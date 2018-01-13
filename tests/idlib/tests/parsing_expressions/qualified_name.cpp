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
using qualified_name = id::parsing_expressions::qualified_name<symbol>;

TEST(qualified_name_testing, test_acceptance)
{
    auto p = qualified_name();
    const std::vector<string> words
        {
            "org.egoboo",
            "org.egoboo.ego",
            "org.egoboo.id"
        };
    for (const auto& word : words)
    {
        auto s = word.cbegin();
        auto e = word.cend();
        ASSERT_EQ(true, static_cast<bool>(p(s, e)));
        ASSERT_EQ(parse(p, s, e).range().end(), e);
        ASSERT_EQ(false, static_cast<bool>(p(p(s, e).range().end(), e)));
    }
}

TEST(qualified_name, test_rejection)
{
    auto p = qualified_name();
    const std::vector<std::tuple<string, bool, size_t>> words
    {
            { ".egoboo", false, 0 },
            { "org.", true, 3 },
            { "org.egoboo.", true, 10 },
            { "org.#", true, 3 },
            { "org.egoboo.#", true, 10 },
    };
    for (const auto& word : words)
    {
        auto s = std::get<0>(word).cbegin();
        auto e = std::get<0>(word).cend();
        ASSERT_EQ(std::get<1>(word), static_cast<bool>(p(s, e)));
        auto a = p(s,e).range().end();
        auto b = std::get<0>(word).cbegin() + std::get<2>(word);
        ASSERT_EQ(a, b);
    }
}

#include "idlib/tests/parsing_expressions/footer.in"
