#pragma once

#include <string>

#include "idlib/file_system/header.in"

/// @brief Delete a regular file.
/// @param pathname the pathname of the regular file to delete
void delete_regular(const std::string& pathname);

#include "idlib/file_system/footer.in"
