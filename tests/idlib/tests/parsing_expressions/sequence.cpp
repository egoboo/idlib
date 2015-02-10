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

using string = std::basic_string<char>;
template <typename T>
using vector = std::vector<T>;

TEST(sequence_testing, test_sequence)
{
    auto p = id::parsing_expressions::sequence(id::parsing_expressions::sym('a'), id::parsing_expressions::sym('b'));
    const vector<string> words
    {
        "ab",
    };
    for (const auto& word : words)
    {
        auto s = word.cbegin();
        auto e = word.cend();
        ASSERT_TRUE(parse(p, s, e));
        ASSERT_EQ(parse(p,s, e).range().end(), word.cend());
    }
}

#include "idlib/tests/parsing_expressions/footer.in"
