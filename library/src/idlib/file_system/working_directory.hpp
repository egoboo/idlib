// Copyright Michael Heilmann 2016, 2017.
//
// This file is part of Idlib.
//
// Idlib is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Idlib is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Idlib. If not, see <http://www.gnu.org/licenses/>.

/// @file idlib/file_system/working_directory.hpp
/// @brief Determine the working directory.
/// @author Michael Heilmann

#pragma once

#include "idlib/utility.hpp"

#include "idlib/file_system/header.in"

/// @brief Get the current working directory of this process.
/// @return the current working directory of this process
/// @throw std::runtime_error the current working directory can not be obtained
/// @throw std::bad_alloc an out of memory situation occurred
std::string get_working_directory();

#include "idlib/file_system/footer.in"
