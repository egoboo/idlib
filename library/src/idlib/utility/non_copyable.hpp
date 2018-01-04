// Copyright Michael Heilmann 2016, 2017, 2018.
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

/// @file idlib/utility/non_copyable.hpp
/// @brief Make classes non-copyable.
/// @author Michael Heilmann

#pragma once

#if !defined(IDLIB_PRIVATE) || IDLIB_PRIVATE != 1
#error(do not include directly, include `idlib/idlib.hpp` instead)
#endif

#include "idlib/utility/header.in"

/// @brief Non-copyable mixing.
/// @detail Inherit from this class to make the inheriting descendant classes non-copyable.
/// The descendants are non-copyable because the copy constructors and assignment operators are deleted.
/// @detail Example usage
/// @code
/// class foo : public bar, private non_copyable
/// { ... }
/// @endcode
class non_copyable
{
protected:
	non_copyable() = default;
	~non_copyable() = default;
public:
    non_copyable(const non_copyable&) = delete;
    non_copyable& operator=(const non_copyable&) = delete;
}; // class non_copyable

#include "idlib/utility/footer.in"
