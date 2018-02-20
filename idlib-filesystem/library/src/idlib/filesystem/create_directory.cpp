#include "idlib/filesystem/create_directory.hpp"

#include "idlib/platform.hpp"
#if defined (ID_WINDOWS)
    #include "idlib/filesystem/create_directory_windows.hpp"
#elif defined (ID_POSIX)
    #include "idlib/filesystem/create_directory_posix.hpp"
#else
    #error("operating system not supported")	
#endif

#include "idlib/filesystem/header.in"

bool create_directory(const std::string& pathname)
{ return create_directory_impl(pathname); }

#include "idlib/filesystem/footer.in"
