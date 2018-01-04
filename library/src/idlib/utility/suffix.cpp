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

/// @file idlib/utility/suffix.cpp
/// @brief Explicit template instantiations.
/// @author Michael Heilmann

#include "idlib/utility/suffix.hpp"

#include "idlib/utility/header.in"

template bool is_suffix<char>(const std::basic_string<char>& w, const std::basic_string<char>& v);
template bool is_suffix<wchar_t>(const std::basic_string<wchar_t>& w, const std::basic_string<wchar_t>& v);

template bool is_true_suffix<char>(const std::basic_string<char>& w, const std::basic_string<char>& v);
template bool is_true_suffix<wchar_t>(const std::basic_string<wchar_t>& w, const std::basic_string<wchar_t>& v);

#include "idlib/utility/footer.in"
