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
