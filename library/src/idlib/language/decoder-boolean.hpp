#pragma once

#pragma push_macro("IDLIB_PRIVATE")
#define IDLIB_PRIVATE 1

#include "idlib/language/decoder.hpp"
#include "idlib/language/classify.hpp"

#include "idlib/utility/invalid_argument_error.hpp"

#undef IDLIB_PRIVATE
#pragma pop_macro("IDLIB_PRIVATE")

namespace id { namespace c {

/// @brief Specialization of id::c::decoder for decoding <c>boolean</c> literals to @a bool values.
/// @tparam V the type of the values to decode the <c>boolean</c> literals to
template <>
struct decoder<bool, void>
{
	bool operator()(const std::string& s, bool& v) const
	{
		if (s == "true")
		{
			v = true;
			return true;
		}
		else if (s == "false")
		{
			v = false;
			return true;
		}
		else
		{
			throw invalid_argument_error(__FILE__, __LINE__, "not a valid boolean literal");
		}
	}
}; // struct decoder

} } // namespace id::c
