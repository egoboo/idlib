#pragma once

#include "idlib/file_system/file_type.hpp"

#include "idlib/file_system/header.in"

class file_status
{
public:
	file_status() noexcept;

	explicit file_status(file_type type) noexcept;

	file_type type() const noexcept;

	void type(file_type type) noexcept;

	file_status(const file_status&) noexcept = default;

	file_status(file_status&&) noexcept = default;

	file_status& operator=(const file_status& other) noexcept = default;

	file_status& operator=(file_status&& other) noexcept = default;
	
private:
	file_type m_type;
}; // class file_status

#include "idlib/file_system/footer.in"
