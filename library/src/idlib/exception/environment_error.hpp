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

/// @file idlib/exception/environment_error.hpp
/// @brief Environment error exception.
/// @author Michael Heilmann

#pragma once

#if !defined(IDLIB_PRIVATE) || IDLIB_PRIVATE != 1
#error(do not include directly, include `idlib/exception.hpp` instead)
#endif

#include "idlib/exception/runtime_error.hpp"

namespace idlib {

/// @brief A generic exception to propagate errors of the environment (e.g. SDL, Win32, OSX, Linux, ...)
/// to the application level. Use this exception as well if the environment does not follow its
/// specification (e.g. documented behavior vs. actual behavior).
class environment_error : public runtime_error
{
private:
    /// @brief The component associated with this environment error.
    std::string m_component;

public:
    /// @brief Construct this environment error.
    /// @param file the C++ source file (as obtained by the __FILE__ macro) associated with this exception
    /// @param line the line within the C++ source file (as obtained by the __LINE__ macro) associated with this exception
    /// @param component the component the error is related to e.g. "pthreads", "SDL video", ...
    /// @param message a message describing the error
    /// @remark Intentionally protected.
    explicit environment_error(const char *file, int line, const std::string& component, const std::string& message) :
        runtime_error(file, line, message), m_component(component)
    {}

public:
    /// @brief Get the component associated with this environment error.
    /// @return the component associated with this environment error
    const std::string& component() const
    {
        return m_component;
    }

    friend void swap(environment_error& a, environment_error& b)
    {
        using std::swap;
        swap(static_cast<runtime_error&>(a), static_cast<runtime_error&>(b));
        swap(a.m_component, b.m_component);        
    }

    virtual std::string to_string() const override
    {
        std::ostringstream buffer;
        buffer << "environment error: " << component() << ":" << std::endl;
        buffer << "(raised in file " << file() << ", line " << line() << ")" << ":" << std::endl;
        buffer << message();
        return buffer.str();
    }

}; // class environment_error

} // namespace idlib
