#pragma once

#include "idlib/platform.hpp"

#if defined (ID_WINDOWS)

#include <string>
#include "idlib/file_system/file_status.hpp"

#include "idlib/file_system/header.in"

file_status status_impl(const std::string& pathname);

#include "idlib/file_system/footer.in"

#endif
