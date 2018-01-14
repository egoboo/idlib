#pragma once

#include "idlib/utility.hpp"

#if defined(ID_WINDOWS)

#include "idlib/file_system/header.in"

bool delete_directory_impl(const std::string& pathname);

#include "idlib/file_system/footer.in"

#endif
