#pragma once

#include "idlib/utility.hpp"

#if defined(ID_WINDOWS)

#include "idlib/file_system/header.in"

void delete_regular_impl(const std::string& filename);

#include "idlib/file_system/footer.in"

#endif