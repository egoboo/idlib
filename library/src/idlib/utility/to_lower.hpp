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

/// @file idlib/utility/to_lower.hpp
/// @brief Conversion of characters and strings to lowercase.
/// @detail For each function an in-place (aka in-situ) variant and a variant returning a copy are provided.
/// @author Michael Heilmann

#pragma once

#include <locale>
#include <algorithm>

#include "idlib/utility/header.in"

/// @brief In-place (aka in-situ) convert a character to lower case.
/// @param x the character
/// @param lc the locale to use. Default is std::locale().
template <class CharType>
void to_lower_in_situ(CharType& x, const std::locale& lc = std::locale())
{
    x = std::tolower(x, lc);
}

/// @brief Convert a character to lower case.
/// @param x the character
/// @param lc the locale to use. Default is std::locale().
/// @return the lower case character
template <class CharType>
CharType to_lower(CharType x, const std::locale& lc = std::locale())
{
    return std::tolower(x, lc);
}

/// @brief In-place (aka in-situ) convert a string to lower case.
/// @param w the string
/// @param lc the locale to use. Default is std::locale().
template <typename CharType>
void to_lower_in_situ(std::basic_string<CharType>& w, const std::locale& lc = std::locale())
{
    // Capture lc by reference, capture nothing else.
    auto f = [&lc](const CharType chr) -> CharType { return to_lower(chr, lc); };
    std::transform(w.begin(), w.end(), w.begin(), f);
}

/// @brief In-place (aka in-situ) convert a string to upper case.
/// @param w the string
/// @param lc the locale to use. Default is std::locale().
/// @return the upper case string
template <typename CharType>
std::basic_string<CharType> to_lower(std::basic_string<CharType> w, const std::locale& lc = std::locale())
{
    // Capture lc by reference, capture nothing else.
    auto f = [&lc](const CharType chr) -> CharType { return to_lower(chr, lc); };
    std::transform(w.begin(), w.end(), w.begin(), f);
    return w;
}

#include "idlib/utility/footer.in"
