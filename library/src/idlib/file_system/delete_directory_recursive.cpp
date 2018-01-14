#include "idlib/file_system/delete_directory_recursive.hpp"

#include "idlib/file_system/delete_directory.hpp"
#include "idlib/file_system/is_directory.hpp"

#include "idlib/file_system/delete_regular.hpp"
#include "idlib/file_system/is_regular.hpp"

#include "idlib/file_system/directory_iterator.hpp"
#include "idlib/file_system/directory_separator.hpp"

#include "idlib/file_system/header.in"

void delete_directory_recursive(const std::string& pathname)
{
	if (is_directory(pathname))
	{
		for (auto it = directory_iterator(pathname); it != directory_iterator(); ++it)
		{
			auto child_pathname = pathname + get_directory_separator() + *it;
			if (is_regular(child_pathname))
			{
				delete_regular(child_pathname);
			}
			else if (is_directory(child_pathname))
			{
				delete_directory_recursive(child_pathname);
			}
			else
			{
				// TODO: Shall we raise an exception or record the error? Shall we continue or abort?
			}
		}
		delete_directory(pathname);
	}
}

#include "idlib/file_system/footer.in"
