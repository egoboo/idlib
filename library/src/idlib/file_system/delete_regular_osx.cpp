#include "idlib/file_system/delete_regular_linux.hpp"

#if defined (ID_OSX)

#include <unistd.h>

#include "idlib/file_system/header.in"

void delete_regular_impl(const std::string& filename)
{
    unlink(filename.c_str());
}

#include "idlib/file_system/footer.in"

#endif
