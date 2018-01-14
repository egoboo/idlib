#include "idlib/file_system/executable_directory.hpp"

#if defined(ID_WINDOWS)
	#include "idlib/file_system/executable_directory_windows.hpp"
#endif

#include "idlib/file_system/header.in"

std::optional<std::string> get_executable_directory()
{ 
	#if defined(ID_WINDOWS)
		return get_executable_directory_impl();
	#else
        return {};
	#endif
}

#include "idlib/file_system/footer.in"
