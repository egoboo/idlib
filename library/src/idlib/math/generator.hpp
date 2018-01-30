///////////////////////////////////////////////////////////////////////////////////////////////////
//
// Idlib: A C++ utility library
// Copyright (C) 2017-2018 Michael Heilmann
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

namespace idlib {

/// @ingroup math
/// @brief Generator functor. Specializations of this functor satisfiy the requirements of the <em>Generator</em> concept.
/// They define an operator() hat accepts a single parameter of type @a size_t and return a value of type @a R.
/// Furthermore a generator needs to be 
/// - <a href="http://en.cppreference.com/w/cpp/concept/DefaultConstructible">DefaultConstructible</a>,
/// - <a href="http://en.cppreference.com/w/cpp/concept/CopyAssignable">CopyAssignable</a>,
/// - <a href="http://en.cppreference.com/w/cpp/concept/Swappable">Swappable</a> and
/// - <a href="http://en.cppreference.com/w/cpp/concept/Destructible">Destructible</a>.
/// @see idlib::constant_generator
/// @see idlib::conditional_generator
struct generator
{};

} // namespace idlib
