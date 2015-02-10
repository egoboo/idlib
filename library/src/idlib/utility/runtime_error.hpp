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

/// @file idlib/utility/runtime_error.hpp
/// @brief Generic runtime error exception.
/// @author Michael Heilmann

#pragma once

#if !defined(IDLIB_PRIVATE) || IDLIB_PRIVATE != 1
#error(do not include directly, include `idlib/idlib.hpp` instead)
#endif

#include "idlib/utility/exception.hpp"

#include "idlib/utility/header.in"

/// @brief A generic exception indicating a runtime error.
/// @detail Use this exception only if there is no exception type available which is more specific.
class runtime_error : public exception
{
public:
    /// @brief Construct this runtime error exception.
    /// @param file the C++ source file (as obtained by the __FILE__ macro) associated with this exception
    /// @param line the line within the C++ source file (as obtained by the __LINE__ macro) associated with this exception
    /// @param message a message describing the error
    explicit runtime_error(const char *file, int line, const std::string& message) :
        exception(file, line), m_message(message)
    {}

	friend void swap(runtime_error& a, runtime_error& b) noexcept
	{
		using std::swap;
		swap(static_cast<exception&>(a), static_cast<exception&>(b));
		swap(a.m_message, b.m_message);
	}

    /// @brief Get the message associated with this environment error.
    /// @return the message associated with this environment error
    const std::string& message() const noexcept
    { return m_message; }
	
    /// @brief Overloaded cast operator for casting into std::string.
    /// @return a human-readable textual description of the string.
	virtual std::string to_string() const override
	{
        std::ostringstream buffer;
		buffer << "runtime error:" << std::endl;
        buffer << "(raised in file " << file() << ", line " << line() << ")" << ":" << std::endl;
        buffer << message();
        return buffer.str();
	}

private:
    /// @brief The exception message.
    std::string m_message;

}; // struct runtime_error

#include "idlib/utility/footer.in"
