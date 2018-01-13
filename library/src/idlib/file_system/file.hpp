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
