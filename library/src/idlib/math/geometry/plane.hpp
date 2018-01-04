// Copyright Michael Heilmann 2016, 2017, 2018.
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

/// @file idlib/math/geometry/plane.hpp
/// @brief Planes in three-dimensional space.
/// @author Michael Heilmann

#pragma once

#include "idlib/math/point.hpp"
#include "idlib/crtp.hpp"
#include "idlib/math/floating_point.hpp"

#include "idlib/math/dot_product.hpp"

namespace id {

template <typename P>
struct plane;

/// @brief A plane.
/// @detail A plane can be defined in terms of a unit normal vector \f$\hat{n}\f$ and a distance from the origin.
/// The set of points of the plane is then defined as
/// \f$\{ X | \hat{n} \cdot X + d = 0 \}\f$
/// which is called the normal-distance form of a plane.
template <typename S>
struct plane<point<vector<S,3>>> : public equal_to_expr<plane<point<vector<S,3>>>>
{
public:
	/// @brief The point type of this plane type.
	using point_type = point<vector<S,3>>;

	/// @brief The vector type of this plane type.
	using vector_type = typename point_type::vector_type;

	/// @brief The scalar type of this plane type.
	using scalar_type = typename point_type::scalar_type;

	/// @brief The dimensionality of this point type.
	/// @return the dimensionality
	static constexpr size_t dimensionality()
	{ return vector_type::dimensionality(); }

	/// @brief Construct this plane with the default values of a plane.
	/// @remark The default values of a plane are a normal \f$\hat{n} = \left(0,0,1\right)\f$ and,0,1) and a distance from the origin \f$d = 0\f$.
	plane()
		: m_normal(zero<scalar_type>(), zero<scalar_type>(), one<scalar_type>()),
		  m_distance(zero<scalar_type>())
	{}

	/// @brief Create a plane from a plane equation \f$a + b + c + d = 0\f$.
	/// @param a, b, c, d the plane equation
	/// @remark
	/// Given a plane equation \f$a + b + c + d = 0\f$, the normal-distance form
	/// \f$(\hat{n}',d')\f$ is defined as \f$\hat{n}' = \frac{\vec{n}}{|\vec{n}'|}\f$
	/// and \f$d' = \frac{d}{|\vec{n}'|}\f$ where \f$\vec{n}' = (a,b,c)\f$.
	plane(const scalar_type& a, const scalar_type& b, const scalar_type& c, const scalar_type& d)
		: m_normal(a, b, c), m_distance(d)
	{
		auto l = euclidean_norm(m_normal);
		if (zero<scalar_type>() == l)
		{ throw std::domain_error("normal vector is zero vector"); }
		auto j = one<scalar_type>() / l;
		m_normal *= j;
		m_distance *= j;
	}

	/// @brief Construct a plane from three non-collinear points.
	/// @param a, b, c the points
	/// @throw std::domain_error the points are collinear
	/// @remark
	/// Assume \f$a\f$, \f$b\f$ and \f$c\f$ are not collinear. Let \f$u = b - a\f$,
	/// \f$v = c - a\f$, \f$n = u \times v\f$, \f$\hat{n} = \frac{n}{|n|}\f$ and
	/// \f$d = -\left(\hat{n} \cdot a\right)\f$.
	/// We show that \f$a\f$, \f$b\f$ and \f$c\f$ are on the plane given by the
	/// equation \f$\hat{n} \cdot p + d = 0\f$. To show this for \f$a\f$,
	/// rewrite the plane equation to
	/// \f{eqnarray*}{
	/// \hat{n} \cdot p  + -(\hat{n} \cdot a) = 0\\
	/// \f}
	/// shows for \f$p=a\f$ immediatly that \f$a\f$ is on the plane.
	/// @remark
	/// To show that \f$b\f$ and \f$c\f$ are on the plane,
	/// the plane equation is rewritten yet another time using
	/// the bilinearity property of the dot product and
	/// the definitions of \f$d\f$ and \f$\hat{n}\f$:
	/// \f{align*}{
	///  &\hat{n} \cdot p + -(\hat{n} \cdot a) \;\;\text{Def. of } d\\
	/// =&\hat{n} \cdot p + \hat{n} \cdot (-a) \;\;\text{Bilinearity of the dot product}\\
	/// =&\hat{n} \cdot (p - a)                \;\;\text{Bilinearity of the dot product}\\
	/// =&\frac{n}{|n|} \cdot (p - a)          \;\;\text{Def. of } \hat{n}\\
	/// =&(\frac{1}{|n|}n) \cdot (p - a)       \;\;\\
	/// =&\frac{1}{|n|}(n \cdot (p - a))       \;\;\text{Compatibility of the dot product w. scalar multiplication}\\
	/// =&n \cdot (p - a)                      \;\;\\
	/// =&(u \times v) \cdot (p - a)           \;\;\text{Def. of } n
	/// \f}
	/// Let \f$p = b\f$ then
	/// \f{align*}{
	///  &(u \times v) \cdot (b - a)           \;\text{Def. of } u\\
	/// =&(u \times v) \cdot u\\
	/// =&0
	/// \f}
	/// or let \f$p = c\f$ then
	/// \f{align*}{
	///  &(u \times v) \cdot (c - a)           \;\text{Def. of } u\\
	/// =&(u \times v) \cdot v\\
	/// =&0
	/// \f}
	/// as \f$u \times v\f$ is orthogonal to both \f$u\f$ and \f$v\f$.
	/// This shows that \f$b\f$ and \f$c\f$ are on the plane.
	plane(const point_type& a, const point_type& b, const point_type& c)
	{
		auto u = b - a;
		if (u == zero<vector_type>())
		{ throw std::domain_error("b = a"); }
		auto v = c - a;
		if (u == zero<vector_type>())
		{ throw std::domain_error("c = a"); }
		m_normal = cross_product(u, v);
		auto r = normalize(m_normal, euclidean_norm_functor<vector_type>{});
		if (r.get_length() == zero<scalar_type>())
		{
			/* u x v = 0 is only possible for u, v != 0 if u = v and thus b = c. */
			throw std::domain_error("b = c");
		}
		m_normal = r.get_vector();
		m_distance = -dot_product(m_normal, semantic_cast<vector_type>(a));
	}

