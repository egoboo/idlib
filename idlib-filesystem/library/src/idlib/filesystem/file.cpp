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

#pragma push_macro("IDLIB_PRIVATE")
#undef IDLIB_PRIVATE
#define IDLIB_PRIVATE 1
#include "idlib/filesystem/file.hpp"
#undef IDLIB_PRIVATE
#pragma pop_macro("IDLIB_PRIVATE")

#if defined(ID_WINDOWS)
	#include "idlib/filesystem/file_windows.hpp"
#elif defined(ID_POSIX)
    #include "idlib/filesystem/file_posix.hpp"
#else
	#error("operating system not supported")	
#endif

#include "idlib/filesystem/header.in"

file_descriptor::file_descriptor() :
	m_pimpl(std::make_unique<file_descriptor_impl>())
{}

file_descriptor::~file_descriptor() noexcept
{}

void file_descriptor::open(const std::string& pathname, access_mode access_mode, create_mode create_mode) noexcept
{
	m_pimpl->open(pathname, access_mode, create_mode);
}

bool file_descriptor::is_open() const noexcept
{
	return m_pimpl->is_open();
}

void file_descriptor::close() noexcept
{
	m_pimpl->close();
}

size_t file_descriptor::size() const
{
	return m_pimpl->size();
}

void *file_descriptor::handle()
{
	return m_pimpl->handle();
}

#include "idlib/filesystem/footer.in"
