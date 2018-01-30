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
#include "idlib/idlib.hpp"

namespace idlib { namespace tests {

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
        ASSERT_EQ(true, idlib::is_prefix(word, prefix));
    }
    // Assert true prefixes are detected as such and as prefixes as well.
    for (const auto& prefix : true_prefixes)
    {
        ASSERT_EQ(true, idlib::is_true_prefix(word, prefix));
        ASSERT_EQ(true, idlib::is_prefix(word, prefix));
    }
    // Assert false prefixes are not detected as true prefixes.
    for (const auto& prefix : false_prefixes)
    {
        ASSERT_EQ(false, idlib::is_true_prefix(word, prefix));
    }
}

} } // namespace idlib::tests
