#include "idlib/file_system/exists.hpp"

#include "idlib/file_system/status.hpp"

#include "idlib/file_system/header.in"

bool exists(const std::string& pathname)
{ auto s = status(pathname); return file_type::none != s.type() && file_type::not_found != s.type(); }

#include "idlib/file_system/footer.in"
