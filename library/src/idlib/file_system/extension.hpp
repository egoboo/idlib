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

/// @file idlib/file_system/extension.hpp
/// @brief Representation of a valid file name extension
/// @author Michael Heilmann

#pragma once

#include "idlib/platform.hpp"
#include "idlib/crtp.hpp"

#include "idlib/file_system/header.in"

namespace internal {

template <typename C>
struct extension_validator
{
	std::basic_string<C> operator()(const std::basic_string<C>& w) const
	{ 
		// Must not be empty.
        if (w.cbegin() == w.cend())
        {
            throw idlib::runtime_error(__FILE__, __LINE__, "invalid extension");
        }
		// Must not contain special characters.
        static const std::vector<C> d{ '*', '?', ':', '.', ',', '/', '\\', ' ', '\t', '\n', '\r' };
        auto it = std::find_first_of(w.cbegin(), w.cend(), d.cbegin(), d.cend());
        if (it != w.cend())
        {
            throw idlib::runtime_error(__FILE__, __LINE__, "invalid extension");
        }
        return w;
    }
}; // struct extension_validator

} // internal

template <typename C>
struct extension;

/// @brief Representation of a valid extension of a file name.
/// A valid extension of a file name is a string of the form @code{'(.-('*', '?', ':', '.', ',', '/', ' ', '\\'))+}.
/// @tparam C the character type.
template <typename C>
struct extension : public equal_to_expr<extension<C>>
{
	using char_type = C;
    using string_type = std::basic_string<char_type>;

	/// @brief Construct this extension with a specified string.
	/// @throw idlib::runtime_error @a string is not a valid extension string
    explicit extension(const string_type& string)
        : m_string(internal::extension_validator<char_type>()(string))
    {}

	/// @brief Get if a string is valid extension string.
	/// @param string a string
	/// @return @a true if @a string is a valid extension string, @a false otherwise
	static bool is_extension_string(const string_type& string)
	{
		try
		{
			internal::extension_validator<char_type>()(string);
		}
		catch (...)
		{
			return false;
		}
		return true;
	}

    const string_type& to_string() const
    { return m_string; }

	bool equal_to(const extension<char_type>& other) const
	{ return m_string == other.m_string; }

private:
    string_type m_string;

}; // struct extension

#include "idlib/file_system/footer.in"

namespace std {

template <typename C>
struct hash<idlib::file_system::extension<C>>
{
    size_t operator()(const idlib::file_system::extension<C>& x) const
    { return hash<basic_string<C>>()(x.to_string()); }
}; // struct hash

} // namespace std
