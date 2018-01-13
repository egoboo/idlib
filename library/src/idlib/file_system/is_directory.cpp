#include "idlib/file_system/is_directory.hpp"

#include "idlib/file_system/status.hpp"

#include "idlib/file_system/header.in"

bool is_directory(const std::string& pathname)
{ return file_type::directory == status(pathname).type(); }

#include "idlib/file_system/footer.in"
