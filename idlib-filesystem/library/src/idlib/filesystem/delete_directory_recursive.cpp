///////////////////////////////////////////////////////////////////////////////////////////////////
//
// Idlib: A C++ utility library
// Copyright (C) 2017-2018 Michael Heilmann
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "idlib/filesystem/delete_directory_recursive.hpp"

#include "idlib/filesystem/delete_directory.hpp"
#include "idlib/filesystem/is_directory.hpp"

#include "idlib/filesystem/delete_regular.hpp"
#include "idlib/filesystem/is_regular.hpp"

#include "idlib/filesystem/directory_iterator.hpp"
#include "idlib/filesystem/directory_separator.hpp"

#include "idlib/filesystem/header.in"

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

#include "idlib/filesystem/footer.in"
