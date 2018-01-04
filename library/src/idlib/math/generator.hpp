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

#pragma once

namespace id {

/// @ingroup math
/// @brief Generator functor. Specializations of this functor satisfiy the requirements of the <em>Generator</em> concept.
/// They define an operator() hat accepts a single parameter of type @a size_t and return a value of type @a R.
/// Furthermore a generator needs to be 
/// - <a href="http://en.cppreference.com/w/cpp/concept/DefaultConstructible">DefaultConstructible</a>,
/// - <a href="http://en.cppreference.com/w/cpp/concept/CopyAssignable">CopyAssignable</a>,
/// - <a href="http://en.cppreference.com/w/cpp/concept/Swappable">Swappable</a> and
/// - <a href="http://en.cppreference.com/w/cpp/concept/Destructible">Destructible</a>.
/// @see id::constant_generator
/// @see id::conditional_generator
struct generator
{};

} // namespace id
