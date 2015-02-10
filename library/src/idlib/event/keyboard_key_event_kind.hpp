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

/// @file idlib/event/keyboard_key_event_kind.hpp
/// @brief Enumeration of the different kinds of keyboard key events.
/// @author Michael Heilmann

#pragma once

#include "idlib/event/internal/header.hpp"

/// @brief Enumeration of the different kinds of keyboard key events.
enum class keyboard_key_event_kind
{
    /// @brief Kind of a keyboard key pressed event.
    pressed,

    /// @brief Kind of a keyboard key released event.
    released,

    /// @brief Kind of a keyboard key typed event.
    typed,

}; // enum class keyboard_key_event_kind

#include "idlib/event/internal/footer.hpp"
