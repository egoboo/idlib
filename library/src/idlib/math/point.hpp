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

/// @file idlib/math/point.hpp
/// @brief Points.
/// @author Michael Heilmann

#pragma once

#include "idlib/math/vector.hpp"

// Includes of functors idlib::point provides a plugin for.
#include "idlib/math/interpolate.hpp"
#include "idlib/math/enclose.hpp"
#include "idlib/math/is_enclosing.hpp"
#include "idlib/math/is_intersecting.hpp"
#include "idlib/math/translate.hpp"
#include "idlib/math/semantic_cast.hpp"

namespace idlib {

/// @ingroup math
/// @brief A point in the \f$n\f$-dimensional Euclidean space.
/// @remark Vectors are <a href=http://en.cppreference.com/w/cpp/concept/DefaultConstructible">DefaultConstructible</a>.
/// @tparam Vector the vector type
template <typename Vector>
struct point
{
public:
	/// @brief The vector type.
    using vector_type = Vector;

    /// @brief The scalar type.
    using scalar_type = typename vector_type::scalar_type;

    /// @brief Get the dimensionality.
	/// @return the dimensionality
    static constexpr size_t dimensionality()
	{ return vector_type::dimensionality(); }
	
    /// @brief The point type.
    using point_type = point<vector_type>;

	/// @brief The implementation type. 
	using implementation_type = idlib::arithmetic_tuple<scalar_type, vector_type::dimensionality(), zero_functor<scalar_type>>;

private:
	/// @brief The implementation.
    implementation_type m_implementation;

public:
    /// @brief Construct this point with the specified values.
    /// @param ...arguments the values
    /// @pre The number of specified values must be equal to the dimensionality of the point type.
    /// @pre Each specified value must be convertible into a scalar type value.
    template<typename ... Arguments,
             typename = std::enable_if_t<(sizeof...(Arguments)) == point_type::dimensionality() &&
                                         all_convertible<scalar_type, typename std::decay<Arguments>::type...>::value>>
    point(Arguments&& ... arguments)
        : m_implementation{ std::forward<Arguments>(arguments)...}
	{ static_assert(dimensionality() == sizeof...(arguments), "wrong number of arguments"); }

    /// @brief Copy-construct this point with the values of another point.
    /// @param other the other point
    point(const point_type& other) = default;

	/// @internal
	template <typename G, std::size_t...Is>
	static point_type generate(const G& g, std::index_sequence<Is...>)
	{ return point_type((g(Is))...); }
	
	/// @brief Create a point with the values of a sequence generator.
	/// @tparam G the generator type
	/// @param g the generator
	/// @return the point
    template <typename G>
    static point_type generate(const G& g)
	{ return generate(g, std::make_index_sequence<dimensionality()>{});	}
	
	/// @internal
	/// @brief Construct this point.
	/// @param other the implementation_type value
	point(const implementation_type& other) :
		m_implementation(other)
	{}

    /// @brief Default-construct this point.
    point() : m_implementation()
	{ /* Intentionally empty. */ }

	/// @{
	/// @brief Get the component value of the \f$x\f$ component.
	/// @return a reference to the component value of the \f$x\f$ component
	template <std::size_t LocalDimensionality = point_type::dimensionality()>
    std::enable_if_t<(LocalDimensionality >= 1), scalar_type>& x()
	{
        static_assert(point_type::dimensionality() >= 1, "cannot call for member x() with dimensionality less than 1");
        return m_implementation[0];
    }
	template <std::size_t LocalDimensionality = point_type::dimensionality()>
    const std::enable_if_t<(LocalDimensionality >= 1), scalar_type>& x() const
	{
        static_assert(point_type::dimensionality() >= 1, "cannot call for member x() with dimensionality less than 1");
        return m_implementation[0];
    }
	/// @}

