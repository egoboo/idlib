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

/// @file idlib/math/normalize.hpp
/// @brief "normalize" functor and function
/// @author Michael Heilmann

namespace idlib {

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

} // namespace idlib
