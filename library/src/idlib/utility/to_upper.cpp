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

/// @file idlib/utility/to_upper.cpp
/// @brief Explicit template instantiations.
/// @author Michael Heilmann

#include "idlib/utility/to_upper.hpp"

#include "idlib/utility/header.in"

template void to_upper_in_situ<char>(char& x, const std::locale& lc);
template void to_upper_in_situ<wchar_t>(wchar_t& x, const std::locale& lc);

template char to_upper<char>(char x, const std::locale& lc);
template wchar_t to_upper<wchar_t>(wchar_t x, const std::locale& lc);

template void to_upper_in_situ<char>(std::basic_string<char>& w, const std::locale& lc);
template void to_upper_in_situ<wchar_t>(std::basic_string<wchar_t>& w, const std::locale& lc);

template std::basic_string<char> to_upper<char>(std::basic_string<char> w, const std::locale& lc);
template std::basic_string<wchar_t> to_upper<wchar_t>(std::basic_string<wchar_t> w, const std::locale& lc);

#include "idlib/utility/footer.in"
