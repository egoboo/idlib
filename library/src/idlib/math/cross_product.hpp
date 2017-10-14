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

/// @file idlib/math/cross_product.hpp
/// @brief "cross product" functor and function
/// @author Michael Heilmann

#pragma once

namespace id {

/// @brief Functor computing the cross product of two vectors.
/// @tparam Vector the vector type
template <typename Vector>
struct cross_product_functor;

template <typename Vector>
auto cross_product(const Vector& v, const Vector& w) -> decltype(cross_product_functor<Vector>()(v, w))
{ return cross_product_functor<Vector>()(v, w); }

} // namespace id
