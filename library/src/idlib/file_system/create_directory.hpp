#pragma once

#include "idlib/utility.hpp"

#include "idlib/file_system/header.in"

/// @brief Create a directory.
/// @param filename the filename
/// @return @a true if the directory was created, @a false otherwise
/// @remark All intermediate directories must exist; this function will only create the final directory in the path.
bool create_directory(const std::string& filename);

#include "idlib/file_system/footer.in"
