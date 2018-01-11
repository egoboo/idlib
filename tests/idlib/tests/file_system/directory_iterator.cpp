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

namespace id { namespace file_system { namespace tests {

TEST(directory_iterator_tests, test1)
{
	using namespace id::file_system;
	ASSERT_TRUE(directory_iterator() == directory_iterator());
	ASSERT_FALSE(directory_iterator() != directory_iterator());
}

TEST(directory_iterator_tests, test2)
{
	using namespace id::file_system;
	for (auto it = directory_iterator(get_working_directory()); it != directory_iterator(); ++it)
	{
		std::cout << *it << std::endl;
	}
}

} } } // namespace id::file_system::tests
