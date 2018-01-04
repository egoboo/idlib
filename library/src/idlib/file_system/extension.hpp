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

/// @file idlib/file_system/extension.hpp
/// @brief Representation of a valid file name extension
/// @author Michael Heilmann

#pragma once

#include "idlib/utility/platform.hpp"
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
            throw id::runtime_error(__FILE__, __LINE__, "invalid extension");
        }
		// Must not contain special characters.
        static const std::vector<C> d{ '*', '?', ':', '.', ',', '/', '\\', ' ', '\t', '\n', '\r' };
        auto it = std::find_first_of(w.cbegin(), w.cend(), d.cbegin(), d.cend());
        if (it != w.cend())
        {
            throw id::runtime_error(__FILE__, __LINE__, "invalid extension");
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
	/// @throw id::runtime_error @a string is not a valid extension string
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
struct hash<id::file_system::extension<C>>
{
    size_t operator()(const id::file_system::extension<C>& x) const
    { return hash<basic_string<C>>()(x.to_string()); }
}; // struct hash

} // namespace std
