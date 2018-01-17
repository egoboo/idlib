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

#pragma once

#include <string>

#include "idlib/file_system/header.in"

/// @brief Copy a regular file.
/// @param source the pathname of the source file
/// @param target the pathname of the target file
/// @param fail_existing @a true or @a false
/// @return @a true on success, @a false on failure
/// @remark The source file must be a regular file.
/// @remark The target file must not exist iff @a fail_existing is @a true.
/// @remark If the target file exists and is not a directory file and @a fail_existing is @a false, the target file is overwritten.
bool copy_regular_file(const std::string& source, const std::string& target, bool fail_existing);

#include "idlib/file_system/footer.in"
