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

#pragma once

#include "idlib/math/one_zero.hpp"

namespace id {

/// @brief Functor determinating if a value is positive.
/// @tparam T the value type
/// @remark Specializations shall provide a constant operator() which takes an argument @a v of type @a T and shall return  @a true if @a v is greater than id::zero<T>() and @a false otherwise.
template <typename T>
struct is_positive_functor;

template <typename T>
auto is_positive(const T& v) -> decltype(is_positive_functor<T>()(v))
{ return is_positive_functor<T>()(v); }

} // namespace id
