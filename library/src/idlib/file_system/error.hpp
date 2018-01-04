// Copyright Michael Heilmann 2016, 2017, 2018.
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

/// @file idlib/file_system/error.hpp
/// @brief Definition of the base exception for any kind of file system exception.
/// @author Michael Heilmann

#pragma once

#if !defined(IDLIB_PRIVATE) || IDLIB_PRIVATE != 1
#error(do not include directly, include `idlib/idlib.hpp` instead)
#endif

#include "idlib/utility/runtime_error.hpp"
#include "idlib/utility/to_string.hpp"

#include "idlib/file_system/header.in"

/// @brief Base exception for any kind of file system exception.
class error : public id::runtime_error
{
public:
    /// @brief Construct this exception.
    /// @param file the C++ source file associated with this exception
    /// @param line the line within the C++ source file associated with this exception
    /// @param message the messae
    explicit error(const char *file, int line, const std::string& message) :
        id::runtime_error(file, line, message)
    {}

public:
    friend void swap(error& a, error& b)
    {
        using std::swap;
        swap(static_cast<id::runtime_error&>(a), static_cast<id::runtime_error&>(b));
    }

    virtual std::string to_string() const override
    {
        std::ostringstream buffer;
        buffer << "file system error:" << std::endl;
        buffer << "(raised in file " << file() << ", line " << line() << ")" << ":" << std::endl;
        buffer << message();
        return buffer.str();
    }

}; // class error

#include "idlib/file_system/footer.in"
