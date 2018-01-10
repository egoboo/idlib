#pragma once

#include "idlib/utility.hpp"

#include "idlib/file_system/header.in"

/// @brief Delete an empty directory file.
/// @param filename the filename of the directory file
/// @return @a true if the directory file was deleted, @a false otherwise
/// @remark This function will only delete the final directory file in the path.
bool delete_directory(const std::string& filename);

#include "idlib/file_system/footer.in"
