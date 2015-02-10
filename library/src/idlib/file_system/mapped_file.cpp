#pragma push_macro("IDLIB_PRIVATE")
#undef IDLIB_PRIVATE
#define IDLIB_PRIVATE 1
#include "idlib/file_system/mapped_file.hpp"
#undef IDLIB_PRIVATE
#pragma pop_macro("IDLIB_PRIVATE")

#if defined(ID_WINDOWS)
#include "idlib/file_system/mapped_file_windows.hpp"
#elif defined(ID_OSX)
#error("operating system not supported")
#elif defined(ID_LINUX)
#include "idlib/file_system/mapped_file_linux.hpp"
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
