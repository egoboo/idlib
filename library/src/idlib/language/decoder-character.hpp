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

#pragma push_macro("IDLIB_PRIVATE")
#if !defined(IDLIB_PRIVATE)
#define IDLIB_PRIVATE 1
#endif

#include "idlib/language/decoder.hpp"
#include "idlib/language/classify.hpp"

#include "idlib/utility/invalid_argument_error.hpp"

#undef IDLIB_PRIVATE
#pragma pop_macro("IDLIB_PRIVATE")

namespace idlib { namespace c {

/// @brief Specialization of idlib::c::decoder for <c>character</c> literals.
/// @tparam V the type of the values to decode the <c>character</c> literals to
template <typename V>
struct decoder<V, std::enable_if_t<internal::is_character<V>::value>>
{
	bool operator()(const std::string& s, V& v) const
	{
		static_assert(internal::is_character<V>::value,
			          "V must be a character type");
		try
		{
			if (s.length() != 1)
			{
				throw invalid_argument_error(__FILE__, __LINE__, "not a valid character literal");
			}
			v = s[0];
		}
		catch (const invalid_argument_error&)
		{
			return false;
		}
		return true;
	}
}; // struct decoder

} } // namespace idlib::c
