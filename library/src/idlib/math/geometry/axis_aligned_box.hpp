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

/// @file idlib/math/geometry/axis_aligned_box.hpp
/// @brief Axis aligned boxes.
/// @author Michael Heilmann

#pragma once

#include "idlib/math/point.hpp"
#include "idlib/crtp.hpp"
#include "idlib/math/floating_point.hpp"

namespace idlib {

/// @brief An axis aligned box (abbrevated as AAB).
/// An AAB in \f$\mathbb{R}^n, n > 0\f$ can be defined in terms of
/// a minimal point \f$\min\f$ and
/// a maximal point \f$\max\f$ such that
/// \f$\min_i \leq \max_i\f$ for all \f$0 \leq i < n\f$.
/// @tparam P the point type of this axis aligned box type
template <typename P>
struct axis_aligned_box : public equal_to_expr<axis_aligned_box<P>>
{
public:
	/// @brief The point type of this axis aligned box type.
	using point_type = P;

	/// @brief The vector type of this axis aligned box type.
	using vector_type = typename P::vector_type;

	/// @brief The scalar type of this axis aligned box type.
	using scalar_type = typename P::scalar_type;

	/// @brief The dimensionality of this axis aligned box type.
	/// @return the dimensionality
	static constexpr size_t dimensionality()
	{ return vector_type::dimensionality(); }
    
	/// @brief Construct this axis aligned box with its default values.
    /// @remark The default values of an axis aligned box are a minimal point of \f$\vec{0}\f$ and a maximal point \f$\vec{0}\f$.
    axis_aligned_box()
        : m_min(), m_max()
	{}

    /// @brief Construct this axis aligned box from the given points.
    /// @param a,b the points
	/// @remarks
    /// Given the points \f$a\f$ and \f$b\f$, the minimum \f$min\f$
    /// and the maximum \f$max\f$ of the axis aligned box are given
    /// by
    /// \f{align*}{
    /// min_i = \min\left(a_i,b_i\right) \;\; max_i = \max\left(a_i,b_i\right)
    /// \f}
    axis_aligned_box(const point_type& a, const point_type& b)
        : m_min(a), m_max(b)
	{
        for (size_t i = 0; i < dimensionality(); ++i)
		{
            if (m_min[i] > m_max[i])
			{
                std::swap(m_min[i], m_max[i]);
            }
        }
    }
	
	axis_aligned_box(const axis_aligned_box&) = default;
	axis_aligned_box& operator=(const axis_aligned_box&) = default;

    /// @brief Get the minimum.
    /// @return the minimum
    const point_type& get_min() const
	{ return m_min; }

    /// @brief Get the maximum.
    /// @return the maximum
    const point_type& get_max() const
	{ return m_max; }

    /// @brief Get the center of this axis aligned box.
    /// @return the center
    point_type get_center() const
	{ 
		static const auto TWO = idlib::one<scalar_type>() + idlib::one<scalar_type>();
		return get_min() + get_size() / TWO;
    }

	/// @brief Get the size of this axis aligned box.
	/// @return the size
	vector_type get_size() const
	{ return get_max() - get_min(); }

    /// @brief Assign this axis aligned box the join if itself with another axis aligned box.
    /// @param other the other axis aligned box
    /// @post The result of the join was assigned to this axis aligned box.
    void join(const axis_aligned_box& other)
	{
        for (size_t i = 0; i < dimensionality(); ++i)
		{
            m_min[i] = std::min(m_min[i], other.m_min[i]);
            m_max[i] = std::max(m_max[i], other.m_max[i]);
        }
    }

    /// @brief Get if this axis aligned box is degenerated.
	/// @return @a true if this axis aligned is degenerated, @a false otherwise
    /// @remark
    /// An axis aligned box is called "degenerated along an axis" if its
    /// minimum equals its maximum along that axis. If an axis aligned
    /// box is "degenerated" along all axes, then the AABB is called
    /// "degenerated".
    bool is_degenerated() const
	{ return m_min == m_max; }

	// CRTP
    bool equal_to(const axis_aligned_box& other) const
	{
        return get_min() == other.get_min()
            && get_max() == other.get_max();
    }

protected:
	struct cookie {};
	friend struct idlib::translate_functor<axis_aligned_box, vector_type>;
	axis_aligned_box(cookie cookie, const point_type& min, const point_type& max)
		: m_min(min), m_max(max)
	{}

private:
	/// @brief The minimum along each axis.
	/// @invariant The i-th component of the minimum is smaller than or equal to the i-th component of the maximum.
	point_type m_min;

