#include "idlib/file_system/file_status.hpp"

#include "idlib/file_system/header.in"

file_status::file_status() noexcept
	: file_status(file_type::none)
{}

file_status::file_status(file_type type) noexcept
	: m_type(type)
{}

file_type file_status::type() const noexcept
{ return m_type; }

void file_status::type(file_type type) noexcept
{ m_type = type; }

#include "idlib/file_system/footer.in"
