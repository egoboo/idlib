#include "idlib/file_system/create_directory_windows.hpp"

#if defined (ID_WINDOWS)

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>

#include "idlib/file_system/header.in"

bool create_directory_impl(const std::string& pathname)
{
    return (0 != CreateDirectoryA(pathname.c_str(), NULL)) ? true : false;
}

#include "idlib/file_system/footer.in"

#endif
