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
        ASSERT_TRUE(exists(*it));
	}
}

} } } // namespace id::file_system::tests
