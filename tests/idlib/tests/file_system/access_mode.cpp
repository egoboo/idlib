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

namespace id { namespace tests { namespace file_system {

TEST(access_mode_test, test_access_mode)
{
    using namespace id::file_system;
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

} } } // namespace id::tests::file_system
