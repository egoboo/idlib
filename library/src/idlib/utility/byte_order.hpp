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

/// @file idlib/utility/byte_order.hpp
/// @brief Support for detection of the "Host" Byte order and Byte order conversions.
/// @author Michael Heilmann

#pragma once

#include "idlib/utility/is_any_of.hpp"
#include "idlib/utility/swap_bytes.hpp"

#include "idlib/utility/header.in"
	
/// @brief An enumeration of Byte orders.
enum class byte_order
{
    /// @brief Little endian Byte order.
    little_endian,
    /// @brief Big endian Byte order.
    big_endian,
}; // enum class byte_order

/// @brief A constexpr function which returns the Byte order of the environment.
/// @return the Byte order of the environment
#if defined(__GNUC__)
	#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
		constexpr byte_order get_byte_order()
		{ return byte_order::little_endian; }
	#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
		constexpr byte_order get_byte_order()
		{ return byte_order::big_endian; }
	#else
		#error("unsupported Byte order")
	#endif
#elif defined(_MSC_VER)
	constexpr byte_order get_byte_order()
	{ return byte_order::little_endian; }
#else
    #error("unable to determine Byte order")
#endif

/// @brief Functor to convert a value from one Byte order to another Byte order.
/// This functor defines an @code{operator()}. Its arguments are depicted in the table below.
/// <table>
/// <tr>
/// <td>@a v</td>
/// <td>@a V</td>
/// <td>the source value with Byte order is @a source</td>
/// </tr>
/// <tr>
/// <td>@a t</td>
/// <td>@a id::byte_order</td>
/// <td>the target Byte order</td>
/// </tr>
/// <tr>
/// <td>@a s</td>
/// <td>@a id::byte_order</td>
/// <td>the source Byte order</td>
/// </tr>
/// </table>
/// The operator returns a value of type @a V that is the value @a v with its Byte order converted to @a t.
/// @tparam V the type of the value
/// @tparam E for SFINAE
/// @remark Specializations for
/// @a int8_t, @a uint8_t, @a int16_t, @a uint16_t,
/// @a int32_t, @a uint32_t, @a int64_t, @a uint64_t,
/// @a float, and @a double are provided.
/// @remark Feel free to provide your own implementation.
template <typename V, typename E = void>
struct byte_order_conversion_functor;

// Specialization for Byte order conversions of @a int8_t and @a uint8_t values.
template <typename V>
struct byte_order_conversion_functor<V, std::enable_if_t<is_any_of_v<V, int8_t, uint8_t>>>
{
    V operator()(const V& v, byte_order t, byte_order s) const
    {
        return v;
    }
}; // struct byte_order_conversion_functor

// Specialization for Byte order conversions of
// @a int16_t, @a uint16_t, @a int32_t, @a uint32_t, @a int64_t, @a uint64_t, @a float, and @a double values.
template <typename V>
struct byte_order_conversion_functor<V, std::enable_if_t<is_any_of_v<V,
                                                                     int16_t, uint16_t,
                                                                     int32_t, uint32_t,
                                                                     int64_t, uint64_t,
                                                                     float, double>>>
{
    V operator()(const V& v, byte_order t, byte_order s) const
    {
        if (t == s)
        {
            return v;
        }
        else
        {
            return swap_bytes(v);
        }
    }
}; // struct byte_order_conversion_functor

/// @brief Convert a value from one Byte order to another Byte order.
/// @param v the value of type @a V in the source Byte order @a s
/// @param t the target Byte order
/// @param s the source Byte order
/// @return a value of type @a V that is the value @a v with its Byte order converted to @a t
/// @tparam V the value type
/// @remark Implementations for
/// @a int8_t, @a uint8_t, @a int16_t, @a uint16_t,
/// @a int32_t, @a uint32_t, @a int64_t, @a uint64_t,
/// @a float, and @a double are provided.
template <typename V>
V convert_byte_order(const V& v, byte_order t, byte_order s)
{
    return byte_order_conversion_functor<V>()(v, t, s);
}

#include "idlib/utility/footer.in"
