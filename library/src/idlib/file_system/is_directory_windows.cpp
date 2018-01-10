#include "idlib/file_system/is_directory_windows.hpp"

#if defined (ID_WINDOWS)

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>

#include "idlib/file_system/header.in"

bool is_directory_impl(const std::string& filename)
{
    if (filename.empty())
    {
        return false;
    }
    DWORD t = GetFileAttributesA(filename.c_str());
    return FILE_ATTRIBUTE_DIRECTORY == (FILE_ATTRIBUTE_DIRECTORY & t);
}

#include "idlib/file_system/footer.in"

#endif
