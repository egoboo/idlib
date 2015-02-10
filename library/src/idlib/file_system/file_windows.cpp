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
    case id::file_system::access_mode::none:
        break;
    case id::file_system::access_mode::read:
        dwAccessMode = GENERIC_READ;
        break;
    case id::file_system::access_mode::write:
        dwAccessMode = GENERIC_WRITE;
        break;
    case id::file_system::access_mode::read_write:
        dwAccessMode = GENERIC_READ | GENERIC_WRITE;
        break;
    default:
        return;
    };
    DWORD dwShareMode = FILE_SHARE_READ | FILE_SHARE_WRITE;
    DWORD dwCreateMode = 0;
    switch (create_mode)
    {
    case id::file_system::create_mode::create_not_existing:
        dwCreateMode = OPEN_ALWAYS;
        break;
    case id::file_system::create_mode::open_existing:
        dwCreateMode = OPEN_EXISTING;
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
        throw id::file_system::error(__FILE__, __LINE__, "unable to determine file size: file is not open");
    }
    LARGE_INTEGER large_integer;
    if (!GetFileSizeEx(m_handle, &large_integer))
    {
        throw id::file_system::error(__FILE__, __LINE__, "unable to determine file size");
    }
    #pragma push_macro("max")
    #undef max
    if (large_integer.QuadPart > std::numeric_limits<size_t>::max() || large_integer.QuadPart < 0)
    {
        throw id::file_system::error(__FILE__, __LINE__, "unable to determine file size");
    }
    #pragma pop_macro("max")
    int64_t size = large_integer.QuadPart;
    return size;
}

#include "idlib/file_system/footer.in"

#endif
