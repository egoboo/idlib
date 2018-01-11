#include "idlib/file_system/delete_directory.hpp"

#if defined (ID_WINDOWS)
    #include "idlib/file_system/delete_directory_windows.hpp"
#elif defined (ID_POSIX)
    #include "idlib/file_system/delete_directory_posix.hpp"
#else
    #error("operating system not supported")	
#endif

#include "idlib/file_system/header.in"

bool delete_directory(const std::string& filename)
{ return delete_directory_impl(filename); }

#include "idlib/file_system/footer.in"
