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

/// @file idlib/hll/qualified_name.cpp
/// @brief A qualified names i.e. a name of the form @code{<name>('.'<name>)*}.
/// @author Michael Heilmann

#pragma push_macro("IDLIB_PRIVATE")
#undef IDLIB_PRIVATE
#define IDLIB_PRIVATE (1)

#include "idlib/hll/qualified_name.hpp"
#include "idlib/hll/location.hpp"
#include "idlib/hll/compilation_error.hpp"

#undef IDLIB_PRIVATE
#pragma pop_macro("IDLIB_PRIVATE")

#include "idlib/parsing_expression.hpp"

namespace idlib::hll {

/// @brief Raise an exception indicating that a string can not be parsed into qualified name.
/// @param file, line the C/C++ source location associated with the exception
/// @param location the source location w.r.t. the string
/// @param string the offending string
/// @throw LexicalError always raised with the specified C/C++ source location and a descriptive error message
static void no_qualified_name(const char *file, int line, const location& location, const std::string& string);

static void no_qualified_name(const char *file, int line, const location& location, const std::string& string)
{
    std::ostringstream message;
    message << file << ":" << line << ": ";
    message << "argument string `" << string << "` does not not represent a valid qualified name";
    throw compilation_error(file, line, compilation_error_kind::lexical,
                            location, message.str());
}

qualified_name::qualified_name(const std::string& string) :
    m_string(string)
{
    static const auto p = parsing_expression::qualified_name<char>();
    auto r = p(string.cbegin(), string.cend());
    if (!r || (r.range().begin() != string.cbegin() || r.range().end() != string.cend())) // The check r.iterator() != string.cend() is actually not required.
    {
        no_qualified_name(__FILE__, __LINE__, location("string `" + string + "`", 1), string);
    }
}

qualified_name::qualified_name(const qualified_name& other) :
    m_string(other.m_string)
{}

qualified_name::~qualified_name()
{}

qualified_name& qualified_name::operator=(const qualified_name& other)
{
    m_string = other.m_string;
    return *this;
}

const std::string& qualified_name::string() const
{
    return m_string;
}

bool qualified_name::equal_to(const qualified_name& other) const
{
    return m_string == other.m_string;
}

} // namespace idlib::hll

namespace std {

size_t hash<idlib::hll::qualified_name>::operator()(const idlib::hll::qualified_name& x) const
{
    return hash<string>()(x.string());
}

bool equal_to<idlib::hll::qualified_name>::operator()(const idlib::hll::qualified_name& x, const idlib::hll::qualified_name& y) const
{
    return equal_to<string>()(x.string(), y.string());
}

bool less<idlib::hll::qualified_name>::operator()(const idlib::hll::qualified_name& x, const idlib::hll::qualified_name& y) const
{
    // Sort the qualifid names lexicographically.
    return less<string>()(x.string(), y.string());
}

} // namespace std
