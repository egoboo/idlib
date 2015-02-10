#pragma once

#pragma push_macro("IDLIB_PRIVATE")
#define IDLIB_PRIVATE 1

#include "idlib/utility/platform.hpp"
#include "idlib/file_system/file.hpp"

#if defined(ID_WINDOWS)
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>

#include "idlib/file_system/header.in"

/// @brief A Windows memory mapped file.
class mapped_file_descriptor_impl
{
private:
    file_descriptor m_file_descriptor;
    HANDLE m_file_mapping_handle;
	size_t m_size;
    void *m_data;
    bool m_writing; ///< @brief Is the file opened for writing.
    bool m_reading; ///< @brief Is the file opened for reading.
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

#undef IDLIB_PRIVATE
#pragma pop_macro("IDLIB_PRIVATE")
