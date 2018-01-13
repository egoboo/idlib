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
#include "idlib/file_system/mapped_file.hpp"
#undef IDLIB_PRIVATE
#pragma pop_macro("IDLIB_PRIVATE")

#if defined(ID_WINDOWS)
	#include "idlib/file_system/mapped_file_windows.hpp"
#elif defined(ID_POSIX)
	#include "idlib/file_system/mapped_file_posix.hpp"
#else
	#error("operating system not supported")	
#endif

#include "idlib/file_system/header.in"

void mapped_file_descriptor::open_read(const std::string& pathname, create_mode create_mode) noexcept
{
    m_pimpl->open_read(pathname, create_mode);
}

void mapped_file_descriptor::open_write(const std::string& pathname, create_mode create_mode, size_t size) noexcept
{
    m_pimpl->open_write(pathname, create_mode, size);
}

bool mapped_file_descriptor::is_open() const noexcept
{
    return m_pimpl->is_open();
}

void mapped_file_descriptor::close() noexcept
{
    m_pimpl->close();
}

char *mapped_file_descriptor::data()
{
    return m_pimpl->data();
}

size_t mapped_file_descriptor::size() const
{
    return m_pimpl->size();
}

mapped_file_descriptor::mapped_file_descriptor() :
    m_pimpl(std::make_unique<mapped_file_descriptor_impl>())
{}

mapped_file_descriptor::~mapped_file_descriptor() noexcept
{}

#include "idlib/file_system/footer.in"
