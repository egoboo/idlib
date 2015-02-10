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
