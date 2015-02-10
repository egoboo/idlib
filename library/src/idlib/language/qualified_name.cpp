// Copyright Michael Heilmann 2016, 2017.
//
// This file is part of Idlib.
//
// Idlib is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Idlib is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Idlib. If not, see <http://www.gnu.org/licenses/>.

/// @file idlib/language/qualified_name.cpp
/// @brief A qualified names i.e. a name of the form @code{<name>('.'<name>)*}.
/// @author Michael Heilmann

#define IDLIB_PRIVATE 1
#include "idlib/language/qualified_name.hpp"

#include "idlib/language/location.hpp"
#include "idlib/parsing_expressions/predefined.hpp"
#include "idlib/language/compilation_error.hpp"
#undef IDLIB_PRIVATE

namespace id {

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
    throw id::compilation_error(file, line, compilation_error_kind::lexical,
                                location, message.str());
}

qualified_name::qualified_name(const std::string& string) :
    m_string(string)
{
    static const auto p = parsing_expressions::qualified_name<char>();
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

} // namespace id

namespace std {

size_t hash<id::qualified_name>::operator()(const id::qualified_name& x) const
{
    return hash<string>()(x.string());
}

bool equal_to<id::qualified_name>::operator()(const id::qualified_name& x, const id::qualified_name& y) const
{
    return equal_to<string>()(x.string(), y.string());
}

bool less<id::qualified_name>::operator()(const id::qualified_name& x, const id::qualified_name& y) const
{
    // Sort the qualifid names lexicographically.
    return less<string>()(x.string(), y.string());
}

} // namespace std
