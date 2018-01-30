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

#include "idlib/file_system/file_windows.hpp"

#if defined(ID_WINDOWS)

#define IDLIB_PRIVATE 1
#include "idlib/file_system/error.hpp"
#undef IDLIB_PRIVATE

#include "idlib/file_system/header.in"

void file_descriptor_impl::open(const std::string& pathname, access_mode access_mode, create_mode create_mode) noexcept
{
    close();
	m_access_mode = access_mode;
    DWORD dwAccessMode = 0;
    switch (access_mode)
    {
    case idlib::file_system::access_mode::none:
        break;
    case idlib::file_system::access_mode::read:
        dwAccessMode = GENERIC_READ;
        break;
    case idlib::file_system::access_mode::write:
        dwAccessMode = GENERIC_WRITE;
        break;
    case idlib::file_system::access_mode::read_write:
        dwAccessMode = GENERIC_READ | GENERIC_WRITE;
        break;
    default:
        return;
    };
    DWORD dwShareMode = FILE_SHARE_READ | FILE_SHARE_WRITE;
    DWORD dwCreateMode = 0;
    switch (create_mode)
    {
    case idlib::file_system::create_mode::create_not_existing:
        dwCreateMode = OPEN_ALWAYS;
        break;
    case idlib::file_system::create_mode::open_existing:
        dwCreateMode = OPEN_EXISTING;
        break;
	case idlib::file_system::create_mode::fail_existing:
		dwCreateMode = CREATE_NEW;
		break;
    default:
        return;
    };
    m_handle = CreateFileA(pathname.c_str(), dwAccessMode, dwShareMode, 0, dwCreateMode, FILE_ATTRIBUTE_NORMAL, 0);
}

bool file_descriptor_impl::is_open() const noexcept
{
    return INVALID_HANDLE_VALUE != m_handle;
}

void file_descriptor_impl::close() noexcept
{
    if (INVALID_HANDLE_VALUE != m_handle)
    {
        CloseHandle(m_handle);
        m_handle = INVALID_HANDLE_VALUE;
    }
}

file_descriptor_impl::file_descriptor_impl() noexcept :
	m_handle(INVALID_HANDLE_VALUE), m_access_mode(access_mode::none)
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
    LARGE_INTEGER large_integer;
    if (!GetFileSizeEx(m_handle, &large_integer))
    {
        throw idlib::file_system::error(__FILE__, __LINE__, "unable to determine file size");
    }
    #pragma push_macro("max")
    #undef max
    if (large_integer.QuadPart > std::numeric_limits<size_t>::max() || large_integer.QuadPart < 0)
    {
        throw idlib::file_system::error(__FILE__, __LINE__, "unable to determine file size");
    }
    #pragma pop_macro("max")
    int64_t size = large_integer.QuadPart;
    return size;
}

#include "idlib/file_system/footer.in"

#endif
