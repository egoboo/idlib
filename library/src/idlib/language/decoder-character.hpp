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

namespace id { namespace c {

/// @brief Specialization of id::c::decoder for <c>character</c> literals.
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

} } // namespace id::c
