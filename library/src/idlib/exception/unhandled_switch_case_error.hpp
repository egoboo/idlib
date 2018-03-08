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

/// @file idlib/exception/unhandled_switch_case_error.hpp
/// @brief Definition of an exception indicating a missing switch case handle for a specific label
/// @author Johan Jansen, Michael Heilmann

#pragma once

#if !defined(IDLIB_PRIVATE) || IDLIB_PRIVATE != 1
#error(do not include directly, include `idlib/exception.hpp` instead)
#endif

#include "idlib/exception/runtime_error.hpp"

namespace idlib {

/// @brief Exception indicating a missing switch case handle for a specific label
class unhandled_switch_case_error : public runtime_error
{
public:
    /// @brief Construct this exception.
    /// @param file the C++ source file (as obtained by the __FILE__ macro) associated with this exception
    /// @param line the line within the C++ source file (as obtained by the __LINE__ macro) associated with this exception
    /// @param message optional exception string message
    explicit unhandled_switch_case_error(const char *file, int line, const std::string& message = "unhandled switch case") :
        runtime_error(file, line, message)
    {}

    friend void swap(unhandled_switch_case_error& a, unhandled_switch_case_error& b) noexcept
    {
        using std::swap;
        swap(static_cast<runtime_error&>(a), static_cast<runtime_error&>(b));
    }

    virtual std::string to_string() const override
    {
        std::ostringstream buffer;
        buffer << "lock failed error:" << std::endl;
        buffer << "(raised in file " << file() << ", line " << line() << ")" << ":" << std::endl;
        buffer << message();
        return buffer.str();
    }

}; // class unhandled_switch_case_error

} // namespace idlib
