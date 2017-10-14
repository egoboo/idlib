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

/// @file idlib/math/normalize.hpp
/// @brief "normalize" functor and function
/// @author Michael Heilmann

namespace id {

/// @ingroup math
/// @brief Functor computing a normalized vector.
/// @remark For a vector \f$v\f$ of dimensionality \f$n\f$ the normalized vector is defined as
/// \f[
/// \frac{v}{|v|}
/// \f]
/// where \f$|.|\f$ is a norm.
/// @tparam Vector the vector type
/// @tparam Norm the norm functor type
template <typename Vector, typename Norm>
struct normalize_functor;

template <typename Vector, typename Norm>
auto normalize(const Vector& v, const Norm& n) -> decltype(normalize_functor<Vector, Norm>()(v, n))
{ return normalize_functor<Vector, Norm>()(v, n); }

} // namespace id
