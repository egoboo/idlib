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

#include "idlib/filesystem/copy_regular_file_posix.hpp"

#if defined (ID_POSIX)

#include "idlib/filesystem/mapped_file.hpp"
#include <memory.h>

#include "idlib/filesystem/header.in"

bool copy_regular_file_impl(const std::string& source, const std::string& target, bool fail_existing)
{
	mapped_file_descriptor source_descriptor;
	source_descriptor.open_read(source, create_mode::open_existing);
	if (!source_descriptor.is_open())
	{ return false; }
	
	mapped_file_descriptor target_descriptor;
	target_descriptor.open_write(target, fail_existing ? create_mode::fail_existing : create_mode::create_not_existing, source_descriptor.size());
	if (!target_descriptor.is_open())
	{ return false; }

	memcpy(target_descriptor.data(), source_descriptor.data(), source_descriptor.size());
	
	return true;
}

#include "idlib/filesystem/footer.in"

#endif