	/// @{
	/// @brief Get the component value of the \f$y\f$ component.
	/// @return a reference to the component value of the \f$y\f$ component
	template <std::size_t LocalDimensionality = point_type::dimensionality()>
    std::enable_if_t<(LocalDimensionality >= 2), scalar_type>& y()
	{
        static_assert(point_type::dimensionality() >= 2, "cannot call for member y() with dimensionality less than 2");
        return m_implementation[1];
    }
	template <std::size_t LocalDimensionality = point_type::dimensionality()>
	const std::enable_if_t<(LocalDimensionality >= 2), scalar_type>& y() const
	{
        static_assert(point_type::dimensionality() >= 2, "cannot call for member y() with dimensionality less than 2");
        return m_implementation[1];
    }
	/// @}

	/// @{
	/// @brief Get the component value of the \f$z\f$ component.
	/// @return a reference to the component value of the \f$z\f$ component
	template <std::size_t LocalDimensionality = point_type::dimensionality()>
	std::enable_if_t<(LocalDimensionality >= 3), scalar_type>& z()
	{
        static_assert(point_type::dimensionality() >= 3, "cannot call for member z() with dimensionality less than 3");
        return m_implementation[2];
    }
	template <std::size_t LocalDimensionality = point_type::dimensionality()>
	const std::enable_if_t<(LocalDimensionality >= 3), scalar_type>& z() const
	{
        static_assert(point_type::dimensionality() >= 3, "cannot call for member z() with dimensionality less than 3");
        return m_implementation[2];
    }
	/// @}

public:
	bool operator==(const point_type& other) const
	{ return m_implementation == other.m_implementation; }
	
	bool operator!=(const point_type& other) const
	{ return m_implementation != other.m_implementation; }

	point_type& operator=(const point_type& other)
	{
		m_implementation = other.m_implementation;
		return *this;
	}
	

	point_type operator+(const vector_type& other) const
	{ return point_type(m_implementation + other.m_implementation); }

	point_type& operator+=(const vector_type& other)
	{ m_implementation += other.m_implementation; return *this; }

	
	point_type operator-(const vector_type& other) const
	{ return point_type(m_implementation - other.m_implementation); }
	
	point_type& operator-=(const vector_type& other)
	{ m_implementation -= other.m_implementation; return *this; }


	vector_type operator-(const point_type& other) const
	{ return vector_type(m_implementation - other.m_implementation); }


    scalar_type& operator[](size_t const& index)
	{ return m_implementation[index]; }

    const scalar_type& operator[](size_t const& index) const
	{ return m_implementation[index]; }

	
    scalar_type& operator()(size_t const& index)
	{ return m_implementation[index]; }

    const scalar_type& operator()(size_t const& index) const
	{ return m_implementation[index]; }
	
private:
	template <typename C, std::size_t...Is>
	bool equal_to(const point_type& other, const C& c, std::index_sequence<Is ...>) const
	{ return and_fold_expr()(c((*this)[Is], other[Is]) ...); }

public:
	/// @brief Generic component-wise equality test.
	/// @tparam C the type of the comparator. Defines a constant operator() receiving the component value of this and the other vector at an index. Returns @a true if they are equal and @a false otherwise.
	/// @param other the other vector
	/// @param c the comparator
	template <typename C>
	bool equal_to(const point_type& other, const C& c) const
	{ return equal_to(other, c, std::make_index_sequence<dimensionality()>{}); }
#if 0
	/**
     * @brief
     *  Get if this point equals another point.
     * @param other
     *  the other point
     * @param ulp
     *  see ScalarFieldType::notEqualUlp
     * @return
     *  @a true if this point equals the other point
     */
    bool equalsUlp(const MyType& other, const size_t& ulp) const {
        for (size_t i = 0; i < MyType::dimensionality(); ++i) {
            if (ScalarFieldType::notEqualULP(this->at(i), other.at(i), ulp)) {
                return false;
            }
        }
        return true;
    }
#endif

#if 0
    /**
     * @brief
     *  Get if this point equals another point.
     * @param other
     *  the other point
     * @param tolerance
     *  see ScalarFieldType::notEqualTolerance
     * @return
     *  @a true if this point equals the other point
     */
    bool equalsTolerance(const MyType& other, const ScalarType& tolerance) const {
        for (size_t i = 0; i < MyType::dimensionality(); ++i) {
            if (ScalarFieldType::notEqualTolerance(this->at(i), other.at(i), tolerance)) {
                return false;
            }
        }
        return true;
    }
#endif
}; // struct point

} // namespace idlib

