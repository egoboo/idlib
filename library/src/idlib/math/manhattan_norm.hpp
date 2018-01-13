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

/// @file idlib/math/manhattan_norm.hpp
/// @brief "Manhattan norm" functor and function
/// @author Michael Heilmann

#pragma once

namespace id {

/// @ingroup math
/// @brief Functor computing the Manhattan norm of a vector.
/// @remark For a vector \f$v\f$ of dimensionality \f$n\f$ the Manhattan norm is defined as
/// \f[
/// \sum_{i=0}^{n-1}|v_i|
/// \f]
/// @tparam Vector the vector type
template <typename Vector>
struct manhattan_norm_functor;

template <typename Vector>
auto manhattan_norm(const Vector& v) -> decltype(manhattan_norm_functor<Vector>()(v))
{ return manhattan_norm_functor<Vector>()(v); }

} // namespace id
