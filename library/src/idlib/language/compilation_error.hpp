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

/// @file idlib/language/compilation_error.hpp
/// @brief Definition of an exception related to compilation errors.
/// @author Michael Heilmann

#pragma once

#if !defined(IDLIB_PRIVATE) || IDLIB_PRIVATE != 1
#error(do not include directly, include `idlib/idlib.hpp` instead)
#endif

#include "idlib/utility/exception.hpp"
#include "idlib/language/location.hpp"

namespace id {

/// @brief An enumeration of the different kinds of compilation errors.
enum class compilation_error_kind
{
    /// @brief A compilation error that occurred during semantic analysis.
    semantical,
    /// @brief A compilation error that occurred during syntactic analysis.
    syntactical,
    /// @brief A compilation error that occurred during lexical analysis.
    lexical,
};

/// @brief A compilation error exception.
class compilation_error : public exception
{
private:
    /// @brief The location associated with the compilation error.
    id::location m_location;
    /// @brief A description of the compilation error.
    std::string m_description;
    /// @brief The kind of the compilation error.
    compilation_error_kind m_kind;

public:
    /// @brief Construct this exception.
    /// @param file the C++ source file (as obtained by the __FILE__ macro) associated with this exception
    /// @param line the line within the C++ source file (as obtained by the __LINE__ macro) associated with this exception
    /// @param kind the kind of the compilation error
    /// @param location the location associated with the error
    /// @param description a description of the error
    compilation_error(const char *file, int line, compilation_error_kind kind, const id::location& location, const std::string& description) :
        exception(file, line), m_location(location), m_description(description), m_kind(kind)
    {}

    /// @brief Copy construct this exception with the values of another exception.
    /// @param other the other exception
    compilation_error(const compilation_error& other) :
        exception(other), m_location(other.m_location), m_description(other.m_description), m_kind(other.m_kind)
    {}

    /// @brief Assign this exception with the values of another exception.
    /// @param other the other exception
    /// @return this exception
    compilation_error& operator=(const compilation_error& other)
    {
        exception::operator=(other);
        m_kind = other.m_kind;
        m_location = other.m_location;
        m_description = other.m_description;
        return *this;
    }

public:
    /// @brief Get the location associated with the compilation error.
    /// @return the location associated with the compilation error
    const id::location& location() const
    {
        return m_location;
    }

    /// @brief Get the kind of the compilation error.
    /// @return the kind of the compilation error
    compilation_error_kind kind() const
    {
        return m_kind;
    }

    virtual std::string to_string() const override
    {
        std::ostringstream o;
        o << m_location.file_name() << ": " << m_location.line_number()
          << " (raised in file " << file() << ", line " << line() << ")";
        o << ": ";
        switch (m_kind)
        {
            case compilation_error_kind::lexical:
                o << "lexical error";
                break;
            case compilation_error_kind::syntactical:
                o << "syntactical error";
                break;
            case compilation_error_kind::semantical:
                o << "semantical error";
                break;
        };
        o << ": ";
        o << m_description;
        return o.str();
    }

};

} // namespace id
