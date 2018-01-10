#include "idlib/file_system/create_directory_windows.hpp"

#if defined (ID_WINDOWS)
    #include "idlib/file_system/create_directory_windows.hpp"
#elif defined (ID_LINUX)
    #include "idlib/file_system/create_directory_linux.hpp"
#elif defined (ID_OSX)
    #include "idlib/file_system/create_directory_osx.hpp"
#else
    #error("operating system not supported")	
#endif

#include "idlib/file_system/header.in"

bool create_directory(const std::string& filename)
{ return create_directory_impl(filename); }

#include "idlib/file_system/footer.in"
