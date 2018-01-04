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

#pragma once

#include "idlib/utility/platform.hpp"

#include "idlib/file_system/access_mode.hpp"
#include "idlib/file_system/create_mode.hpp"

#include "idlib/file_system/header.in"

// Forward declaration.
class file_descriptor_impl;

/// @brief A file descriptor.
/// @remark Implemented using the PIMPL idiom to avoid namespace pollution by system-specific header files.
class file_descriptor
{
private:
	/// @brief The pointer to the implementation.
	std::unique_ptr<file_descriptor_impl> m_pimpl;
public:
    /// @brief Construct the file descriptor.
    /// @post The file descriptor is closed.
    file_descriptor();

    /// @brief Destruct the file descriptor.
    /// @post The file descriptor is closed.
    ~file_descriptor() noexcept;
	
    // Delete copy constructor.
    file_descriptor(const file_descriptor&) = delete;

    // Delete copy assignment operator.
    file_descriptor& operator=(const file_descriptor&) = delete;
	
    /// @brief Ensure the file descriptor is open.
    /// @param pathname the pathname of the file
    /// @param access_mode the access mode
    /// @param create_mode the create mode
    void open(const std::string& pathname, access_mode access_mode, create_mode create_mode) noexcept;

    /// @brief Get if the file descriptor is open.
    /// @return @a true if the descriptor is open, @a false otherwise
    bool is_open() const noexcept;

    /// @brief Ensure the file descriptor is closed.
    void close() noexcept;
	
    /// @brief Get the size, in Bytes, of the file size.
    /// @return the size, in Bytes, of the file
    /// @pre The file is open.
    /// @throw id::file_system::read_write_error the file is not open or the environment fails
    size_t size() const;
	
    /// @brief Get the internal handle.
	/// @return an opaque pointer
	void *handle();

}; // class file_descriptor

#include "idlib/file_system/footer.in"