namespace idlib {

template <typename Vector>
struct zero_functor<point<Vector>>
{
	using vector_type = Vector;

	using scalar_type = typename vector_type::scalar_type;

	using point_type = point<vector_type>;
	
	static constexpr size_t dimensionality() { return vector_type::dimensionality(); }

	auto operator()() const
	{ return point_type::generate(constant_generator<scalar_type>(zero<scalar_type>())); }

}; // struct zero_functor

/// @brief Specialization of idlib::enclose_functor enclosing a point in a point.
/// @detail The point \f$b\f$ enclosing a point \f$a\f$ is \f$a\f$ itself i.e. \f$b = a\f$.
/// @tparam Vector the vector type
template <typename Vector>
struct enclose_functor<point<Vector>, point<Vector>>
{
	using vector_type = Vector;
	using scalar_type = typename vector_type::scalar_type;
	using point_type = point<vector_type>;
	static constexpr size_t dimensionality() { return vector_type::dimensionality(); }

	auto operator()(const point_type& source) const
	{ return source; }

}; // struct enclose_functor

/// @brief Specialization of idlib::is_enclosing_functor.
/// Determines if a point contains another point.
/// @tparam Vector the vector type
template <typename Vector>
struct is_enclosing_functor<point<Vector>, point<Vector>>
{
	using vector_type = Vector;
	using scalar_type = typename vector_type::scalar_type;
	using point_type = point<vector_type>;	
	static constexpr size_t dimensionality() { return vector_type::dimensionality(); }
	
	bool operator()(const point_type& a, const point_type& b) const
	{
		for (size_t i = 0, n = dimensionality(); i < n; ++i)
		{
			if (a[i] != b[i])
			{
				return false;
			}
		}
		return true;
	}
}; // struct is_enclosing_functor

/// @brief Specialization of idlib::translate_functor.
/// Translates a point.
/// @tparam Vector the vector type
template <typename Vector>
struct translate_functor<point<Vector>, Vector>
{
	using vector_type = Vector;
	using scalar_type = typename vector_type::scalar_type;
	using point_type = point<vector_type>;
	static constexpr size_t dimensionality() { return vector_type::dimensionality(); }
	
	auto operator()(const point_type& x, const vector_type& t) const
	{
		return semantic_cast<point_type>(semantic_cast<vector_type>(x) + t);
	}
}; // struct translare_functor

/// @brief Specialization of idlib::is_intersecting_functor.
/// Determines if two points intersect.
/// @tparam Vector the vector type
template<typename Vector>
struct is_intersecting_functor<point<Vector>, point<Vector>>
{
	using vector_type = Vector;
	using scalar_type = typename vector_type::scalar_type;
	using point_type = point<vector_type>;
	static constexpr size_t dimensionality() { return vector_type::dimensionality(); }
	
	bool operator()(const point_type& a, const point_type& b) const
	{
		for (size_t i = 0, n = dimensionality(); i < n; ++i)
		{
			if (a[i] != b[i])
			{
				return false;
			}
		}
		return true;
	}
}; // struct is_intersecting_functor

/// @brief Specialization of idlib::max_element_functor for idlib::point<Vector> values.
template <typename Vector>
struct max_element_functor<point<Vector>>
{
	using point_type = point<Vector>;

