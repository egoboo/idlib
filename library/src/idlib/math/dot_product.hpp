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

/// @file idlib/math/dot_product.hpp
/// @brief "dot product" functor and function
/// @author Michael Heilmann

#pragma once

namespace idlib {

/// @brief Functor computing the dot product of two vectors.
/// @tparam Vector the vector type
template <typename Vector>
struct dot_product_functor;

template <typename Vector>
auto dot_product(const Vector& v, const Vector& w) -> decltype(dot_product_functor<Vector>()(v, w))
{ return dot_product_functor<Vector>()(v, w); }

} // namespace idlib
