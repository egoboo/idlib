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
#include "idlib/file_system.hpp"

namespace id { namespace file_system { namespace tests {

TEST(working_directory_tests, test_return_value)
{
	auto s = id::file_system::get_working_directory();
	ASSERT_FALSE((s.size() == 1 && s[0] == '.') || (s.size() == 2 && s[0] == '.' && s[1] == '.'));
	ASSERT_FALSE(s.size() == 0);
}

} } } // namespace id::test::file_system
