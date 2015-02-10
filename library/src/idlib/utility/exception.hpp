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

/// @file idlib/utility/exception.hpp
/// @brief Root of the exception hierarchy.
/// @author Michael Heilmann

#pragma once

#if !defined(IDLIB_PRIVATE) || IDLIB_PRIVATE != 1
#error(do not include directly, include `idlib/idlib.hpp` instead)
#endif

#include "idlib/utility/platform.hpp"

#include "idlib/utility/header.in"

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

#include "idlib/utility/footer.in"
