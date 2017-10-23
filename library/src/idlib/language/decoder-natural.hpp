#pragma once

#pragma push_macro("IDLIB_PRIVATE")
#if !defined(IDLIB_PRIVATE)
#define IDLIB_PRIVATE 1
#endif

#include <string>
#include "idlib/language/decoder.hpp"

//#include "idlib/language/classify.hpp"
//#include "idlib/utility/invalid_argument_error.hpp"

#undef IDLIB_PRIVATE
#pragma pop_macro("IDLIB_PRIVATE")

namespace id { namespace c {
	
/// @brief Specialization of id::c::decoder for decoding <c>natural</c> literals to <c>unsigned long</c> values.
template <>
struct decoder<unsigned long, void>
{
    bool operator()(const std::string& s, unsigned long& v) const;
}; // struct decoder
	
/// @brief Specialization of id::c::decoder for decoding <c>natural</c> literals to <c>unsigned long long</c> values.
template <>
struct decoder<unsigned long long, void>
{
    bool operator()(const std::string& s, unsigned long long& v) const;
}; // struct decoder
	
	
/// @brief Specialization of id::decoder for decoding <c>natural</c> literals to <c>unsigned char</c> values.
template <>
struct decoder<unsigned char, void>
{
    bool operator()(const std::string& s, unsigned char& v) const;
}; // struct decoder
	
/// @brief Specialization of id::decoder for decoding <c>natural</c> literals to <c>unsigned short</c> values.
template <>
struct decoder<unsigned short, void>
{
    bool operator()(const std::string& s, unsigned short& v) const;
}; // struct decoder
	
/// @brief Specialization of id::decoder for decoding <c>natural</c> literals to <c>unsigned int</c> values.
template <>
struct decoder<unsigned int, void>
{
    bool operator()(const std::string& s, unsigned int& v) const;
}; // struct decoder

} } // namespace id::c
