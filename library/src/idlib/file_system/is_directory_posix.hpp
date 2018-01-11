#pragma once

#include "idlib/utility.hpp"

#if defined(ID_POSIX)

#include "idlib/file_system/header.in"

bool is_directory_impl(const std::string& filename);

#include "idlib/file_system/footer.in"

#endif
