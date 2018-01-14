#include "idlib/file_system/delete_directory_posix.hpp"

#if defined (ID_POSIX)

#include "idlib/file_system/header.in"

bool delete_directory_impl(const std::string& pathname)
{
    if (0 != rmdir(pathname.c_str()))
    {
        errno = 0; // Clear errno.
        return false;
    }
    return true;
}

#include "idlib/file_system/footer.in"

#endif
