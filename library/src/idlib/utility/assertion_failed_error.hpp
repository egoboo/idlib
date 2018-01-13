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
