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

/// @file idlib/math/maximum_norm.hpp
/// @brief "maximum norm" functor and function
/// @author Michael Heilmann

#pragma once

namespace id {

/// @ingroup math
/// @brief Functor computing the maximum norm of a vector.
/// @remark For a vector \f$v\f$ of dimensionality \f$n\f$ the maximum norm is defined as
/// \f[
/// \max_{i=0}^{n-1} |v_i|
/// \f]
/// @tparam Vector the vector type
template <typename Vector>
struct maximum_norm_functor;

template <typename Vector>
auto maximum_norm(const Vector& v) -> decltype(maximum_norm_functor<Vector>()(v))
{ return maximum_norm_functor<Vector>()(v); }

} // namespace id
