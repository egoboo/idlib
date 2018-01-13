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

#include "idlib/file_system/mapped_file_posix.hpp"

#if defined(ID_POSIX)

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