	/// @brief The maximum along each axis.
	/// @invariant The i-th component of the maximum is greater than or equal to the i-th component of the minimum.
	point_type m_max;

}; // struct axis_aligned_box

/// @brief Specialization of idlib::enclose_functor enclosing an axis aligned box into an axis aligned box.
/// @details The axis aligned box \f$b\f$ enclosing an axis aligned box \f$a\f$ is \f$a\f$ itself i.e. \f$a = b\f$.
/// @tparam P the point type of the axis aligned box types
template <typename P>
struct enclose_functor<axis_aligned_box<P>, axis_aligned_box<P>>
{
	auto operator()(const axis_aligned_box<P>& source) const
	{ return source; }
}; // struct enclose_functor

/// @brief Specialization of idlib::is_enclosing_functor.
/// Determines if an axis aligned box encloses a point.
/// @tparam P the point type of the geomtries
template <typename P>
struct is_enclosing_functor<axis_aligned_box<P>, P>
{
	bool operator()(const axis_aligned_box<P>& a, const P& b) const
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
/// Determines if an axis aligned box contains another axis aligned box.
/// @remark An axis aligned box \f$A\f$ does <em>not</em> contain an axis aligned box \f$B\f$
/// if for at least one axis \$k\f$ at least one of the following conditions is true:
/// - \f$A_{min_k} > B_{min_k}\f$
/// - \f$A_{max_k} < B_{max_k}\f$
/// Otherwise \f$A\f$ contains \f$B\f$.
/// This is a variant of the Separating Axis Theorem (aka SAT).
/// @tparam P the point type of the axis aligned box types
template <typename P>
struct is_enclosing_functor<axis_aligned_box<P>, axis_aligned_box<P>>
{
	bool operator()(const axis_aligned_box<P>& a, const axis_aligned_box<P>& b) const
	{
		for (size_t i = 0; i < P::dimensionality(); ++i)
		{
			// If a is the axis-aligned bounding box that is supposed to contain the
			// axis-aligned bounding box b, then a does not contain b if along some axis
			// - the maximum of a is smaller than the maximum of b, or
			if (a.get_max()[i] < b.get_max()[i]) return false;
			// - the minimum of a is greater than the minimum of b.
			if (a.get_min()[i] > b.get_min()[i]) return false;
		}
		return true;
	}
}; // struct is_enclosing_functor

/// @brief Specialization of idlib::translate_functor.
/// Translates an axis aligned box.
/// @tparam P the point type of the axis aligned box type
template <typename P>
struct translate_functor<axis_aligned_box<P>, typename P::vector_type>
{
	auto operator()(const axis_aligned_box<P>& x,
		            const typename P::vector_type& t) const
	{
		return axis_aligned_box<P>(typename axis_aligned_box<P>::cookie(),
			                       x.get_min() + t, x.get_max() + t);
	}
}; // struct translate_functor

/// @brief Specialization of idlib::is_intersecting_functor.
/// Determines wether two axis aligned boxes intersect.
/// @remark Two axis aligned boxes \f$A\f$ and \f$B\f$ do <em>not</em> intersect
/// if for at least one axis \f$k\f$ at least one of the following conditions is true:
/// - \f$A_{min_k} > B_{max_k}\f$
/// - \f$A_{max_k} < B_{min_k}\f$
/// Otherwise \f$A\f$ and \f$B\f$ intersect.
/// This is a variant of the Separating Axis Theorem (aka SAT).
/// @tparam P the point type of the axis aligned box types
template<typename P>
struct is_intersecting_functor<axis_aligned_box<P>, axis_aligned_box<P>>
{
	bool operator()(const axis_aligned_box<P>& a, const axis_aligned_box<P>& b) const
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
/// Determines if an axis aligned bounding box and a point intersect.
/// @remark A point \f$P\f$ and an axis aligned bounding box \f$A\f$ do <em>not</em> intersect
/// if for at least one axis \f$k\f$ at least one of the following conditions is true:
/// - \f$P_k > A_{max_k}\f$
/// - \f$P_k < A_{min_k}\f$
/// Otherwise \f$P\f$ and \f$A\f$ intersect.
/// @tparam P the point type of the axis aligned box types
template <typename P>
struct is_intersecting_functor<axis_aligned_box<P>, P>
{
	bool operator()(const axis_aligned_box<P>& a, const P& b) const
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
/// Determines if a point and an axis aligned box intersect.
/// @remark The method for determinating if an axis aligned box and a pointer intersect is
/// commutative. By swapping the arguments that method can be reused to determine if a
/// point and an axis aligned box intersect.
/// @tparam P the point type of the axis aligned box types
template <typename P>
struct is_intersecting_functor<P, axis_aligned_box<P>>
{
	bool operator()(const P& a, const axis_aligned_box<P>& b) const
	{ return is_intersecting(b, a); }
}; // struct is_intersecting_functor

} // namespace idlib
