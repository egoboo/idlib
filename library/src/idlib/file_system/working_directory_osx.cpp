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

#include "idlib/file_system/working_directory_osx.hpp"

#if defined(ID_OSX)

#include <errno.h>
#include <unistd.h>

#include "idlib/file_system/header.in"

std::string get_working_directory_impl()
{
	size_t size = 512 + 1;
	auto buffer = std::make_unique<char[]>(size);
	while (!getcwd(buffer.get(), size))
	{
		if (errno == ERANGE)
		{
			size_t new_size = size;
			if (std::numeric_limits<size_t>::max() / size <= 2) {
				new_size = std::numeric_limits<size_t>::max();
			} else {
				new_size *= 2;
			}
			auto new_buffer = std::make_unique<char[]>(new_size);
			memcpy(new_buffer.get(), buffer.get(), size);
			std::swap(buffer, new_buffer);
		}
		else
		{
			throw std::bad_alloc();
		}
	}
	return std::string(buffer.get());
}

#include "idlib/file_system/footer.in"

#endif
