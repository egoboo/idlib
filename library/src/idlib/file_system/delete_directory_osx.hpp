#pragma once

#include "idlib/utility.hpp"

#if defined(ID_OSX)

#include "idlib/file_system/header.in"

bool delete_directory_impl(const std::string& filename);

#include "idlib/file_system/footer.in"

#endif
