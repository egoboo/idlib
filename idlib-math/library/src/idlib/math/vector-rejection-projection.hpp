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

/// @file idlib/math/vector-projection-rejection.hpp
/// @brief Projection and rejection of vectors.
/// @author Michael Heilmann

#pragma once

#include "idlib/platform.hpp"

namespace idlib {

/**
 * Compute the vector projection of a vector \f$\vec{v}\f$ onto a vector \f$\vec{w}\f$.
 * @param v the vector \f$\vec{v}\f$
 * @param w the vector \f$\vec{w}\f$
 * @return the projection of this vector \f$\vec{v}\f$ onto a vector \f$\vec{w}\f$
 * @remark The vector projection is defined as
 * \f{align*}
 * proj(\vec{v},\vec{w}) = \frac{\vec{v} \cdot \vec{w}}{|\vec{w}|^2} \vec{w}
 * \f}
 * which is the definition this implementation is using.
 * @throw idlib::runtime_error the vector \f$\vec{w}\f$ is the zero vector
 */
template <typename V>
V vector_projection(const V& v, const V& w)
{
    auto l = squared_euclidean_norm(w);
    if (l == zero<typename V::scalar_type>())
    {
        runtime_error(__FILE__, __LINE__, "vector w must not be the zero vector");
    }
    return w * (dot_product(w, v) / l);
}

/**
 * @brief Compute the rejection of a vector \f$\vec{v}\f$ onto a vector \f$\vec{w}\f$.
 * @param v the vector \$\vec{v}\f$
 * @param w the vector \$\vec{w}\f$
 * @return the rejection of the vector \$v\f$ onto a vector \f$w\f$
 * @remark The vector rejection of a vector \f$v\f$ onto a vector \f$w\f$
 * is defined as
 * \f{align*}
 * rej(\vec{v},\vec{w}) = \vec{v} - proj(\vec{v},\vec{w}) 
 * \f}
 * where \f$proj(\vec{v},\vec{w})\f$ is the vector projection of the vector \f$\vec{v}\f$ onto the vector \f$\vec{w}\f$.
 * @throw idlib::runtime_error the vector \f$\vec{w}\f$ is the zero vector
 */
template <typename V>
V vector_rejection(const V& v, const V& w)
{ return v - vector_projection(v, w); }

} // namespace idlib
