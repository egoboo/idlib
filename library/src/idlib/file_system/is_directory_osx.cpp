#include "idlib/file_system/is_directory_osx.hpp"

#if defined (ID_OSX)

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "idlib/file_system/header.in"

bool is_directory_impl(const std::string& filename)
{
    struct stat t;
    if (!stat(filename.c_str(), &t))
    {
        return (0 != S_ISDIR(t.st_mode)) ? true : false;
    }
    return false;
}

#include "idlib/file_system/footer.in"

#endif
