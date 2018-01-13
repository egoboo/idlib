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

#pragma once

#if !defined(IDLIB_PRIVATE) || IDLIB_PRIVATE != 1
#error(do not include directly, include `idlib/idlib.hpp` instead)
#endif

#include "idlib/language/location.hpp"
#include "idlib/language/category_element.hpp"

#define ID_TOKEN_WITH_ENDLOCATION (0)

namespace id { namespace c {

/// @brief Generic token.
/// @tparam Kind the type of the kinds of this token type.
template <typename Kind, Kind DefaultKind>
class token	: public category_element<Kind, DefaultKind>
{
private:
	/// @brief The start location of this token.
	location m_start_location;

#if defined(ID_TOKEN_WITH_END_LOCATION) && 1 == ID_TOKEN_WITH_END_LOCATION
    /// @brief The end location of this token.
    location m_end_location;
#endif

	/// @brief The lexeme of this token.
	std::string m_lexeme;

public:
	/// @brief Construct this token with the specified values.
	/// @param kind the kind of this token
	/// @param start_location the start location of this token
    /// @param end_location the end location of this token
	/// @param lexeme the lexeme of this token. Default is the empty string.
	token(Kind kind,
          const location& start_location,
      #if defined(ID_TOKEN_WITH_END_LOCATION) && 1 == ID_TOKEN_WITH_END_LOCATION  
          const location& end_location,
      #endif
          const std::string& lexeme = std::string())
		: category_element<Kind, DefaultKind>(kind),
          m_start_location(start_location),
    #if defined(ID_TOKEN_WITH_END_LOCATION) && 1 == ID_TOKEN_WITH_END_LOCATION  
          m_end_location(end_location),
    #endif
          m_lexeme(lexeme)
	{}
	
public:
#if defined(ID_TOKEN_WITH_END_LOCATION) && 1 == ID_TOKEN_WITH_END_LOCATION
    /// @brief @brief Get the end location of this token.
    /// @return the end location of this token
    /// @see set_end_location
    /// @remark The end location is the location at which the lexeme of this token ends at.
    const location& get_end_location() const noexcept
    {
        return m_endLocation;
    }

    /// @brief Set the end location of this token.
    /// @param endLocation the end location of this token
    /// @see get_end_location
    void set_end_location(const location& end_location) noexcept(std::i_nothrow_assignable<location>::value)
    {
        m_end_location = end_location;
    }
#endif

	/// @brief @brief Get the start location of this token.
	/// @return the start location of this token
    /// @see set_start_location
    /// @remark The start location is the location at which the lexeme of this token starts at.
	constexpr const location& get_start_location() const noexcept
	{
		return m_start_location;
	}
	
	/// @brief Set the start location of this token.
	/// @param start_location the start location of this token
    /// @see get_start_Location
	void set_start_location(const location& start_location) noexcept(std::is_nothrow_assignable<location, location>::value)
	{
		m_start_location = start_location;
	}

	/// @brief Get the lexeme of this token.
	/// @return the lexeme of this token
    /// @see set_lexeme
	const std::string& get_lexeme() const noexcept
	{
		return m_lexeme;
	}
	
	/// @brief Set the lexeme of this token.
	/// @param lexeme the lexeme of this token
    /// @see getLexeme
	void set_lexeme(const std::string& lexeme) noexcept(std::is_nothrow_assignable<std::string, std::string>::value)
	{
		m_lexeme = lexeme;
	}

}; // class token

} } // namespace id::c
