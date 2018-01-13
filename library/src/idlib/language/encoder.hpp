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

namespace id { namespace c {

/// @brief Functor encoding a value TO its string representation.
/// @tparam V the source type
/// @tparam E for SFINAE
/// @remark
/// Specializations shall provide an operator() which takes
/// a value of type @a (V) as its first argument
/// and
/// a reference to a variable of type @a (std::string) as its second argument.
/// That operator may not raise an exception
/// and
/// shall returns @a true on success and @a false on failure.
/// If the function succeeds, the encoded value is assigned to the variable,
/// otherwise the variable is not assigned.
template <typename V, typename E = void>
struct encoder;
	
} } // namespace id::c
