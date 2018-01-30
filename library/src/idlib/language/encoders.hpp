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

#include "idlib/language/encoder.hpp"
#include <string>

namespace idlib { namespace c {

/// @brief Specialization of idlib::decoder for encoding <c>bool</c> values to <c>boolean</c> literals.
template <>
struct encoder<bool, void>
{
    bool operator()(const bool& v, std::string& s)
    {
        s = v ? "true" : "false";
        return true;
    }
}; // struct encoder

/// @brief Specialization of idlib::encoder for encoding <c>uint8_t</c> values to <c>natural</c> literals.
template <>
struct encoder<uint8_t, void>
{
    bool operator()(const uint8_t& v, std::string& s)
    {
        try
        {
            s = std::to_string((unsigned int)v);
        }
        catch (...)
        {
            return false;
        }
        return true;
    }
}; // struct encoder

/// @brief Specialization of idlib::encoder for encoding <c>int8_t</c> values to <c>integer</c> literals.
template <>
struct encoder<int8_t, void>
{
    bool operator()(const int8_t& v, std::string& s)
    {
        try
        {
            s = std::to_string((signed int)v);
        }
        catch (...)
        {
            return false;
        }
        return true;
    }
}; // struct encoder

/// @brief Specialization of idlib::encoder for encoding <c>std::string</c> values to <c>string</c> literals.
/// @todo By no means this is sufficient. Control characters need to be escaped etc. etc.
template <>
struct encoder<std::string, void>
{
    bool operator()(const std::string& v, std::string& s)
    {
        s = v;
        return true;
    }
}; // struct encoder

/// @brief Specialization for unsigned integral types without the @a bool, @a int8_t and @a uint8_t types.
/// @todo Should be mor terse and more efficient.
template <typename V>
struct encoder<V, std::enable_if_t<std::is_integral<V>::value && !std::is_same<V, int8_t>::value && !std::is_same<V, uint8_t>::value && !std::is_same<V, bool>::value && !std::is_signed<V>::value>>
{

    bool operator()(const V& v, std::string& s)
    {
        try
        {
            s = std::to_string(v);
        }
        catch (...)
        {
            return false;
        }
        return true;
    }
};

/// @brief Specialization for signed integral types without the @a bool type.
/// @todo Should be more terse and more efficient.
template <typename V>
struct encoder<V, std::enable_if_t<std::is_integral<V>::value && !std::is_same<V, bool>::value && std::is_signed<V>::value>>
{
    bool operator()(const V& v, std::string& s)
    {
        try
        {
            s = std::to_string(v);
        }
        catch (...)
        {
            return false;
        }
        return true;
    }
};

/// @brief Specialization for @s single, @a double, and @a quadruple.
/// @todo Should be mor terse and more efficient.
template <typename V>
struct encoder<V, std::enable_if_t<std::is_floating_point<V>::value>>
{
    bool operator()(const V& v, std::string& s)
    {
        try
        {
            s = std::to_string(v);
        }
        catch (...)
        {
            return false;
        }
        return true;
    }
};

} } // namespace idlib::c
