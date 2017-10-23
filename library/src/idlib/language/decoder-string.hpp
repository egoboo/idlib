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

/// @brief Specialization of id::c::decoder for decoding <c>string</c> literals to @a std::string values.
template <>
struct decoder<std::string, void>
{
	bool operator()(const std::string& s, std::string& v) const
	{
		v = s;
		return true;
	}
}; // struct decoder

} } // namespace id::c
