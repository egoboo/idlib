#include "idlib/filesystem/create_directory_posix.hpp"

#if defined (ID_POSIX)

#include <sys/stat.h>
#include <sys/types.h>

#include "idlib/filesystem/header.in"

bool create_directory_impl(const std::string& pathname)
{
    if (0 != mkdir(pathname.c_str(), 0755))
    {
        errno = 0; // Clear errno.
        return false;
    }
    return true;
}

#include "idlib/filesystem/footer.in"

#endif
