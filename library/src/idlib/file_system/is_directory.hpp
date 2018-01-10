#pragma once

#include "idlib/utility.hpp"

#include "idlib/file_system/header.in"

/// @brief Get if a file is is an existing directory file.
/// @param filename the filename
/// @return @a true if a file is an existing directory file, @a false otherwise
bool is_directory(const std::string& filename);

#include "idlib/file_system/footer.in"
