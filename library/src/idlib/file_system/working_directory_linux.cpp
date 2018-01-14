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

#include "idlib/file_system/working_directory_linux.hpp"

#if defined(ID_LINUX)

#include <memory>

#include <unistd.h>

#include "idlib/file_system/header.in"

std::string get_working_directory_impl()
{
	std::unique_ptr<char, decltype(std::free) *> path{get_current_dir_name(), std::free };
	if (!path)
	{
		throw std::runtime_error("unable to obtain working directory");
	}
	return std::string(path.get());
}

#include "idlib/file_system/footer.in"

#endif
