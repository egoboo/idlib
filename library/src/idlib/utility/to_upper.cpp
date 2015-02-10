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
