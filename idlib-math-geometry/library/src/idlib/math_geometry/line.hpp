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

/// @file idlib/math_geometry/line.hpp
/// @brief Lines.
/// @author Michael Heilmann

#pragma once

#include "idlib/math/point.hpp"
#include "idlib/crtp.hpp"

namespace idlib {

/// @brief A line.
/// @detail
/// A line can be specified by two endpoints \f$A\f$ and \f$B\f$ or an origin point \f$O\f$ and a direction vector \f$d\f$.
/// The set of points of a line is given either by
/// \f$\{ (1-t) A + t B| t \in \mathbb{R}_{[0, 1]} \}\f$
/// or by
/// \f$\{ O + t d | t \in \mathbb{R}_{[0, 1]} \}\f$
template <typename P>
struct line : public equal_to_expr<line<P>>
{
public:
    /// @brief The point type of this line type.
    using point_type = P;

    /// @brief The vector type of this line type.
    using vector_type = typename point_type::vector_type;

    /// @brief The scalar type of this line type.
    using scalar_type = typename point_type::scalar_type;
    
    /// @brief The dimensionality of this line type.
    /// @return the dimensionality
    static constexpr size_t dimensionality()
    { return vector_type::dimensionality(); }

    /// @brief Default construct this line.
    /// @post The line starts at the origin and is of zero length.
    line()
        : m_a(zero<point_type>()), m_b(zero<point_type>()) 
    {}

    /// @brief Construct this line with the specified end points.
    /// @param a, b the end points \f$A\f$ and \f$B\f$
    line(const point_type& a, const point_type& b) :
        m_a(a), m_b(b)
    {}

    line(const line&) = default;
    line& operator=(const line&) = default;

    /// @brief Get the 1st end point \f$A\f$ of this line.
    /// @return the 1st end point \f$A\f$ of this line
    const point_type& get_a() const
    { return m_a; }

    /// @brief Get the 2nd end point \f$B\f$ of this line.
    /// @return the 2nd end point \f$B\f$ of the line
    const point_type& get_b() const
    { return m_b; }

    // CRTP
    bool equal_to(const line& other) const
    {
        return m_a == other.m_a
            && m_b == other.m_b;
    }

private:
    /// @brief The 1st point \f$A\f$.
    point_type m_a;

    /// @brief The 2nd point \f$B\f$.
    point_type m_b;

}; // struct line

/// @brief Specialization of idlib::enclose_functor enclosing a line in a line.
/// @detail The line \f$b\f$ enclosing a line \f$a\f$ is \f$a\f$ itself i.e. \f$b = a\f$.
/// @tparam P the point type of the lines
template <typename P>
struct enclose_functor<line<P>, line<P>>
{
    auto operator()(const line<P>& source) const
    { return source; }
}; // struct enclose_functor

/// @brief Specialization of idlib::translate_functor.
/// Translates a line.
/// @tparam E the Euclidean space type of the geometry
template <typename P>
struct translate_functor<line<P>, typename P::vector_type>
{
    auto operator()(const line<P>& x, const typename P::vector_type& t) const
    { return line<P>(x.get_a() + t, x.get_b() + t); }
}; // struct translate_functor

} // namespace idlib
