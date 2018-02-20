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

#include "idlib/filesystem/status_posix.hpp"

#if defined (ID_POSIX)

#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "idlib/filesystem/header.in"

file_status status_impl(const std::string& pathname)
{
    struct stat t;
    int result = stat(pathname.c_str(), &t);
	if (0 == result)
	{
        if (0 != S_ISDIR(t.st_mode))
			return file_status(file_type::directory);
		else if (0 != S_ISREG(t.st_mode))
			return file_status(file_type::regular);
		else
			return file_status(file_type::unknown);
    }
	else
	{
		if (errno == ENOTDIR || errno == ENOENT || errno == ENAMETOOLONG || errno == EACCES)
			// ENOTDIR, ENOENT, ENAMETOOLONG, and EACCES all imply that the file does not exist or is not accessible due to permission constraints
			return file_status(file_type::not_found);
		else if (errno == EOVERFLOW) // EOVERFLOW indicates that some file exists but is not accessible due to technical constraints
			return file_status(file_type::unknown);
		else /*if (errno == ELOOP || errno == ENOMEN || errno == EFAULT || errno == EBADF)*/
			return file_status(file_type::none);
	}
}

#include "idlib/filesystem/footer.in"

#endif
