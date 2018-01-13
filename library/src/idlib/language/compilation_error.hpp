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

/// @file idlib/language/compilation_error.hpp
/// @brief Definition of an exception related to compilation errors.
/// @author Michael Heilmann

#pragma once

#if !defined(IDLIB_PRIVATE) || IDLIB_PRIVATE != 1
#error(do not include directly, include `idlib/idlib.hpp` instead)
#endif

#include "idlib/utility/exception.hpp"
#include "idlib/language/location.hpp"

namespace id { namespace c {

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
    location m_location;
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
    compilation_error(const char *file, int line, compilation_error_kind kind, const location& location, const std::string& description) :
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
    const location& get_location() const
    {
        return m_location;
    }

    /// @brief Get the kind of the compilation error.
    /// @return the kind of the compilation error
    compilation_error_kind get_kind() const
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

} } // namespace id::c
