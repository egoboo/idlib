#pragma once

#pragma push_macro("IDLIB_PRIVATE")
#if !defined(IDLIB_PRIVATE)
#define IDLIB_PRIVATE 1
#endif

#include "idlib/utility/platform.hpp"

#undef IDLIB_PRIVATE
#pragma pop_macro("IDLIB_PRIVATE")

namespace id { namespace c { namespace internal {
	
/// The configuration framework knows five categories of types:
/// - integer types,
/// - natural types,
/// - boolean types,
/// - real types,
/// - character types, and
/// - string types.
/// @remark
/// - @a (char), @a (unsignd char), and @a (signed char) are distinct types in C++.
/// @a (signed char) is considered as an integer type and @a (unsigned char) is considered as a natural type by the framework.
/// - @a (uint8_t) is not necessarily the same type as @a (unsigned char) and @a (int8_t) is not necessarily the same type as @a (signed char) in C++.
/// - @a (single), @a (double), and @a (quadruple) are considered as real types by the framework.
/// - @a (bool) is considered as a boolan type.
/// - @a (char) is considered as a character type.
/// - @a (std::string) is considered as a string type.

/// @tparam T the type
/// @tparam E for SFINAE
template <typename T, typename E = void>
struct is_integer;

/// @tparam T the type
/// @tparam E for SFINAE
template <typename T, typename E = void>
struct is_natural;

/// @tparam T the type
/// @tparam E for SFINAE
template <typename T, typename E = void>
struct is_real;

/// @tparam T the type
/// @tparam E for SFINAE
template <typename T, typename E = void>
struct is_boolean;

/// @tparam T the type
/// @tparam E for SFINAE
template <typename T, typename E = void>
struct is_character;

/// @tparam T the type
/// @tparam E for SINFAE
template <typename T, typename E = void>
struct is_string;

/// @tparam T the type
template <typename T>
struct is_integer<T, std::enable_if_t<std::is_integral<T>::value &&
                                      std::is_signed<T>::value &&
                                      !std::is_same<T, bool>::value &&
                                      !std::is_same<T, char>::value>>
{
	static constexpr bool value = true;
}; // struct is_integer

/// @tparam T the type
template <typename T>
struct is_natural<T, std::enable_if_t<std::is_integral<T>::value &&
                                      std::is_unsigned<T>::value &&
                                      !std::is_same<T, bool>::value &&
                                      !std::is_same<T, char>::value>>
{
    static constexpr bool value = true;
}; // struct is_natural

/// @tparam T the type
template <typename T>
struct is_real<T, std::enable_if_t<std::is_floating_point<T>::value>>
{
    static constexpr bool value = true;
}; // struct is_real

/// @tparam T the type
template <typename T>
struct is_boolean<T, std::enable_if_t<std::is_same<T, bool>::value>>
{
    static constexpr bool value = true;
}; // struct is_boolean

/// @tparam T the type
template <typename T>
struct is_character<T, std::enable_if_t<std::is_same<T, char>::value>>
{
    static constexpr bool value = true;
}; // struct is_character

template <typename T>
struct is_string <T, std::enable_if_t<std::is_same<T, std::string>::value>>
{
    static constexpr bool value = true;
}; // struct is_string

} } } // namespace id::c
