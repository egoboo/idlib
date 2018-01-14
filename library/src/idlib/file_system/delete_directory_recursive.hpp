#pragma once

#include <string>

#include "idlib/file_system/header.in"

/// @brief Delete a directory file and all the files contained in that directory file.
/// @param pathname the pathname of the directory file to delete
void delete_directory_recursive(const std::string& pathname);

#include "idlib/file_system/footer.in"