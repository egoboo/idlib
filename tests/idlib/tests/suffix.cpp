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
