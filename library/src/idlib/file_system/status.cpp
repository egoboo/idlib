#include "idlib/file_system/status.hpp"

#if defined (ID_WINDOWS)
	#include "idlib/file_system/status_windows.hpp"
#elif defined (ID_POSIX)
	#include "idlib/file_system/status_posix.hpp"
#else
    #error("operating system not supported")	
#endif

#include "idlib/file_system/header.in"

file_status status(const std::string& pathname)
{ return status_impl(pathname); }

#include "idlib/file_system/footer.in"
