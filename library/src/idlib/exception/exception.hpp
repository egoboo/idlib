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

/// @file idlib/exception/exception.hpp
/// @brief Root of the exception hierarchy.
/// @author Michael Heilmann

#pragma once

#if !defined(IDLIB_PRIVATE) || IDLIB_PRIVATE != 1
#error(do not include directly, include `idlib/exception.hpp` instead)
#endif

#include "idlib/platform.hpp"
#include <string>
#include <sstream>

namespace idlib {

inline std::string sanitize(const std::string& source)
{
    std::string target = source;
    //
    {
        std::string::size_type pos = 0; // Must initialize
        while ( ( pos = target.find ("\r\n",pos) ) != std::string::npos )
        {
            target.replace( pos, 2, "\n" );
        }
    }
    //
    {
        std::string::size_type pos = 0; // Must initialize
        while ( ( pos = target.find ("\n\r",pos) ) != std::string::npos )
        {
            target.replace ( pos, 2, "\n" );
        }
    }    
    return target;
}

/// @brief The base class of all id exceptions.
class exception
{
private:
    /// @brief The C++ source file (as obtained by the __FILE__ macro) associated with this exception.
    const char *m_file;

    /// @brief The line within the C++ source file (as obtained by the __LINE__ macro) associated with this exception.
    int m_line;

protected:
    virtual ~exception() = default;
    exception(const exception&) = default;
    exception& operator=(const exception&) = default;
    exception(exception&&) = default;
    exception& operator=(exception&&) = default;

protected:
    /// @brief Construct this exception.
    /// @param file the C++ source file (as obtained by the __FILE__ macro) associated with this exception
    /// @param line the line within the C++ source file (as obtained by the __LINE__ macro) associated with this exception
    /// @remark Intentionally protected.
    explicit exception(const char *file, int line) noexcept :
        m_file(file), m_line(line)
    {}

public:
    friend void swap(exception& a, exception& b) noexcept
    {
        using std::swap;
        swap(a.m_file, b.m_file);
        swap(a.m_line, b.m_line);
    }

    /// @brief Get the C++ source file associated with this exception.
    /// @return the C++ source file associated with this exception
    const char *file() const noexcept
    { return m_file; }

    /// @brief Get the line within the C++ source file associated with this exception.
    /// @return the line within the C++ source file associated with this exception
    int line() const noexcept
    { return m_line; }
    
    /// @brief Get a human-readable string describing this exception.
    /// @return a human-readable string describing this exception
    virtual std::string to_string() const
    {
        std::ostringstream buffer;
        buffer << "exception:" << std::endl;
        buffer << "(raised in file " << file() << ", line " << line() << ")";
        return buffer.str();
    }

}; // struct exception

} // namespace idlib
