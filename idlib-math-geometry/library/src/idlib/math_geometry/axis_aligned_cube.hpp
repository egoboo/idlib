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

/// @file idlib/math/geometry/axis_aligned_cube.hpp
/// @brief Axis aligned cubes.
/// @author Michael Heilmann

#pragma once

#include "idlib/math/point.hpp"
#include "idlib/crtp.hpp"

namespace idlib {

/// @brief An axis aligned cube.
/// @detail An axis aligned cube in \f$\mathbb{R}^n\f$ can be defined in terms of a center point \f$P\f$ and a size \f$s\f$.
/// The set of points of that cube is then given by \f$\left\{ X | P_i - \frac{s}{2} \leq X_i \leq P_i + \frac{s}{2}, 0 \leq i < n \right\}$
/// @tparam P the point type of this axis aligned cube type
template <typename P>
struct axis_aligned_cube : public equal_to_expr<axis_aligned_cube<P>>
{
public:
    /// @brief The point type of this axis aligned cube type.
    using point_type = P;

    /// @brief The vector type of this axis aligned cube type.
    using vector_type = typename P::vector_type;

    /// @brief The scalar type of this axis aligned cube type.
    using scalar_type = typename P::scalar_type;

    /// @brief The dimensionality of this axis aligned cube type.
    /// @return the dimensionality
    static constexpr size_t dimensionality()
    { return vector_type::dimensionality(); }

    /// @brief Construct this axis aligned cube with the default values of an axis aligned cube.
    /// @post This axis aligned cube was constructed with the default values of an axis aligned cube.
    /// @remark The default values of an axis aligned cube are the center of \f$C = 0\f$ and the size of \f$s = 0\f$.
    axis_aligned_cube()
        : m_center(), m_size()
    { /* Intentionally empty. */ }

    /// @brief Construct this axis aligned cube with the specified values.
    /// @param center the center of the axis aligned cube
    /// @param size the size of the axis aligned cube
    /// @throw std::domain_error the size is negative
    /// @pre The size is not negative.
    /// @post The cube was constructed with the specified values.
    axis_aligned_cube(const point_type& center, const scalar_type& size)
        : m_center(center), m_size(size)
    {
        if (m_size < zero<scalar_type>())
        { throw std::domain_error("cube size is negative"); }
    }

    axis_aligned_cube(const axis_aligned_cube&) = default;
    axis_aligned_cube& operator=(const axis_aligned_cube&) = default;

    /// @brief Get the center of this axis aligned cube.
    /// @return the center of this axis aligned cube
    const point_type& get_center() const
    { return m_center; }

    /// @brief Get the size of this axis aligned cube.
    /// @return the size of this axis aligned cube
    const scalar_type& get_size() const
    { return m_size; }

    /// @brief Get the minimum of this axis aligned cube.
    /// @return the minimum of this axis aligned cube
    point_type get_min() const
    {
        static const auto TWO = one<scalar_type>() + one<scalar_type>();
        return get_center() - one<vector_type>() * (get_size() / TWO);
    }

    /// @brief Get the maximum of this axis aligned cube.
    /// @return the maximum of this axis aligned cube
    point_type get_max() const
    {
        static const auto TWO = one<scalar_type>() + one<scalar_type>();
        return get_center() + one<vector_type>() * (get_size() / TWO);
    }

    // CRTP
    bool equal_to(const axis_aligned_cube& other) const
    {
        return get_center() == other.get_center()
            && get_size() == other.get_size();
    }

private:
    /// @brief The center of the cube.
    point_type m_center;

