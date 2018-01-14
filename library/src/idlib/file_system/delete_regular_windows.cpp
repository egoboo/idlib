#include "idlib/file_system/delete_regular_windows.hpp"

#if defined (ID_WINDOWS)

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>

#include "idlib/file_system/header.in"

void delete_regular_impl(const std::string& pathname)
{
    if (!pathname.empty())
    {
        DeleteFileA(pathname.c_str());
    }
}

#include "idlib/file_system/footer.in"

#endif
