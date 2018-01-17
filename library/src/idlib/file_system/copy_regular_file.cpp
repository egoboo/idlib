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

#include "idlib/file_system/copy_regular_file.hpp"

#include "idlib/platform.hpp"
#if defined (ID_WINDOWS)
    #include "idlib/file_system/copy_regular_file_windows.hpp"
#elif defined (ID_POSIX)
    #include "idlib/file_system/copy_regular_file_posix.hpp"
#else
    #error("operating system not supported")	
#endif

#include "idlib/file_system/header.in"

bool copy_regular_file(const std::string& source, const std::string& target, bool fail_existing)
{ return copy_regular_file_impl(source, target, fail_existing); }

#include "idlib/file_system/footer.in"
