#pragma once

#include <string>

#include "idlib/file_system/header.in"

/// @brief Delete an empty directory file.
/// @param pathname the pathname of the directory file to delete
/// @return @a true if the directory file was deleted, @a false otherwise
/// @remark This function will only delete the final directory file in the path.
bool delete_directory(const std::string& pathname);

#include "idlib/file_system/footer.in"
