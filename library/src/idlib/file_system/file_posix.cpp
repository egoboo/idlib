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

#include "idlib/file_system/file_posix.hpp"

#if defined(ID_POSIX)

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define IDLIB_PRIVATE 1
#include "idlib/file_system/error.hpp"
#undef IDLIB_PRIVATE

#include "idlib/file_system/header.in"

void file_descriptor_impl::open(const std::string& pathname, access_mode access_mode, create_mode create_mode) noexcept
{
    close();
	m_access_mode = access_mode;
    int flags = 0;
    
    //
    switch (access_mode)
    {
        case idlib::file_system::access_mode::read:
            flags = O_RDONLY;
            break;
        case idlib::file_system::access_mode::write:
            flags = O_WRONLY;
            break;
        case idlib::file_system::access_mode::read_write:
            flags = O_RDWR;
            break;
        default:
            return;
    };

    //
    switch (create_mode)
    {
    case idlib::file_system::create_mode::create_not_existing:
        flags |= O_CREAT;
        break;
    case idlib::file_system::create_mode::open_existing:
        break;
	case idlib::file_system::create_mode::fail_existing:
		flags |= O_CREAT | O_EXCL;
		break;
    default:
        return;
    };
    m_handle = ::open(pathname.c_str(), flags, 0);
}

bool file_descriptor_impl::is_open() const noexcept
{
    return -1 != m_handle;
}

void file_descriptor_impl::close() noexcept
{
    if (-1 != m_handle)
    {
        ::close(m_handle);
        m_handle = -1;
    }
}

file_descriptor_impl::file_descriptor_impl() noexcept :
    m_handle(-1)
{}

file_descriptor_impl::~file_descriptor_impl() noexcept
{
    close();
}

size_t file_descriptor_impl::size() const
{
    if (!is_open())
    {
        throw idlib::file_system::error(__FILE__, __LINE__, "unable to determine file size: file is not open");
    }
    struct stat buf;
    if (-1 == fstat(m_handle, &buf))
    {
        errno = 0;
        throw idlib::file_system::error(__FILE__, __LINE__, "unable to determine file size");
    }
    return buf.st_size;
}

#include "idlib/file_system/footer.in"

#endif
