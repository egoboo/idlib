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

/// @file idlib/utility/out_of_bounds_error.hpp
/// @brief Out of bounds error exception.
/// @author Michael Heilmann

#pragma once

#if !defined(IDLIB_PRIVATE) || IDLIB_PRIVATE != 1
#error(do not include directly, include `idlib/idlib.hpp` instead)
#endif

#include "idlib/utility/invalid_argument_error.hpp"

#include "idlib/utility/header.in"

/// @brief Exception indicating an argument out of bounds error.
class out_of_bounds_error : public invalid_argument_error
{
public:
    /// @brief Construct this exception.
    /// @param file the C++ source file (as obtained by the __FILE__ macro) associated with this exception
    /// @param line the line within the C++ source file (as obtained by the __LINE__ macro) associated with this exception
    /// @param name the name of the argument
    explicit out_of_bounds_error(const char *file, int line, const std::string& name) :
        invalid_argument_error(file, line, "argument `" + name + "` is out of bounds")
    {}

	friend void swap(out_of_bounds_error& a, out_of_bounds_error& b)
	{
		using std::swap;
		swap(static_cast<runtime_error&>(a), static_cast<runtime_error&>(b));
	}

    virtual std::string to_string() const override
    {
        std::ostringstream buffer;
		buffer << "out of bounds error:" << std::endl;
        buffer << "(raised in file " << file() << ", line " << line() << ")" << ":" << std::endl;
        buffer << message();
        return buffer.str();
    }

}; // class out_of_bounds_error

#include "idlib/utility/footer.in"
