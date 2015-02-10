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

/// @file idlib/file_system/create_mode.hpp
/// @brief Create mode for files.
/// @author Michael Heilmann

#pragma once

#include "idlib/utility/platform.hpp"
#include "idlib/utility/bitmask_type.hpp"

#include "idlib/file_system/header.in"

/// @brief Enum class of file create modes.
enum class create_mode
{
    open_existing = 0, ///< Open the file if it exists.
    create_not_existing = (1 << 1), ///< Create the file if it does not exist.
};

#include "idlib/file_system/footer.in"
