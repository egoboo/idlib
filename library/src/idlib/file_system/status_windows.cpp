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
