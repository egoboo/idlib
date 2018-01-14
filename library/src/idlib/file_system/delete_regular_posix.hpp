#pragma once

#include "idlib/platform.hpp"

#if defined(ID_POSIX)

#include <string>

#include "idlib/file_system/header.in"

void delete_regular_impl(const std::string& pathname);

#include "idlib/file_system/footer.in"

#endif
