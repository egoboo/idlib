// Copyright Michael Heilmann 2016, 2017, 2018.
//
// This file is part of Idlib.
//
// Idlib is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Idlib is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Idlib. If not, see <http://www.gnu.org/licenses/>.

/// @file idlib/file_system/working_directory.cpp
/// @brief Determine the working directory.
/// @author Michael Heilmann

#include "idlib/file_system/working_directory.hpp"

#if defined(ID_WINDOWS)
#include "idlib/file_system/working_directory_windows.hpp"
#elif defined(ID_OSX)
#include "idlib/file_system/working_directory_osx.hpp"
#elif defined(ID_LINUX)
#include "idlib/file_system/working_directory_linux.hpp"
#else
#error("operating system not supported")	
#endif

#include "idlib/file_system/header.in"

std::string get_working_directory()
{
	return get_working_directory_impl();
}

#include "idlib/file_system/footer.in"
