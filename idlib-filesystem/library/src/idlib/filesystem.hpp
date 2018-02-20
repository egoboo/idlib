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

/// @file idlib/filesystem.hpp
/// @brief Master include file of the Idlib file system library.
/// @author Michael Heilmann

#pragma once

#pragma push_macro("IDLIB_PRIVATE")
#undef IDLIB_PRIVATE
#define IDLIB_PRIVATE (1)

#include "idlib/filesystem/access_mode.hpp"
#include "idlib/filesystem/create_directory.hpp"
#include "idlib/filesystem/copy_directory_contents.hpp"
#include "idlib/filesystem/copy_regular_file.hpp"
#include "idlib/filesystem/delete_directory.hpp"
#include "idlib/filesystem/delete_directory_recursive.hpp"
#include "idlib/filesystem/delete_regular.hpp"
#include "idlib/filesystem/directory_iterator.hpp"
#include "idlib/filesystem/error.hpp"
#include "idlib/filesystem/executable_directory.hpp"
#include "idlib/filesystem/exists.hpp"
#include "idlib/filesystem/extension.hpp"
#include "idlib/filesystem/file.hpp"
#include "idlib/filesystem/is_directory.hpp"
#include "idlib/filesystem/is_regular.hpp"
#include "idlib/filesystem/mapped_file.hpp"
#include "idlib/filesystem/status.hpp"
#include "idlib/filesystem/working_directory.hpp"
#include "idlib/filesystem/directory_separator.hpp"

#undef IDLIB_PRIVATE
#pragma pop_macro("IDLIB_PRIVATE")