    /// @brief The size of the cube.
    /// @invariant Greater than or equal to @a 0.
    scalar_type m_size;

}; // struct axis_aligned_cube

/// @brief Specialization of idlib::enclose_functor enclosing an axis aligned cube in an axis aligned cube.
/// @detail The axis aligned cube \f$b\f$ enclosing an axis aligned cube \f$a\f$ is \f$a\f$ itself i.e. \f$b = a\f$.
/// @tparam P the point type of the axis aligned cube types
template <typename P>
struct enclose_functor<axis_aligned_cube<P>, axis_aligned_cube<P>>
{
    auto operator()(const axis_aligned_cube<P>& source) const
    { return source; }
}; // struct enclose_functor

/// @brief Specialization of idlib::is_enclosing_functor.
/// Determines if an axis aligned cube encloses a point.
/// @remark An axis aligned cube \$A\f$ does <em>not</em> enclose a point \f$P\f$
/// if for at least one axis \$k\f$ at least one of the following conditions is true:
/// - \f$P_k > A_{max_k}\f$
/// - \f$P_k < A_{min_k}\f$
/// Otherwise \f$A\f$ contains \f$P\f$.
/// This is a variant of the Separating Axis Theorem (aka SAT).
/// @tparam P the point type of the axis aligned cube type
template <typename P>
struct is_enclosing_functor<axis_aligned_cube<P>, P>
{
    bool operator()(const axis_aligned_cube<P>& a, const P& b) const
    {
        for (size_t i = 0; i < P::dimensionality(); ++i)
        {
            if (a.get_max()[i] < b[i]) return false;
            if (a.get_min()[i] > b[i]) return false;
        }
        return true;
    }
}; // struct is_enclosing_functor

/// @brief Specialization of idlib::is_enclosing_functor.
/// Determines if an axis aligned cube encloses another axis aligned cube.
/// @remark An axis aligned cube \f$A\f$ does <em>not</em> enclose an axis aligned cube \f$B\f$
/// if for at least one axis \$k\f$ at least one of the following conditions is true:
/// - \f$A_{min_k} > B_{min_k}\f$
/// - \f$A_{max_k} < B_{max_k}\f$
/// Otherwise \f$x\f$ contains \f$y\f$.
/// This is a variant of the Separating Axis Theorem (aka SAT).
/// @tparam P the point type of the axis aligned cube types
template <typename P>
struct is_enclosing_functor<axis_aligned_cube<P>, axis_aligned_cube<P>>
{
    bool operator()(const axis_aligned_cube<P>& a, const axis_aligned_cube<P>& b) const
    {
        for (size_t i = 0; i < P::dimensionality(); ++i)
        {
            // If a is the cube that is supposed to contain the
            // cube b, then a does not contain b if along some axis
            // - the maximum of a is smaller than the maximum of b, or
            if (a.get_max()[i] < b.get_max()[i]) return false;
            // - the minimum of a is greater than the minimum of b.
            if (a.get_min()[i] > b.get_min()[i]) return false;
        }
        return true;
    }
}; // struct is_enclosing_functor

/// @brief Specialization of idlib::translate_functor.
/// Translates an axis aligned cube.
/// @tparam P the point type of the axis aligned cube type
template <typename P>
struct translate_functor<axis_aligned_cube<P>, typename P::vector_type>
{
    auto operator()(const axis_aligned_cube<P>& x, const typename P::vector_type& t) const
    {
        return axis_aligned_cube<P>(x.get_center() + t, x.get_size());
    }
}; // struct translate_functor

/// @brief Specialization of idlib::is_intersecting_functor.
/// Determines if two axis aligned cubes intersect.
/// @remark Two axis aligned cubes \f$A\f$ and \f$B\f$ do <em>not</em> intersect
/// if for at least one axis \f$k\f$ at least one of the following conditions is true:
/// - \f$A_{min_k} > B_{max_k}\f$
/// - \f$A_{max_k} < B_{min_k}\f$
/// Otherwise \f$A\f$ and \f$B\f$ intersect.
/// This is a variant of the Separating Axis Theorem (aka SAT).
/// @tparam P the point type of the axis aligned cube type
template <typename P>
struct is_intersecting_functor<axis_aligned_cube<P>, axis_aligned_cube<P>>
{
    bool operator()(const axis_aligned_cube<P>& a, const axis_aligned_cube<P>& b) const
    {
        for (size_t i = 0; i < P::dimensionality(); ++i)
        {
            // If the minimum of a is greater than the maximum of b along one axis,
            // then they can not intersect.
            if (a.get_min()[i] > b.get_max()[i])
            {
                return false;
            }
            // If the maximum of a is smaller than the minimum of b along one axis,
            // then they can not intersect.
            if (a.get_max()[i] < b.get_min()[i])
            {
                return false;
            }
        }
        return true;
    }
}; // struct is_intersecting_functor

/// @brief Specialization of idlib::is_intersecting_functor.
/// Determines if an axis aligned cube and a point intersect.
/// @remark A point \f$P\f$ and an axis aligned cube \f$A\f$ do <em>not</em> intersect
/// if for at least one axis \f$k\f$ at least one of the following conditions is true:
/// - \f$P_k > A_{max_k}\f$
/// - \f$P_k < A_{min_k}\f$
/// Otherwise \f$P\f$ and \f$A\f$ intersect.
/// @tparam P the point type of the axis aligned cube type
template <typename P>
struct is_intersecting_functor<axis_aligned_cube<P>, P>
{
    bool operator()(const axis_aligned_cube<P>& a, const P& b) const
    {
        for (size_t i = 0; i < P::dimensionality(); ++i)
        {
            if (a.get_max()[i] < b[i]) return false;
            if (a.get_min()[i] > b[i]) return false;
        }
        return true;
    }
}; // struct is_intersecting_functor

/// @brief Specialization of idlib::is_intersecting_functor.
/// Determines if a point and an axis aligned cube intersect.
/// @remark The method for determinating if an axis aligned cube and a point intersect is
/// commutative. By swapping the arguments that method can be reused to determine if a
/// point and an axis aligned box intersect.
/// @tparam P the point type of the axis aligned cube type
template <typename P>
struct is_intersecting_functor<P, axis_aligned_cube<P>>
{
    bool operator()(const P& a, const axis_aligned_cube<P>& b) const
    { return is_intersecting(b, a); }
}; // struct is_intersecting_functor

} // namespace idlib
