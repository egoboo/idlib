#include "idlib/file_system/delete_regular.hpp"

#include "idlib/platform.hpp"

#if defined (ID_WINDOWS)
    #include "idlib/file_system/delete_regular_windows.hpp"
#elif defined (ID_POSIX)
    #include "idlib/file_system/delete_regular_posix.hpp"
#else
    #error("operating system not supported")	
#endif

#include "idlib/file_system/header.in"

void delete_regular(const std::string& pathname)
{ return delete_regular_impl(pathname); }

#include "idlib/file_system/footer.in"