	auto operator()(const point_type& p) const
	{ return impl(p); }
	
private:
	template<std::size_t...Is>
	auto impl(const point_type& p, std::index_sequence<Is...>) const
	{ return variadic::max((p[Is])...); }

	auto impl(const point_type& p) const
	{ return impl(p, std::make_index_sequence<point_type::dimensionality()>{}); }
	
}; // struct max_element_functor
	
/// @brief Specialization of idlib::min_element_functor for idlib::point<Vector> values.
template <typename Vector>
struct min_element_functor<point<Vector>>
{
	using point_type = point<Vector>;

	auto operator()(const point_type& p) const
	{ return impl(p); }

private:
	template<std::size_t...Is>
	auto impl(const point_type& p, std::index_sequence<Is...>) const
	{ return variadic::min((p[Is])...); }

	auto impl(const point_type& p) const
	{ return impl(p, std::make_index_sequence<point_type::dimensionality()>{}); }

}; // struct min_element_functor

/// @brief Specialization of idlib::interpolate_functor for linear interpolation of idlib::point<Vector>.
template <typename Vector>
struct lineary_interpolate_functor<point<Vector>, typename Vector::scalar_type, void>
{
	using vector_type = Vector;
    using point_type = idlib::point<vector_type>;
	
	using value_type = point_type;
    using parameter_type = typename point_type::scalar_type;

    auto operator()(const value_type& x, const value_type& y, parameter_type t) const
    { return (*this)(x, y, mu<parameter_type>(t)); }

    auto operator()(const value_type& x, const value_type& y, const mu<parameter_type>& mu) const
    { return semantic_cast<point_type>(lineary_interpolate(semantic_cast<vector_type>(x), semantic_cast<vector_type>(y), mu)); }

}; // struct interpolate_functor

template <typename V>
struct semantic_cast_functor<point<V>, V, void>
{
	auto operator()(const V& v) const
	{ return impl(v, std::make_index_sequence<V::dimensionality()>{}); }
	
private:
    template <std::size_t...Is>
    static decltype(auto) impl(const V& v, std::index_sequence<Is ...>)
	{ return point<V>(v[Is]...); }
	
}; // struct semantic_cast_functor

template <typename V>
struct semantic_cast_functor<V, point<V>, void>
{
	auto operator()(const point<V>& p) const
	{ return impl(p, std::make_index_sequence<point<V>::dimensionality()>{}); }
	
private:
    template <std::size_t...Is>
    static decltype(auto) impl(const point<V>& p, std::index_sequence<Is ...>)
	{ return V(p[Is]...); }
	
}; // struct semantic_cast_functor

/// @internal
template <typename V>
struct random_functor<point<V>>
{
	using point_type = point<V>;
	using scalar_type = typename point_type::scalar_type;
    static const interval<scalar_type> DEFAULT_INTERVAL;

    point_type operator()() const
    {
		rng rng;
        return (*this)(&rng, DEFAULT_INTERVAL);
    }
	
    point_type operator()(rng *rng) const
    {
        return (*this)(rng, DEFAULT_INTERVAL);
    }

    point_type operator()(const interval<scalar_type>& interval) const
    {
		rng rng;
        return (*this)(&rng, interval);
    }
    
	point_type operator()(rng *rng, const interval<scalar_type>& interval) const
    { 
		return impl(rng, interval, std::make_index_sequence<point_type::dimensionality()>{});
	}

private:
	template<std::size_t...Is>
	point_type impl(rng *rng, const interval<scalar_type>& interval, std::index_sequence<Is ...>) const
	{ return point_type(impl(rng, interval, Is) ...); }
	
	scalar_type impl(rng *rng, const interval<scalar_type>& interval, size_t i) const
	{ return rng->next(interval); }
}; // struct random_functor

template <typename V>
const interval<typename point<V>::scalar_type> random_functor<point<V>>::DEFAULT_INTERVAL(zero<typename point<V>::scalar_type>(), one<typename point<V>::scalar_type>());

} // namespace idlib
