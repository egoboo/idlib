#include "idlib/file_system/working_directory_osx.hpp"

#if defined(ID_OSX)

#include <errno.h>
#include <unistd.h>

#include "idlib/file_system/header.in"

std::string get_working_directory_impl()
{
	size_t size = 512 + 1;
	auto buffer = std::make_unique<char[]>(size);
	while (!getcwd(buffer.get(), size))
	{
		if (errno == ERANGE)
		{
			size_t new_size = size;
			if (std::numeric_limits<size_t>::max() / size <= 2) {
				new_size = std::numeric_limits<size_t>::max();
			} else {
				new_size *= 2;
			}
			auto new_buffer = std::make_unique<char[]>(new_size);
			memcpy(new_buffer.get(), buffer.get(), size);
			std::swap(buffer, new_buffer);
		}
		else
		{
			throw std::bad_alloc();
		}
	}
	return std::string(buffer.get());
}

#include "idlib/file_system/footer.in"

#endif
