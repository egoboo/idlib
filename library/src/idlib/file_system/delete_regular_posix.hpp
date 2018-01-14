#pragma once

#include "idlib/utility.hpp"

#if defined(ID_POSIX)

#include "idlib/file_system/header.in"

void delete_regular_impl(const std::string& pathname);

#include "idlib/file_system/footer.in"

#endif
