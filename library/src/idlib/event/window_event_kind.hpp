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

/// @file idlib/event/window_event_kind.hpp
/// @brief Enumeration of the different kinds of window events.
/// @author Michael Heilmann

#pragma once

#include "idlib/event/internal/header.hpp"

/// @brief Enumeration of the different kinds of window events.
enum class window_event_kind
{
	/// @brief Kind of a window moved event.
	moved,
	
	/// @brief Kind of a window resized event.
	resized,
	
	/// @brief Kind of a window received keyboard input focus event.
	keyboard_input_focus_received,
	
	/// @brief Kind of a window lost keyboard input focus event.
	keyboard_input_focus_lost,

	/// @brief Kind of mouse pointer entered a window event.
	mouse_pointer_entered,

	/// @brief Kind of a mouse pointer left a window event.
	mouse_pointer_left,
	
	/// @brief Kind of a window was shown event.
	shown,
	
	/// @brief Kind of a window was hidden event.
	hidden,

}; // struct window_event_kind

#include "idlib/event/internal/footer.hpp"
