#include "idlib/file_system/status_posix.hpp"

#if defined (ID_POSIX)

#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "idlib/file_system/header.in"

file_status status_impl(const std::string& pathname)
{
    struct stat t;
    int result = stat(pathname.c_str(), &t);
	if (0 == result)
	{
        if (0 != S_ISDIR(t.st_mode))
			return file_status(file_type::directory);
		else if (0 != S_ISREG(t.st_mode))
			return file_status(file_type::regular);
		else
			return file_status(file_type::unknown);
    }
	else
	{
		if (errno = ENOTDIR || errno == ENOENT || errno == ENAMETOOLONG || errno == EACCES)
			// ENOTDIR, ENOENT, ENAMETOOLONG, and EACCES all imply that the file does not exist or is not accessible due to permission constraints
			return file_status(file_type::not_found);
		else if (errno == EOVERFLOW) // EOVERFLOW indicates that some file exists but is not accessible due to technical constraints
			return file_status(file_type::unknown);
		else /*if (errno == ELOOP || errno == ENOMEN || errno == EFAULT || errno == EBADF)*/
			return file_status(file_type::none);
	}
}

#include "idlib/file_system/footer.in"

#endif
