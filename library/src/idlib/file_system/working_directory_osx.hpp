#pragma once

#include "idlib/utility.hpp"

#if defined(ID_OSX)

#include "idlib/file_system/header.in"

std::string get_working_directory_impl();

#include "idlib/file_system/footer.in"

#endif