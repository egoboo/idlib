#pragma push_macro("IDLIB_PRIVATE")
#undef IDLIB_PRIVATE
#define IDLIB_PRIVATE 1
#include "idlib/file_system/file.hpp"
#undef IDLIB_PRIVATE
#pragma pop_macro("IDLIB_PRIVATE")

#if defined(ID_WINDOWS)
	#include "idlib/file_system/file_windows.hpp"
#elif defined(ID_OSX)
    #error("operating system not supported")	
#elif defined(ID_LINUX)
	#include "idlib/file_system/file_linux.hpp"
#else
	#error("operating system not supported")	
#endif

#include "idlib/file_system/header.in"

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

#include "idlib/file_system/footer.in"
