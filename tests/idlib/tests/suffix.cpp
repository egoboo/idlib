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
#include <idlib/idlib.hpp>
#include <vector>

namespace id { namespace tests {

TEST(suffix_testing, test_suffix)
{
    static const std::string word = "abcdef";
    static const std::vector<std::string> true_suffixes =
    {
        "",
        "f",
        "ef",
        "def",
        "cdef",
        "bcdef",
    };
    static const std::vector<std::string> false_suffixes =
    {
        "abcdef",
    };
    std::vector<std::string> suffixes;
    suffixes.insert(suffixes.end(), true_suffixes.cbegin(), true_suffixes.cend());
    suffixes.insert(suffixes.end(), false_suffixes.cbegin(), false_suffixes.cend());
    // Assert prefixes are detected as such.
    for (const auto& suffix : suffixes)
    {
        ASSERT_EQ(true, id::is_suffix(word, suffix));
    }
    // Assert true suffixes are detected as such and as suffixes as well.
    for (const auto& suffix : true_suffixes)
    {
        ASSERT_EQ(true, id::is_true_suffix(word, suffix));
        ASSERT_EQ(true, id::is_suffix(word, suffix));
    }
    // Assert false suffixes are not detected as true suffixes.
    for (const auto& suffix : false_suffixes)
    {
        ASSERT_EQ(false, id::is_true_suffix(word, suffix));
    }
}

} } // namespace id::tests