	/// @brief Construct a plane with a point and a normal.
	/// @param p the point
	/// @param n the normal
	/// @throw std::domain_error the normal vector is the zero vector
	/// @remark The plane normal is normalized if necessary.
	/// @remark
	/// Let \f$X\f$ be the point and \f$\vec{n}\f$ the unnormalized plane normal, then the plane equation is given by
	/// \f{align*}{
	/// \hat{n} \cdot P + d = 0, \hat{n} = \frac{\vec{n}}{|\vec{n}|}, d = -\left(\hat{n} \cdot X\right)
	/// \f}
	/// \f$X\f$ is on the plane as
	/// \f{ align* }{
	///   &\hat{n} \cdot X + d\\
	/// = &\hat{ n } \cdot X + -(\hat{ n } \cdot X)\\
	/// = &\hat{ n } \cdot X - \hat{ n } \cdot X\\
	/// = &0
	/// \f}
	plane(const point_type& p, const vector_type& n)
		: m_normal(n), m_distance(zero<scalar_type>())
	{
		auto r = normalize(m_normal, euclidean_norm_functor<vector_type>{});
		if (r.get_length() == zero<scalar_type>())
		{ throw std::domain_error("normal vector is zero vector"); }
		m_normal = r.get_vector();
		m_distance = -dot_product(m_normal, semantic_cast<vector_type>(p));
	}

	/// @brief Construct a plane from a direction vector and a distance from the origin.
	/// @param the direction vector
	/// @param d the distance from the origin
	/// @post
	/// Given an axis \f$\vec{t}\f$ and a distance from the origin \f$d\f$
	/// the plane equation is given by
	/// \f{align*}{
	/// \hat{n} \cdot p + d = 0, \hat{n} = \frac{\vec{t}}{|\vec{t}|}
	/// \f}
	/// @throw std::domain_error the translation axis is the zero vector
	plane(const vector_type& t, const scalar_type& d)
		: m_normal(t), m_distance(d)
	{
		auto x = normalize(t, euclidean_norm_functor<vector_type>{});
		if (x.get_length() == zero<scalar_type>())
		{ throw std::domain_error("axis vector is zero vector"); }
		m_normal = x.get_vector();
	}

	plane(const plane&) = default;
	plane& operator=(const plane&) = default;

	/// @brief Get the plane normal of this plane.
	/// @return the plane normal of this plane
	const vector_type& get_normal() const
	{ return m_normal; }

	/// @brief Get the distance of this plane from the origin.
	/// @return the distance of this plane from the origin
	const scalar_type& get_distance() const
	{ return m_distance; }

	/// @brief Get the distance of a point from this plane.
	/// @param point the point
	/// @return
	/// the distance of the point from the plane.
	/// The point is in the positive (negative) half-space of the plane if the distance is positive (negative).
	/// Otherwise the point is on the plane.
	/// @remark
	/// Let \f$\hat{n} \cdot P + d = 0\f$ be a plane and \f$v\f$ be some point.
	/// We claim that \f$d'=\hat{n} \cdot v + d\f$ is the signed distance of the point \f$v\f$ from the plane.
	/// To show this, assume \f$v\f$ is not in the plane.
	/// Then there exists a single point \f$u\f$ on the plane which is closest to \f$v\f$ such that \f$v\f$ can
	/// be expressed by translating \f$u\f$ along the plane normal by the signed distance \f$d'\f$ from
	/// \f$u\f$ to \f$v\f$ i.e. \f$v = u + d' \hat{n}\f$. Obviously,
	/// if \f$v\f$ is in the positive (negative) half-space of the plane, then
	/// \f$d'>0\f$ (\f$d' < 0\f$). We obtain now
	/// \f{align*}{
	///   &\hat{n} \cdot v + d\\
	/// = &\hat{n} \cdot (u + d' \hat{n}) + d\\
	/// = &\hat{n} \cdot u + d' (\hat{n} \cdot \hat{n}) + d\\
	/// = &\hat{n} \cdot u + d' + d\\
	/// = &\hat{n} \cdot u + d + d'\\
	/// \f}
	/// However, as \f$u\f$ is on the plane
	/// \f{align*}{
	/// = &\hat{n} \cdot u + d + d'\\
	/// = &d'
	/// \f}
	scalar_type distance(const point_type& point) const
	{ return dot_product(get_normal(), semantic_cast<vector_type>(point)) + get_distance(); }

