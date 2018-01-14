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

#include "idlib/file_system/status_windows.hpp"

#if defined (ID_WINDOWS)

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>

#include "idlib/file_system/header.in"

file_status status_impl(const std::string& pathname)
{
    if (pathname.empty())
    {
        return file_status(file_type::none);
    }
    DWORD t = GetFileAttributesA(pathname.c_str());
	if (t == INVALID_FILE_ATTRIBUTES)
	{
		// error or not found
		t = GetLastError();
		SetLastError(0);
		if (t == ERROR_FILE_NOT_FOUND    ||
            t == ERROR_PATH_NOT_FOUND    ||
            t == ERROR_INVALID_NAME      ||
            t == ERROR_INVALID_DRIVE     ||
            t == ERROR_NOT_READY         ||
            t == ERROR_INVALID_PARAMETER ||
            t == ERROR_BAD_PATHNAME      ||
            t == ERROR_BAD_NETPATH)
		{
			return file_status(file_type::not_found); // not found
		}
		else
		{
			return file_status(file_type::none); // error
		}
	}
	if (FILE_ATTRIBUTE_DIRECTORY == (FILE_ATTRIBUTE_DIRECTORY & t))
		return file_status(file_type::directory);
	else
		return file_status(file_type::regular);
		
}

#include "idlib/file_system/footer.in"

#endif
