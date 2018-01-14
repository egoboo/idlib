#pragma once

#include "idlib/platform.hpp"

#if defined(ID_WINDOWS)

#include <string>

#include "idlib/file_system/header.in"

bool create_directory_impl(const std::string& filename);

#include "idlib/file_system/footer.in"

#endif
