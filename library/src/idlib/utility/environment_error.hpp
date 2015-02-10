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

/// @file idlib/utility/environment_error.hpp
/// @brief Environment error exception.
/// @author Michael Heilmann

#pragma once

#if !defined(IDLIB_PRIVATE) || IDLIB_PRIVATE != 1
#error(do not include directly, include `idlib/idlib.hpp` instead)
#endif

#include "idlib/utility/runtime_error.hpp"

#include "idlib/utility/header.in"

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

#include "idlib/utility/footer.in"
