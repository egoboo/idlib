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

#include "idlib/file_system/file.hpp"

#include "idlib/file_system/header.in"

// Forward declaration.
class mapped_file_descriptor_impl;

/// @brief A mapped file descriptor.
class mapped_file_descriptor
{
private:
    /// @brief The pointer to the implementation.
    std::unique_ptr<mapped_file_descriptor_impl> m_pimpl;
public:
    /// @brief Open a memory mapped file for writing.
    /// @param pathname the pathname of the file
    /// @param create_mode the create mode
    /// @param size the size, in Bytes, of the memory mapped file
    void open_write(const std::string& pathname, create_mode create_mode, size_t size) noexcept;
    /// @brief Open a memory mapped file for reading.
    /// @param pathname the pathname of the file
    /// @param create_mode the create mode
    void open_read(const std::string& pathname, create_mode create_mode) noexcept;

    /// @brief Get if the mapped file descriptor is open.
    /// @return @a true if the mapped descriptor is open, @a false otherwise
    bool is_open() const noexcept;

    /// @brief Get if the mapped file descriptor is open for reading.
    /// @return @a true if the mapped file descriptor is open for reading, @a false otherwise
    bool is_opened_for_reading() const noexcept;

    /// @brief Get if the mapped file descriptor is open for writing.
    /// @return @a true if the mapped file descriptor is open for writing, @a false otherwise
    bool is_opened_for_writing() const noexcept;

    /// @brief Ensure the mapped file descriptor is closed.
    void close() noexcept;

    /// @brief A pointer to an array of @a size() Bytes.
    /// writing (reading) if the file is not opened for writing (reading) or an access outside of the bounds of the array is undefined behaviour.
    char *data();

    /// @brief The size, in Bytes, of the mapped file.
    /// @return The size, in Bytes, of the mapped file
    size_t size() const;

    /// @brief Construct this mapped file descriptor.
    /// @post The mapped file descriptor is closed.
    mapped_file_descriptor();

    /// @brief Destruct this mapped file descriptor.
    /// @post The file descriptor is closed.
    ~mapped_file_descriptor() noexcept;

public:
    // Delete copy constructor.
    mapped_file_descriptor(const mapped_file_descriptor&) = delete;

    // Delete copy assignment operator.
    mapped_file_descriptor& operator=(const mapped_file_descriptor&) = delete;

}; // class mapped_file_descriptor

#include "idlib/file_system/footer.in"
