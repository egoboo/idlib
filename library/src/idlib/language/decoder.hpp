#pragma once

namespace id { namespace c {
	
/// @brief Functor decoding value FROM its string representation.
/// @tparam V the target type to convert the string representation into
/// @tparam E for SFINAE
/// @remark
/// Specializations shall provide a constant operator() which takes
/// a value of type @a (std::string) as its first argument
/// and
/// a reference to a variable of type @a (V) as its second argument.
/// That operator may not raise an exception
/// and
/// shall returns @a true on success and @a false on failure.
/// If the function succeeds, the decoded value is assigned to the variable,
/// otherwise the variable is not assigned.
template <typename V, typename E = void>
struct decoder;

} } // namespace id::c
