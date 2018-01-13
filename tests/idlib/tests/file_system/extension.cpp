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
#include "idlib/file_system.hpp"

namespace id { namespace file_system { namespace tests {

TEST(extension_tests, tests_rejection)
{
	static const std::vector<std::string> es = 
	{
      "",
      " ",
      "/",
      "\\",
      "/",
      ".",
      ":",
      "?",
      "*",
	};
	
	for (const auto& e : es)
    {
		ASSERT_THROW((id::file_system::extension<char>(e)), id::runtime_error);
	}
}

} } } // namespace id::test::file_system
