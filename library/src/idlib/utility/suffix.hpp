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

/// @file idlib/utility/suffix.hpp
/// @brief Test if a string is suffix of another string.
/// @detail A word @a v is a suffix of a word @a w if there exists a decomposition such that w = pv.
/// @a v is a true suffix of @a w if @a p is not empty.
/// @author Michael Heilmann

#pragma once

#include <string>

#include "idlib/utility/header.in"

/// @brief Get if a string is a suffix of another string.
/// @param w the string
/// @param v the string which is tested if it is a suffix of @a w
/// @return @a true if @a v is a suffix of @a w, @a false otherwise
template <typename CharType>
bool is_suffix(const std::basic_string<CharType>& w, const std::basic_string<CharType>& v)
{
    if (v.size() > w.size()) return false;
    return std::equal(v.crbegin(), v.crend(), w.crbegin());
}

/// @brief Get if a character is a suffix of a string.
/// @param w the string
/// @param v the character which is tested if it is a suffix of @a w
/// @return @a true if @a v is a suffix of @a w, @a false otherwise
template <typename CharType>
bool is_suffix(const std::basic_string<CharType>& w, const CharType& v)
{
    if (w.size() < 1) return false; // If |w| < 1, then v can not be a true suffix of w.
	return v == w[w.size()-1];
}

/// @brief Get if a string is a true suffix of another string.
/// @param w the string
/// @param v the string which is tested if it is a true suffix of @a w
/// @return @a true if @a v is a true suffix of @a w, @a false otherwise
template <typename CharType>
bool is_true_suffix(const std::basic_string<CharType>& w, const std::basic_string<CharType>& v)
{
    if (v.size() >= w.size()) return false;
    return std::equal(v.crbegin(), v.crend(), w.crbegin());
}

/// @brief Get if a character is a true suffix of a string.
/// @param w the string
/// @param v the character which is tested if it is a true suffix of @a w
/// @return @a true if @a v is a true suffix of @a w, @a false otherwise
template <typename CharType>
bool is_true_suffix(const std::basic_string<CharType>& w, const CharType& v)
{ 
    if (w.size() < 2) return false; // If |w| < 2, then v can not be a true suffix of w.
	return v == w[w.size()-1];
}

#include "idlib/utility/footer.in"
