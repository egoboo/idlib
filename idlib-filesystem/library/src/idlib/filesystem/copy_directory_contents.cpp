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

#include "idlib/filesystem/copy_directory_contents.hpp"

#include "idlib/filesystem/create_directory.hpp"
#include "idlib/filesystem/copy_regular_file.hpp"
#include "idlib/filesystem/exists.hpp"
#include "idlib/filesystem/directory_iterator.hpp"
#include "idlib/filesystem/is_directory.hpp"
#include "idlib/filesystem/is_regular.hpp"
#include "idlib/filesystem/directory_separator.hpp"

#include "idlib/filesystem/header.in"

void copy_directory_contents(const std::string& source, const std::string& target)
{
	if (!is_directory(target))
	{
		return; /// @todo Policy-based error handling.
	}
    for (auto it = directory_iterator(source); it != directory_iterator(); ++it)
    {
        if (is_directory(*it))
		{
			if (!exists(target + get_directory_separator() + *it))
			{
				if (!create_directory(target + get_directory_separator() + *it))
				{
					return; /// @todo Policy-based error handling.
				}
			}
			else if (!is_directory(target + get_directory_separator() + *it))
			{
				return; /// @todo Policy-based error handling.
			}
			copy_directory_contents(source + get_directory_separator() + *it, target + get_directory_separator() + *it);
		}
		else
		{
			copy_regular_file(source + get_directory_separator() + *it, target + get_directory_separator() + *it, true);
		}
    }
}

#include "idlib/filesystem/footer.in"
