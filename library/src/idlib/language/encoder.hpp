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
