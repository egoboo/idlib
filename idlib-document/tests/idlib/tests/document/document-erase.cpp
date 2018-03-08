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

#include "idlib/tests/document/utilities.hpp"

namespace idlib::tests {

TEST(document_test, erase_suffix)
{
    idlib::document d;
    document_utilities tu;
    static const auto t = std::string("Hello, World!\n");
    d.set_text(t);
    tu.connect(document_utilities::REJECT_REPLACE |
               document_utilities::REJECT_INSERT |
               document_utilities::REJECT_SET,
               d);
    d.erase(std::string("Hello, ").size(), std::string("World!\n").size());
    tu.disconnect();
    ASSERT_EQ(d.get_text(), "Hello, ");
}

TEST(document_test, erase_prefix)
{
    idlib::document d;
    document_utilities tu;
    static const auto t = std::string("Hello, World!\n");
    d.set_text(t);
    tu.connect(document_utilities::REJECT_REPLACE |
               document_utilities::REJECT_INSERT |
               document_utilities::REJECT_SET,
               d);
    d.erase(0, std::string("Hello, ").size());
    tu.disconnect();
    ASSERT_EQ(d.get_text(), "World!\n");
}

TEST(document_test, erase_all)
{
    idlib::document d;
    document_utilities tu;
    static const auto t = std::string("Hello, World!\n");
    d.set_text(t);
    tu.connect(document_utilities::REJECT_REPLACE |
               document_utilities::REJECT_INSERT |
               document_utilities::REJECT_SET,
               d);
    d.erase(0, d.get_text().size());
    tu.disconnect();
    ASSERT_TRUE(d.get_text().empty());
}

TEST(document_test, erase_none)
{
    idlib::document d;
    document_utilities tu;
    static const auto t = std::string("Hello, World!\n");
    for (size_t i = 0, n = d.get_text().size(); i < n; ++i)
    {
        d.set_text(t);
        tu.connect(document_utilities::REJECT_REPLACE |
                   document_utilities::REJECT_INSERT |
                   document_utilities::REJECT_ERASE |
                   document_utilities::REJECT_SET,
                   d);
        d.erase(i, 0);
        tu.disconnect();
        ASSERT_EQ(d.get_text(), t);
    }
}

} // namespace idlib::tests
