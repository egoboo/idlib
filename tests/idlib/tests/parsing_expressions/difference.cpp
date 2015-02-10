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

TEST(parsing_expressions,test_difference)
{
    using namespace id::parsing_expressions;
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

#include "idlib/tests/parsing_expressions/footer.in"
