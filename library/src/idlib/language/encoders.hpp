#pragma once

#include "idlib/language/encoder.hpp"
#include <string>

namespace id { namespace c {

/// @brief Specialization of id::decoder for encoding <c>bool</c> values to <c>boolean</c> literals.
template <>
struct encoder<bool, void>
{
    bool operator()(const bool& v, std::string& s)
    {
        s = v ? "true" : "false";
        return true;
    }
}; // struct encoder

/// @brief Specialization of id::encoder for encoding <c>uint8_t</c> values to <c>natural</c> literals.
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

/// @brief Specialization of id::encoder for encoding <c>int8_t</c> values to <c>integer</c> literals.
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

/// @brief Specialization of id::encoder for encoding <c>std::string</c> values to <c>string</c> literals.
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

} } // namespace id::c
