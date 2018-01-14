#include "idlib/file_system/delete_regular_posix.hpp"

#if defined (ID_POSIX)

#include "idlib/file_system/header.in"

void delete_regular_impl(const std::string& pathname)
{
    unlink(pathname.c_str());
}

#include "idlib/file_system/footer.in"

#endif
