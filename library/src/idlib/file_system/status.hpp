#pragma once

#include "idlib/file_system/file_status.hpp"
#include <string>

#include "idlib/file_system/header.in"

file_status status(const std::string& pathname);

#include "idlib/file_system/footer.in"
