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

/// @file idlib/utility/assertion_failed_error.hpp
/// @brief Definition of an exception indicating that an assertion failed.
/// @author Michael Heilmann

#pragma once

#if !defined(IDLIB_PRIVATE) || IDLIB_PRIVATE != 1
#error(do not include directly, include `idlib/idlib.hpp` instead)
#endif

#include "idlib/utility/runtime_error.hpp"

#include "idlib/utility/header.in"

/// @brief Exception for an assertion failed error.
class assertion_failed_error : public runtime_error
{
private:
    /// @brief A string describing the assertion e.g. <tt>nullptr != ptr</tt>.
    std::string m_assertion;

public:
    /// @brief Construct this exception.
    /// @param file the C++ source file associated with this exception
    /// @param line the line within the C++ source file associated with this exception
    /// @param assertion a description of the assertion
    explicit assertion_failed_error(const char *file, int line, const std::string& assertion) :
        runtime_error(file, line, "assertion `" + assertion + "` failed"), m_assertion(assertion)
    {}

public:
    /// @brief Get a description of the assertion.
    /// @return a description of the assertion
    const std::string& assertion() const
    {
        return m_assertion;
    }

	friend void swap(assertion_failed_error& a, assertion_failed_error& b)
	{
		using std::swap;
		swap(static_cast<runtime_error&>(a), static_cast<runtime_error&>(b));
		swap(a.m_assertion, b.m_assertion);
	}
	
    virtual std::string to_string() const override
    {
        std::ostringstream buffer;
        buffer << "invalid argument error:" << std::endl;
        buffer << "(raised in file " << file() << ", line " << line() << ")" << ":" << std::endl;
        buffer << message();
        return buffer.str();
    }

}; // class assertion_failed_error

#include "idlib/utility/footer.in"
