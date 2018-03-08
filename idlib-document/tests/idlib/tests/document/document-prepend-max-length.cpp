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

TEST(document_test, append_console_style_1)
{
    idlib::document d;
    document_utilities tu;
    static const auto t = std::string("xxxx");
    d.set_text(t);
    d.set_max_length(4);
    tu.connect(document_utilities::REJECT_ERASE | document_utilities::REJECT_SET | document_utilities::REJECT_REPLACE, d);
    d.append_text("yyyy");
    tu.disconnect();
    ASSERT_EQ(d.get_text(), "yyyy");
}

TEST(document_test, append_console_style_2)
{
    idlib::document d;
    document_utilities tu;
    static const auto t = std::string("xxxx");
    d.set_text(t);
    d.set_trim_policy(idlib::document_trim_policy::leading);
    d.set_max_length(6);
    tu.connect(document_utilities::REJECT_ERASE | document_utilities::REJECT_SET | document_utilities::REJECT_REPLACE, d);
    d.append_text("yyyy");
    tu.disconnect();
    ASSERT_EQ(d.get_text(), "xxyyyy");
}

} // namespace idlib::tests
