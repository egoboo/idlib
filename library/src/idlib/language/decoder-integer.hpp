#pragma once

#pragma push_macro("IDLIB_PRIVATE")
#if !defined(IDLIB_PRIVATE)
#define IDLIB_PRIVATE 1
#endif

#include "idlib/language/decoder.hpp"
#include "idlib/language/classify.hpp"

#include "idlib/utility/out_of_bounds_error.hpp"
#include "idlib/utility/invalid_argument_error.hpp"

#undef IDLIB_PRIVATE
#pragma pop_macro("IDLIB_PRIVATE")

namespace id { namespace c {
	
/// @brief Specialization of id::c::decoder for decoding <c>integer</c> literals to <c>int</c> values.
template <>
struct decoder<int, void>
{
    bool operator()(const std::string& s, int& v) const;
}; // struct decoder

/// @brief Specialization of id::c::decoder for decoding <c>integer</c> literals to <c>long</c> values.
template <>
struct decoder<long, void>
{
    bool operator()(const std::string& s, long& v) const;
}; // struct decoder

/// @brief Specialization of id::c::decoder for decoding <c>integer</c> literals to <c>long long</c> values.
template <>
struct decoder<long long, void>
{
    bool operator()(const std::string& s, long long& v) const;
}; // struct decoder
	
/// @brief Specialization of id::c::decoder for decoding <c>integer</c> literals to <c>signed char</c> values.
template <>
struct decoder<signed char, void>
{
    bool operator()(const std::string& s, signed char& v) const;
}; // struct decoder

/// @brief Specialization of id::c::decoder for decoding <c>integer</c> literals to <c>short</c> values.
template <>
struct decoder<short, void>
{
    bool operator()(const std::string& s, short& v) const;
}; // struct decoder

} } // namespace id::c
