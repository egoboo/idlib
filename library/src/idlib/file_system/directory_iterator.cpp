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

#include "idlib/file_system/directory_iterator.hpp"

#if defined (ID_WINDOWS)
	#include "idlib/file_system/directory_stream_windows.hpp"
#elif defined (ID_POSIX)
	#include "idlib/file_system/directory_stream_posix.hpp"
#endif

#include "idlib/file_system/header.in"

namespace internal {	

#if defined (ID_WINDOWS)
using impl = directory_stream_windows;
#elif defined (ID_POSIX)
using impl = directory_stream_posix;
#endif

directory_stream::directory_stream()
	: m_pimpl(new impl())
{}

directory_stream::~directory_stream()
{ 
    if (m_pimpl)
    { 
        delete static_cast<impl *>(m_pimpl); 
        m_pimpl = nullptr;
    } 
}

void directory_stream::open(const std::string& pathname)
{ static_cast<impl *>(m_pimpl)->open(pathname); }

bool directory_stream::has_value() const
{ return static_cast<const impl *>(m_pimpl)->has_value(); }
	
std::string directory_stream::get_value() const
{ return static_cast<const impl *>(m_pimpl)->get_value(); }

void directory_stream::next()
{ static_cast<impl *>(m_pimpl)->next(); }
	
} // namespace internal

#include "idlib/file_system/footer.in"
