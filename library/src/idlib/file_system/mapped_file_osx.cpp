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

#include "idlib/file_system/mapped_file_osx.hpp"

#if defined(ID_OSX)

#include <sys/mman.h>

#include "idlib/file_system/header.in"

void mapped_file_descriptor_impl::open_read(const std::string& pathname, create_mode create_mode) noexcept
{
    close();
    m_file_descriptor.open(pathname, id::file_system::access_mode::read, create_mode);
    if (!m_file_descriptor.is_open())
    {
        return;
    }
    m_size = m_file_descriptor.size();
    m_data = mmap(0, m_size, PROT_READ, MAP_SHARED, *((int *)m_file_descriptor.handle()), 0);
    if (MAP_FAILED == m_data)
    {
        errno = 0;
        m_file_descriptor.close();
        return;
    }
}

void mapped_file_descriptor_impl::open_write(const std::string& pathname, create_mode create_mode, size_t size) noexcept
{
    close();
    m_file_descriptor.open(pathname, id::file_system::access_mode::write, create_mode);
    if (!m_file_descriptor.is_open())
    {
        return;
    }
    m_size = size;
    m_data = mmap(0, m_size, PROT_READ, MAP_SHARED, *((int *)m_file_descriptor.handle()), 0);
    if (MAP_FAILED == m_data)
    {
        errno = 0;
        m_file_descriptor.close();
        return;
    }
}

bool mapped_file_descriptor_impl::is_open() const noexcept
{
    return MAP_FAILED != m_data;
}

void mapped_file_descriptor_impl::close() noexcept
{
    if (MAP_FAILED != m_data)
    {
        if (-1 == munmap(m_data, m_size))
        {
            perror("Error un-mmapping the file");
        }
        m_data = NULL;
    }
    m_file_descriptor.close();
}

char *mapped_file_descriptor_impl::data()
{
    return (char *)m_data;
}

size_t mapped_file_descriptor_impl::size() const
{
    return m_size;
}

mapped_file_descriptor_impl::mapped_file_descriptor_impl() noexcept :
    m_file_descriptor(), m_size((size_t)-1), m_data(MAP_FAILED)
{}

mapped_file_descriptor_impl::~mapped_file_descriptor_impl() noexcept
{
    close();
}

#include "idlib/file_system/footer.in"
#endif
