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
#include "idlib/idlib.hpp"

namespace id { namespace tests {

TEST(prefix_testing, test_prefix)
{
    static const std::string word = "abcdef";
    static const std::vector<std::string> true_prefixes =
    {
        "",
        "a",
        "ab",
        "abc",
        "abcd",
        "abcde",
    };
    static const std::vector<std::string> false_prefixes =
    {
        "abcdef",
    };
    std::vector<std::string> prefixes;
    prefixes.insert(prefixes.end(), true_prefixes.cbegin(), true_prefixes.cend());
    prefixes.insert(prefixes.end(), false_prefixes.cbegin(), false_prefixes.cend());
    // Assert prefixes are detected as such.
    for (const auto& prefix : prefixes)
    {
        ASSERT_EQ(true, id::is_prefix(word, prefix));
    }
    // Assert true prefixes are detected as such and as prefixes as well.
    for (const auto& prefix : true_prefixes)
    {
        ASSERT_EQ(true, id::is_true_prefix(word, prefix));
        ASSERT_EQ(true, id::is_prefix(word, prefix));
    }
    // Assert false prefixes are not detected as true prefixes.
    for (const auto& prefix : false_prefixes)
    {
        ASSERT_EQ(false, id::is_true_prefix(word, prefix));
    }
}

} } // namespace id::tests
