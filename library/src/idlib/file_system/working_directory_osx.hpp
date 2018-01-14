#pragma once

#include "idlib/platform.hpp"

#if defined(ID_OSX)

#include <string>

#include "idlib/file_system/header.in"

std::string get_working_directory_impl();

#include "idlib/file_system/footer.in"

#endif