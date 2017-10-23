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

namespace id { namespace tests { namespace c { namespace qualified_name {

/// Assert selected strings which are not qualified name strings are rejected.
TEST(non_qualified_name_strings_rejection, reject_non_qualified_name_strings)
{
    const std::vector<std::string> words
    {
        "",
        ".",
        ".egoboo",
        "org.egoboo.",
        "org.",
    };
    for (const auto& word : words)
    {
        try
        {
            id::c::qualified_name qualified_name(word);
            ASSERT_TRUE(false);
        }
        catch (...)
        {
        }
    }
}

} } } } // namespace id::tests::c::qualified_name
