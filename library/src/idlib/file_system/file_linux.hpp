#pragma once

#pragma push_macro("IDLIB_PRIVATE")
#define IDLIB_PRIVATE 1
#include "idlib/utility/platform.hpp"

#if defined(ID_LINUX)

#include "idlib/file_system/access_mode.hpp"
#include "idlib/file_system/create_mode.hpp"

#include "idlib/file_system/header.in"

/// @brief A Linux file descriptor.
class file_descriptor_impl final
{
private:
    /// @brief The Linux file handle.
    int m_handle;

    /// @brief The access model.
	access_mode m_access_mode;

public:
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

    /// @brief Construct the file descriptor.
    /// @post The file descriptor is closed.
    file_descriptor_impl() noexcept;

    /// @brief Destruct the file descriptor.
    /// @post The file descriptor is closed.
    ~file_descriptor_impl() noexcept;

    // Delete copy constructor.
    file_descriptor_impl(const file_descriptor_impl&) = delete;

    // Delete copy assignment operator.
    file_descriptor_impl& operator=(const file_descriptor_impl&) = delete;

    /// @brief Get the size, in Bytes, of the file size.
    /// @return the size, in Bytes, of the file
    /// @pre The file is open.
    /// @throw id::file_system::read_write_error the file is not open or the environment fails
    size_t size() const;

    /// Get the internal handle.
    void *handle() { return &m_handle; }

}; // class file_descriptor_impl

#include "idlib/file_system/footer.in"

#endif

#undef IDLIB_PRIVATE
#pragma pop_macro("IDLIB_PRIVATE")