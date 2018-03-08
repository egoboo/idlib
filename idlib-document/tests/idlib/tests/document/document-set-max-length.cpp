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

static void test_set_max_length(idlib::document_trim_policy trim_policy)
{
    idlib::document d;
    d.set_trim_policy(trim_policy);
    document_utilities tu;
    static const auto t = std::string("Hello, World!\n");
    //
    for (size_t i = 0, n = t.size(); i <= n; ++i)
    {
        int text_set_count = 0;
        int text_erased_count = 0;

        d.set_max_length(std::numeric_limits<size_t>::max());
        tu.connect(document_utilities::REJECT_REPLACE |
                   document_utilities::REJECT_INSERT, d);
        tu.m_connections.push_back(d.text_set_signal.subscribe([&text_set_count](const auto& e) {
            text_set_count++;
        }));
        tu.m_connections.push_back(d.text_erased_signal.subscribe([&text_erased_count](const auto& e) {
            text_erased_count++;
        }));
        d.set_text(t);
        d.set_max_length(i);
        tu.disconnect();
        auto required = i < t.size() ? i : t.size();
        if (i < t.size()) {
            ASSERT_EQ(text_erased_count, 1);
        }
        if (t.size() < i)
        {
            ASSERT_EQ(text_set_count, 1);
        }
        ASSERT_EQ(d.get_text().size(), required);
    }
}

TEST(document_test, max_text_length) {
    test_set_max_length(idlib::document_trim_policy::leading);
    test_set_max_length(idlib::document_trim_policy::trailing);
}

} // namespace idlib::tests
