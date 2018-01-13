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

/// @file egolib/math/geometry/sphere.hpp
/// @brief Spheres.
/// @author Michael Heilmann

#pragma once

#include "idlib/math/point.hpp"
#include "idlib/crtp.hpp"
#include "idlib/math/floating_point.hpp"

namespace id {

/// @brief A sphere has a center point \f$C\f$ and a radius \f$r \geq 0\f$.
/// The set of points of a sphere is given by \f$\left{ P | 0 \leq d(C,P) \leq r\right}\f$.
template <typename P>
struct sphere : public equal_to_expr<sphere<P>>
{
public:
	/// @brief The point type of this ray type.
	using point_type = P;

	/// @brief The vector type of this ray type.
	using vector_type = typename point_type::vector_type;

	/// @brief The scalar type of this ray type.
	using scalar_type = typename point_type::scalar_type;
	
	/// @brief The dimensionality of this sphere type.
	/// @return the dimensionality
	static constexpr size_t dimensionality()
	{ return vector_type::dimensionality(); }

    /// @brief Construct this sphere with the default values of a sphere.
    /// @post This sphere was constructed with the default values of a sphere.
    /// @remark The default values of a sphere are \f$C = 0\f$ and \f$r = 1\f$.
    sphere()
        : m_center(zero<point_type>()), m_radius(zero<scalar_type>())
	{ /* Intentionally empty. */ }

    /// @brief Construct this sphere with the specified center and radius.
	/// @param center the center of this sphere
	/// @param radius the radius of this sphere
	/// @throw std::domain_error the radius is negative
    /// @pre The radius is non-negative.
    /// @post The sphere was constructed with the specified values.
    sphere(const point_type& center, const scalar_type& radius)
        : m_center(center), m_radius(radius)
	{
        if (m_radius < zero<scalar_type>())
		{ throw std::domain_error("sphere radius is negative"); }
    }

	sphere(const sphere&) = default;
	sphere<point_type>& operator=(const sphere&) = default;

	/// @{

	/// @brief Get the center \f$C\f$ of this sphere.
	/// @return the center \f$C\f$ of this sphere
    const point_type& get_center() const
	{ return m_center; }

    /// @brief Set the center of this sphere.
    /// @param center the center
    void set_center(const point_type& center)
	{ m_center = center; }

	/// @}

    /// @{

	/// @brief Get the radius of this sphere.
    /// @return the radius of this sphere
    const scalar_type& get_radius() const
	{ return m_radius; }

	/// @brief Set the radius of this sphere.
	/// @param radius the radius
	/// @pre The radius must be non-negative.
	/// @throw std::domain_error the radius is negative
	/// @post If an exception is raised, the sphere's radius was not modified.
	void set_radius(const scalar_type& radius)
	{
		if (radius < zero<scalar_type>())
		{ throw std::domain_error("sphere radius is negative"); }
		m_radius = radius;
	}

	/// @brief Get the squared radius of this sphere.
	/// @return the squared radius of this sphere
	scalar_type get_radius_squared() const
	{ return m_radius * m_radius; }

	/// @}

	/// @{

    /// @brief Get the diameter of this sphere.
    /// @return the diameter of this sphere
	scalar_type get_diameter() const
	{ 
		static const auto TWO = one<scalar_type>() + one<scalar_type>();
		return get_radius() * TWO;
	}

    /// @brief Get the squared diameter of this sphere.
    /// @return the squared diameter of this sphere
    scalar_type get_diameter_squared() const
	{
        auto diameter = get_diameter();
        return diameter * diameter;
    }

	/// @}

	// CRTP
    bool equal_to(const sphere& other) const
	{
        return get_center() == other.get_center()
            && get_radius() == other.get_radius();
    }

private:
	/// @brief The center point \f$C\f$ of this sphere.
	point_type m_center;

