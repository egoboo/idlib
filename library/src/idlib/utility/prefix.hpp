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

/// @file idlib/utility/prefix.hpp
/// @brief Test if a string is prefix of another string.
/// @detail A word @a v is a prefix of a word @a w if there exists a decomposition such that w = vp.
/// @a v is a true prefix of @a w if @a p is not empty.
/// @author Michael Heilmann

#pragma once

#include <string>

#include "idlib/utility/header.in"

/// @brief Get if a string is a prefix of another string.
/// @param w the string
/// @param v the string which is tested if it is a prefix of @a w
/// @return @a true if @a v is a prefix of @a w, @a false otherwise
template <typename CharType>
bool is_prefix(const std::basic_string<CharType>& w, const std::basic_string<CharType>& v)
{
    if (v.size() > w.size()) return false;
    return std::equal(v.cbegin(), v.cend(), w.cbegin());
}

/// @brief Get if a character is a prefix of a string.
/// @param w the string
/// @param v the character which is tested if it is a prefix of @a w
/// @return @a true if @a v is a prefix of @a w, @a false otherwise
template <typename CharType>
bool is_prefix(const std::basic_string<CharType>& w, const CharType& v)
{
    if (w.length() < 1) return false; // If |w| < 1, then v can not be a prefix of w.
	return v == w[0];
}

/// @brief Get if a string is a true prefix of another string.
/// @param w the string
/// @param v the string which is tested if it is a true prefix of @a w
/// @return @a true if @a v is a true prefix of @a w, @a false otherwise
template <typename CharType>
bool is_true_prefix(const std::basic_string<CharType>& w, const std::basic_string<CharType>& v)
{
    if (v.size() >= w.size()) return false;
    return std::equal(v.cbegin(), v.cend(), w.cbegin());
}

/// @brief Get if a character is a true prefix of a string.
/// @param w the string
/// @param v the character which is tested if it is a true prefix of @a w
/// @return @a true if @a v is a true prefix of @a w, @a false otherwise
template <typename CharType>
bool is_true_prefix(const std::basic_string<CharType>& w, const CharType& v)
{ 
    if (w.length() < 2) return false; // If |w| < 2, then v can not be a true prefix of w.
	return v == w[0];
}

#include "idlib/utility/footer.in"
