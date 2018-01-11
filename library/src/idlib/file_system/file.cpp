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

#pragma push_macro("IDLIB_PRIVATE")
#undef IDLIB_PRIVATE
#define IDLIB_PRIVATE 1
#include "idlib/file_system/file.hpp"
#undef IDLIB_PRIVATE
#pragma pop_macro("IDLIB_PRIVATE")

#if defined(ID_WINDOWS)
	#include "idlib/file_system/file_windows.hpp"
#elif defined(ID_POSIX)
    #include "idlib/file_system/file_posix.hpp"
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
