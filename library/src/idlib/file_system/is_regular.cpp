#include "idlib/file_system/is_regular.hpp"

#include "idlib/file_system/status.hpp"

#include "idlib/file_system/header.in"

bool is_regular(const std::string& pathname)
{ return file_type::regular == status(pathname).type(); }

#include "idlib/file_system/footer.in"
