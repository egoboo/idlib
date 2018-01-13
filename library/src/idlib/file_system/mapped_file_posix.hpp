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

#pragma push_macro("IDLIB_PRIVATE")
#define IDLIB_PRIVATE 1

#include "idlib/utility/platform.hpp"
#include "idlib/file_system/file.hpp"

#if defined(ID_POSIX)

#include "idlib/file_system/header.in"

/// @brief A Linux memory mapped file.
class mapped_file_descriptor_impl
{
private:
    file_descriptor m_file_descriptor;
    size_t m_size;
    void *m_data;

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
    mapped_file_descriptor_impl() noexcept;

    /// @brief Destruct this mapped file descriptor.
    /// @post The file descriptor is closed.
    ~mapped_file_descriptor_impl() noexcept;

public:
    // Delete copy constructor.
    mapped_file_descriptor_impl(const mapped_file_descriptor_impl&) = delete;

    // Delete copy assignment operator.
    mapped_file_descriptor_impl& operator=(const mapped_file_descriptor_impl&) = delete;

}; // class mapped_file_descriptor_impl

#include "idlib/file_system/footer.in"

#endif
