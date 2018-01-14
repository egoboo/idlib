#include "idlib/file_system/create_directory.hpp"

#if defined (ID_WINDOWS)
    #include "idlib/file_system/create_directory_windows.hpp"
#elif defined (ID_POSIX)
    #include "idlib/file_system/create_directory_posix.hpp"
#else
    #error("operating system not supported")	
#endif

#include "idlib/file_system/header.in"

bool create_directory(const std::string& pathname)
{ return create_directory_impl(pathname); }

#include "idlib/file_system/footer.in"
