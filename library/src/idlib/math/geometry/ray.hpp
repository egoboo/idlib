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

/// @file idlib/math/geometry/ray.hpp
/// @brief Rays.
/// @author Michael Heilmann

#pragma once

#include "idlib/math/point.hpp"
#include "idlib/crtp.hpp"
#include "idlib/math/floating_point.hpp"

namespace idlib {

/// @brief A ray has an origin point \f$O\f$ and an unit direction vector \$\vec{d}\f$.
/// The set of points of a ray is given by \f$\left\{ O + t \vec{d} | t \in \subseteq \mathbb{R}_{\geq 0} \right\}$.
template <typename P>
struct ray : public equal_to_expr<ray<P>>
{
public:
	/// @brief The point type of this ray type.
	using point_type = P;

	/// @brief The vector type of this ray type.
	using vector_type = typename point_type::vector_type;

	/// @brief The scalar type of this ray type.
	using scalar_type = typename point_type::scalar_type;
	
	/// @brief The dimensionality of this ray type.
	/// @return the dimensionality
	static constexpr size_t dimensionality()
	{ return vector_type::dimensionality(); }

    /// @brief Construct this ray with the specified origin point \f$O\f$ and axis vector \f$\vec{a}\f$.
    /// @param origin the origin point \f$O\f$
    /// @param direction the direction vector \f$\vec{d}\f$
    /// @throw idlib::runtime_error if the direction vector \f$\vec{d}\f$ is the zero vector
    ray(const point_type& origin, const vector_type& direction)
        : m_origin(origin), m_direction(direction)
	{
        auto result = normalize(m_direction, euclidean_norm_functor<vector_type>{});
        if (result.get_length() == zero<scalar_type>())
		{ throw runtime_error(__FILE__, __LINE__, "direction vector is zero vector"); }
        m_direction = result.get_vector();
    }

	ray(const ray&) = default;
	ray& operator=(const ray&) = default;

    /// @brief Get the origin of this ray.
    /// @return the origin of this ray
    const point_type& get_origin() const
	{ return m_origin; }

	/// @brief Set the origin of this ray.
	/// @param origin the origin
	void set_origin(const point_type& origin)
	{ m_origin = origin; }

    /// @brief Get the unit direction vector of this ray.
    /// @return the unit direction vector of this ray
    const vector_type& get_direction() const
	{ return m_direction; }

	/// @brief Set the direction vector of this ray.
	/// @param direction the direction vector
	/// @throw idlib::runtime_error the direction vecotr is the zero vector
	void set_direction(const vector_type& direction)
	{
		auto result = normalize(m_direction, euclidean_norm_functor<vector_type>{});
		if (result.get_length() == zero<scalar_type>())
		{ throw runtime_error(__FILE__, __LINE__, "direction vector is zero vector"); }
		m_direction = result.get_vector();
	}

public:
    // CRTP
    bool equal_to(const ray& other) const
    {
        return m_origin == other.m_origin
            && m_direction == other.m_direction;
    }

private:
	/// @brief The origin of this ray.
	point_type m_origin;

	/// @brief The direction of this ray.
	vector_type m_direction;

}; // struct ray

/// @brief Specialization of idlib::enclose_functor.
/// Encloses a ray in a ray.
/// @detail The ray \f$b\f$ enclosing a ray \f$a\f$ is \f$a\f$ itself i.e. \f$b = a\f$.
/// @tparam P the point type of the rays
template <typename P>
struct enclose_functor<ray<P>, ray<P>>
{
	auto operator()(const ray<P>& source) const
	{ return source; }
}; // struct enclose_functor

/// @brief Specialization of idlib::translate_functor.
/// Translates a ray.
/// @tparam P the point type of the ray
template <typename P>
struct translate_functor<ray<P>, typename P::vector_type>
{
	auto operator()(const ray<P>& x, const typename P::vector_type& t) const
	{ return ray<P>(x.get_origin() + t, x.get_direction()); }
}; // struct translate_functor

} // namespace idlib
