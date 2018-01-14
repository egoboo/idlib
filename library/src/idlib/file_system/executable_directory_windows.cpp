#include "idlib/file_system/executable_directory_windows.hpp"

#if defined (ID_WINDOWS)

#define NOMINMAX
#include <Windows.h>
#include <Shlwapi.h>

#include "idlib/file_system/header.in"

std::string get_executable_directory_impl()
{
    char temporary[MAX_PATH];
    GetModuleFileNameA(NULL, temporary, MAX_PATH);
    PathRemoveFileSpecA(temporary);
	return temporary;
}

#include "idlib/file_system/footer.in"
	
#endif

