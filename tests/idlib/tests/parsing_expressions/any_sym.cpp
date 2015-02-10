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
using namespace id::parsing_expressions;
using namespace std;

TEST(any_sym_testing, test_acceptance)
{
    auto p = any_sym<char>();
    const vector<pair<string, bool>> words
    {
        make_pair("", false),
        make_pair("x", true),
        make_pair("y", true),
        make_pair("z", true),
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

#include "idlib/tests/parsing_expressions/footer.in"
