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

namespace idlib { namespace file_system { namespace tests {

TEST(access_mode_tests, test_access_mode)
{
    using namespace idlib::file_system;
    // Negation.
    ASSERT_EQ(~access_mode::all, access_mode::none);
    ASSERT_EQ(~access_mode::none, access_mode::all);
    ASSERT_EQ(~access_mode::write, access_mode::read);
    ASSERT_EQ(~access_mode::read, access_mode::write);
    // Equality. 
    ASSERT_EQ(access_mode::none, access_mode::none);
    ASSERT_EQ(access_mode::read, access_mode::read);
    ASSERT_EQ(access_mode::write, access_mode::write);
    ASSERT_EQ(access_mode::all, access_mode::all);
    // Inequality.
    ASSERT_NE(access_mode::all, access_mode::none);
    ASSERT_NE(access_mode::read, access_mode::write);
    ASSERT_NE(access_mode::write, access_mode::read);
    ASSERT_NE(access_mode::write, access_mode::none);
    // ...
    //
    ASSERT_EQ((access_mode::write | access_mode::read), access_mode::read_write);
    ASSERT_EQ((access_mode::read | access_mode::write), access_mode::read_write);
    // Aliases.
    ASSERT_EQ(access_mode::write_read, access_mode::read_write);
    //
    ASSERT_EQ((access_mode::read_write & access_mode::read), access_mode::read);
    ASSERT_EQ((access_mode::read_write & access_mode::write), access_mode::write);
    //
    ASSERT_EQ((access_mode::write & access_mode::read), access_mode::none);
    ASSERT_EQ((access_mode::read & access_mode::write), access_mode::none);
    //
    ASSERT_EQ((access_mode::read & access_mode::read), access_mode::read);
    ASSERT_EQ((access_mode::write & access_mode::write), access_mode::write);
}

} } } // namespace idlib::file_system::tests
