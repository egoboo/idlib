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

/// @file idlib/file_system.hpp
/// @brief Master include file of the Idlib file system library.
/// @author Michael Heilmann

#pragma once

#pragma push_macro("IDLIB_PRIVATE")
#undef IDLIB_PRIVATE
#define IDLIB_PRIVATE (1)

#include "idlib/file_system/access_mode.hpp"
#include "idlib/file_system/create_directory.hpp"
#include "idlib/file_system/delete_regular.hpp"
#include "idlib/file_system/error.hpp"
#include "idlib/file_system/extension.hpp"
#include "idlib/file_system/file.hpp"
#include "idlib/file_system/is_directory.hpp"
#include "idlib/file_system/mapped_file.hpp"
#include "idlib/file_system/working_directory.hpp"
#include "idlib/file_system/directory_separator.hpp"

#undef IDLIB_PRIVATE
#pragma pop_macro("IDLIB_PRIVATE")
