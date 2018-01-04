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

#include "idlib/file_system/file_linux.hpp"

#if defined(ID_LINUX)

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
        case id::file_system::access_mode::read:
            flags = O_RDONLY;
            break;
        case id::file_system::access_mode::write:
            flags = O_WRONLY;
            break;
        case id::file_system::access_mode::read_write:
            flags = O_RDWR;
            break;
        default:
            return;
    };

    //
    switch (create_mode)
    {
    case id::file_system::create_mode::create_not_existing:
        flags |= O_CREAT;
        break;
    case id::file_system::create_mode::open_existing:
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
        throw id::file_system::error(__FILE__, __LINE__, "unable to determine file size: file is not open");
    }
    struct stat buf;
    if (-1 == fstat(m_handle, &buf))
    {
        errno = 0;
        throw id::file_system::error(__FILE__, __LINE__, "unable to determine file size");
    }
    return buf.st_size;
}

#include "idlib/file_system/footer.in"

#endif