	/// @brief The radius \f$r\f$ of this sphere.
	/// @invariant \f$r \geq 0\f$.
	scalar_type m_radius;

}; // struct sphere

/// @brief Specialization of id::enclose_functor enclosing a sphere into a sphere.
/// @detail The sphere \f$b\f$ enclosing a sphere \f$a\f$ is \f$a\f$ itself i.e. \f$b = a\f$.
/// @tparam P the point type of the spheres
template <typename P>
struct enclose_functor<sphere<P>, sphere<P>>
{
	auto operator()(const sphere<P>& source) const
	{ return source; }
}; // struct enclose_functor

/// @brief Specialization of id::is_enclosing_functor.
/// Determines wether a sphere contains a point.
/// @remark A sphere \f$(c,r)\f$ with the center $c$ and the radius $r$
/// contains a point \f$p\f$ if \f$|p - c| \leq r\f$ holds.
/// That condition is equivalent to the condition \f$|p - c|^2
/// \leq r^2\f$ but the latter is more efficient to test (two
/// multiplications vs. one square root).
template <typename P>
struct is_enclosing_functor<sphere<P>, P>
{
	bool operator()(const sphere<P>& a, const P& b) const
	{
		// Get the squared distance from the point to the center of the sphere.
		auto distance_squared = id::squared_euclidean_norm(a.get_center() - b);
		// Get the squared radius of the sphere.
		auto radius_squared = a.get_radius_squared();
		// If the squared distance beween the point and the center of the sphere
		// is smaller than or equal to the squared radius of the sphere ...
		if (distance_squared <= radius_squared)
		{
			// ... the sphere contains the point.
			return true;
		}
		// Otherwise the sphere does not contain the point.
		return false;
	}
}; // struct is_enclosing_functor

/// @brief Specialization of id::is_enclosing_functor.
/// Determine if a sphere contains another sphere.
/// @remark
/// A sphere \f$S\f$ with center \f$c\f$ and radius \f$r\f$ contains
/// another sphere \f$S'\$ with center \f$c'\f$ and radius \f$r'\f$
/// if \f$|c-c'|+r' \leq r\f$ holds.
template <typename P>
struct is_enclosing_functor<sphere<P>, sphere<P>>
{
	bool operator()(const sphere<P>& a, const sphere<P>& b) const
	{
		return euclidean_norm(a.get_center() - b.get_center()) + b.get_radius()
			<= a.get_radius();
	}
}; // struct is_enclosing_functor

/// @brief Specialization of id::translate_functor.
/// Translates an sphere.
/// @tparam P the point type of the sphere
template <typename P>
struct translate_functor<sphere<P>, typename P::vector_type>
{
	auto operator()(const sphere<P>& x, const typename P::vector_type& t) const
	{ return sphere<P>(x.get_center() + t, x.get_radius()); }
}; // struct translate_functor

/// @brief Specialization of id::is_intersecting_functor.
/// Determines if two spheres intersect.
/// @remark Two spheres \f$X\f$ and \f$Yf$ with the
/// centers \f$X_C\f$ and \f$Y_Y\f$ and the radii \f$X_r\f$
/// and \f$Y_r\f$ intersect if \f$|X_c - Y_c| \leq X_r + Y_r\f$
/// holds. That condition is equivalent to the condition
/// \f$|X_C - Y_C|^2 \leq (X_ + Y_r)^2\f$. In terms of
/// an implementation the former is usually less efficient
/// than the latter.
template <typename P>
struct is_intersecting_functor<sphere<P>, sphere<P>>
{
	bool operator()(const sphere<P>& a, const sphere<P>& b) const
	{
		// Get the squared distance between the centers of the two spheres.
		auto distance_squared = squared_euclidean_norm(a.get_center() - b.get_center());
		// Get the squared sum of the radiis of the two spheres.
		auto sum_of_radii = a.get_radius() + b.get_radius();
		auto sum_of_radii_squared = sum_of_radii * sum_of_radii;
		// If the squared distance beween the centers of the spheres
		// is smaller than or equal to the squared sum of the radii of the spheres ...
		if (distance_squared <= sum_of_radii_squared)
		{
			// ... the spheres intersect.
			return true;
		}
		// Otherwise they don't intersect.
		return false;
	}
}; // struct is_intersecting_functor

/// @brief Specialization of id::is_intersecting_functor.
/// Determines if a sphere and a point intersect.
/// @remark A sphere \f$A\f$ with the center $C$ and the radius $r$
/// and a point \f$P\f$ intersect if \f$|P - C| \leq r\f$ holds.
/// That condition is equivalent to the condition \f$|p - c|^2
/// \leq r^2\f$ but the latter is more efficient to test (two
/// multiplications vs. one square root).
template <typename P>
struct is_intersecting_functor<sphere<P>, P>
{
	bool operator()(const sphere<P>& a, const P& b) const
	{
		// Get the squared distance from the point to the center of the sphere.
		auto distance_squared = squared_euclidean_norm(a.get_center() - b);
		// Get the squared radius of the sphere.
		auto radius_squared = a.get_radius_squared();
		// If the squared distance beween the point and the center of the sphere
		// is smaller than or equal to the squared radius of the sphere ...
		if (distance_squared <= radius_squared)
		{
			// ... the sphere and the point intersect.
			return true;
		}
		// Otherwise the sphere and the point do not intersect.
		return false;
	}
}; // struct is_intersecting_functor

/// @brief Specialization of id::is_intersecting_functor.
/// Determines if a point and a sphere intersect.
/// @remark The method for determinating if a sphere and a point intersect is
/// commutative. By swapping the arguments that method can be reused to determine if a
/// point and a sphere intersect.
template <typename P>
struct is_intersecting_functor<P, sphere<P>>
{
	bool operator()(const P& a, const sphere<P>& b) const
	{ return is_intersecting(b, a); }
}; // struct is_intersecting_functor

} // namespace id