	/// @brief Get a point on this plane.
	/// @return a point on this plane
	/// @remark
	/// The point \f$X = (-d) \hat{n}\f$ is guaranteed to be on the plane.
	/// To see that, insert \f$X\f$ into the plane equation:
	/// \f{align*}{
	/// \hat{n} \cdot X + d = \hat{n} \cdot \left[(-d) \hat{n}\right] + d
	/// = (-d) \left(\hat{n} \cdot \hat{n}\right] + d
	/// \f}
	/// As \f$\hat{n}\f$ is a unit vector
	/// \f{align*}{
	///  &(-d) \left[\hat{n} \cdot \hat{n}\right] + d\\
	/// =&-d + d\\
	/// =&0
	/// \f}
	vector_type get_point() const
	{ return get_normal() * (-get_distance()); }

	// CRTP
	bool equal_to(const plane& other) const
	{
		return get_distance() == other.get_distance()
			&& get_normal() == other.get_normal();
	}

protected:
	struct cookie {};
	friend struct translate_functor<plane, vector_type>;
	plane(cookie cookie, const vector_type& n, const scalar_type& d)
		: m_normal(n), m_distance(d) {}

private:

	/// @brief The plane normal.
	/// @invariant The plane normal is a unit vector.
	vector_type m_normal;

	/// @brief The distance of the plane from the origin.
	scalar_type m_distance;

}; // struct plane

/// @brief Specialization of id::enclose_functor enclosing a plane in a plane.
/// @detail The plane \f$b\f$ enclosing a plane \f$a\f$ is \f$a\f$ itself i.e. \f$b = a\f$.
/// @tparam P the point type of this plane
template <typename P>
struct enclose_functor<plane<P>, plane<P>>
{
	auto operator()(const plane<typename P::scalar_type>& source) const
	{ return source; }
}; // struct enclose_functor

/// @brief Specialization of id::translate_functor.
/// Translates a plane.
/// @remark
/// The first (slow) method to compute the translation of a plane \f$\hat{n} \cdot P + d = 0\f$
/// is to compute a point on the plane, translate the point, and compute from the new point and
/// and the old plane normal the new plane:
/// To translate a plane \f$\hat{n} \cdot P + d = 0\f$, compute a point on the plane
/// \f$X\f$ (i.e. a point \f$\hat{n} \cdot X + d = 0\f$) by
/// \f{align*}{
/// X = (-d) \cdot \hat{n}
/// \f}
/// Translate the point \f$X\f$ by \f$\vec{t}\f$ into a new point \f$X'\f$:
/// \f{align*}{
/// X' = X + \vec{t}
/// \f}
/// and compute the new plane
/// \f{align*}{
/// \hat{n} \cdot P + d' = 0, d' = -\left(\hat{n} \cdot X'\right)
/// \f}
/// @remark
/// The above method is not the fastest method. Observing that the old and the new plane equation only
/// differ by \f$d\f$ and \f$d'\f$, a faster method of translating a plane can be devised by computing
/// \f$d'\f$ directly. Expanding \f$d'\f$ gives
/// \f{align*}{
/// d' =& -\left(\hat{n} \cdot X'\right)\\
///    =& -\left[\hat{n} \cdot \left((-d) \cdot \hat{n} + \vec{t}\right)\right]\\
///    =& -\left[(-d) \cdot \hat{n} \cdot \hat{n} + \hat{n} \cdot \vec{t}\right]\\
///    =& -\left[-d + \hat{n} \cdot \vec{t}\right]\\
///    =& d - \hat{n} \cdot \vec{t}
/// \f}
/// The new plane can then be computed by
/// \f{align*}{
/// \hat{n} \cdot P + d' = 0, d' = d - \hat{n} \cdot \vec{t}
/// \f}
/// @tparam P the point type of the plane
template <typename P>
struct translate_functor<plane<P>, typename P::vector_type>
{
	auto operator()(const plane<P>& x, const typename P::vector_type& t) const
	{ return plane<P>(x.get_normal(), x.get_distance() - dot_product(x.get_normal(), t)); }
}; // struct translate_functor

} // namespace id
