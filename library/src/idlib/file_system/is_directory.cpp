#include "idlib/file_system/is_directory.hpp"

#if defined (ID_WINDOWS)
	#include "idlib/file_system/is_directory_windows.hpp"
#elif defined (ID_LINUX)
	#include "idlib/file_system/is_directory_linux.hpp"
#elif defined (ID_OSX)
	#include "idlib/file_system/is_directory_osx.hpp"
#else
    #error("operating system not supported")	
#endif

#include "idlib/file_system/header.in"

bool is_directory(const std::string& filename)
{ return is_directory_impl(filename); }

#include "idlib/file_system/footer.in"
