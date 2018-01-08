#include "idlib/file_system/working_directory_linux.hpp"

#if defined(ID_LINUX)

#include <unistd.h>

#include "idlib/file_system/header.in"

std::string get_working_directory_impl()
{
	std::unique_ptr<char, decltype(std::free) *> path{get_current_dir_name(), std::free };
	if (!path)
	{
		throw std::runtime_error("unable to obtain working directory");
	}
	return std::string(path.get());
}

#include "idlib/file_system/footer.in"

#endif
