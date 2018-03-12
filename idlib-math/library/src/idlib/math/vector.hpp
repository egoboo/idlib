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

/// @file idlib/math/vector.hpp
/// @brief \f$n\f$-dimensional vectors
/// @author Michael Heilmann

#pragma once

#include "idlib/math/arithmetic_array_1d.hpp"
#include "idlib/math/constant_generator.hpp"
#include "idlib/math/conditional_generator.hpp"
#include "idlib/utility/fold_expressions.hpp"
#include "idlib/variadic/min.hpp"
#include "idlib/variadic/max.hpp"

// Includes of functors idlib::vector provides a plugin for.
#include "idlib/numeric.hpp"
#include "idlib/math/euclidean_norm.hpp"
#include "idlib/math/manhattan_norm.hpp"
#include "idlib/math/maximum_norm.hpp"
#include "idlib/math/squared_euclidean_norm.hpp"
#include "idlib/math/cross_product.hpp"
#include "idlib/math/dot_product.hpp"
#include "idlib/math/normalize.hpp"
#include "idlib/math/min_element.hpp"
#include "idlib/math/max_element.hpp"
#include "idlib/math/zip_min.hpp"
#include "idlib/math/zip_max.hpp"
#include "idlib/numeric.hpp"

namespace idlib {

/// @ingroup math
/// @brief A vector.
/// @remark Vectors are <a href=http://en.cppreference.com/w/cpp/concept/DefaultConstructible">DefaultConstructible</a>.
/// @tparam Scalar the scalar type
/// @tparam Dimensionality the dimensionality
template <typename Scalar, size_t Dimensionality>
struct vector
{
public:
    /// @brief The scalar type.
    using scalar_type = Scalar;
    
    /// @brief Get the dimensionality.
    /// @return the dimensionality
    static constexpr size_t dimensionality()
    { return Dimensionality; }
    
    /// @brief The type of this template/template specialization.
    using vector_type = vector<scalar_type, Dimensionality>;

    /// @brief The implementation type.
    using implementation_type = arithmetic_array_1d<scalar_type, Dimensionality, zero_functor<scalar_type>>;

    /// @internal
    /// @brief The implementation.
    implementation_type m_implementation;

    /// @brief Construct this vector with the specified component values.
    /// @param arguments ... the component values
    /// @pre The number of specified element values must be equal to the dimensionality of the vector type.
    /// @pre Each specified component value must be convertible into a scalar type value.
    template<typename ... Arguments,
             typename = std::enable_if_t<(sizeof...(Arguments)) == vector_type::dimensionality() &&
                                         all_convertible<scalar_type, typename std::decay<Arguments>::type...>::value>>
    vector(Arguments&& ... arguments)
        : m_implementation(std::forward<Arguments>(arguments)...)
    { static_assert(dimensionality() == sizeof ... (arguments), "wrong number of arguments"); }

    /// @brief Copy-construct this vector with the values of another vector.
    /// @param other the other vector
    vector(const vector_type& other)
        : m_implementation(other.m_implementation)
    {}

    /// @internal
    /// @brief Construct this vector.
    /// @param other the implementation_type value
    vector(const implementation_type& other) :
        m_implementation(other)
    {}
    
    /// @brief Default-construct this vector.
    vector()
        : m_implementation()
    { /* Intentionally empty. */ }

public:
    /// @{
    /// @brief Get the component value of the \f$x\f$ component.
    /// @return a reference to the component value of the \f$x\f$ component
    template <size_t LocalDimensionality = vector_type::dimensionality()>
    std::enable_if_t<(LocalDimensionality >= 1), scalar_type>& x()
    {
        static_assert(vector_type::dimensionality() >= 1, "cannot call for member x() with dimensionality less than 1");
        return m_implementation(0);
    }
    template <size_t LocalDimensionality = vector_type::dimensionality()>
    const std::enable_if_t<(LocalDimensionality >= 1), scalar_type>& x() const
    {
        static_assert(vector_type::dimensionality() >= 1, "cannot call for member x() with dimensionality less than 1");
        return m_implementation(0);
    }
    /// @}

    /// @{
    /// @brief Get the component value of the \f$y\f$ component.
    /// @return a reference to the component value of the \f$y\f$ component
    template <size_t LocalDimensionality = vector_type::dimensionality()>
    scalar_type& y()
    {
        static_assert(vector_type::dimensionality() >= 2, "cannot call for member y() with dimensionality less than 2");
        return m_implementation(1);
    }
    template <size_t LocalDimensionality = vector_type::dimensionality()>
    const scalar_type& y() const
    {
        static_assert(vector_type::dimensionality() >= 2, "cannot call for member y() with dimensionality less than 2");
        return m_implementation(1);
    }
    /// @}
    
    /// @{
    /// @brief Get the component value of the \f$z\f$ component.
    /// @return a reference to the component value of the \f$z\f$ component
    template <size_t LocalDimensionality = vector_type::dimensionality()>
    std::enable_if_t<(LocalDimensionality >= 3), scalar_type>& z()
    {
        static_assert(vector_type::dimensionality() >= 3, "cannot call for member z() with dimensionality less than 3");
        return m_implementation(2);
    }
    template <size_t LocalDimensionality = vector_type::dimensionality()>
    const std::enable_if_t<(LocalDimensionality >= 3), scalar_type>& z() const
    {
        static_assert(vector_type::dimensionality() >= 3, "cannot call for member z() with dimensionality less than 3");
        return m_implementation(2);
    }
    /// @}

public:
    bool operator==(const vector_type& other) const
    { return m_implementation == other.m_implementation; }

    bool operator!=(const vector_type& other) const
    { return m_implementation != other.m_implementation; }

    vector_type& operator=(const vector_type& other)
    {
        m_implementation = other.m_implementation;
        return *this;
    }

private:
    template <typename C, size_t...Is>
    bool equal_to(const vector_type& other, const C& c, std::index_sequence<Is ...>) const
    { return and_fold_expr()(c((*this)[Is], other[Is]) ...); }

public:
    /// @brief Generic component-wise equality test.
    /// @tparam C the type of the comparator. Defines a constant operator() receiving the component value of this and the other vector at an index. Returns @a true if they are equal and @a false otherwise.
    /// @param other the other vector
    /// @param c the comparator
    template <typename C>
    bool equal_to(const vector_type& other, const C& c) const
    { return equal_to(other, c, std::make_index_sequence<Dimensionality>{}); }

#if 0

    /**
     * @brief
     *  Get if this vector equals another vector.
     * @param other
     *  the other vector
     * @param ulp
     *  see ScalarFieldType::notEqualUlp
     * @return
     *  @a true if this vector equals the other vector
     */
    bool equalsUlp(const MyType& other, const size_t& ulp) const {
        for (size_t i = 0; i < MyType::dimensionality(); ++i) {
            if (ScalarFieldType::notEqualUlp(this->at(i), other.at(i), ulp)) {
                return false;
            }
        }
        return true;
    }
#endif

#if 0
    /**
     * @brief
     *  Get if this vector equals another vector.
     * @param other
     *  the other vector
     * @param tolerance
     *  see ScalarFieldType::notEqualTolerance
     * @return
     *  @a true if this vector equals the other vector
     */
    bool equalsTolerance(const MyType& other, const ScalarType& tolerance) const {
        for (size_t i = 0; i < MyType::dimensionality(); ++i) {
            if (ScalarFieldType::notEqualToTolerance(this->at(i), other.at(i), tolerance)) {
                return false;
            }
        }
        return true;
    }
#endif

public:
    scalar_type& operator[](size_t const& index)
    { return m_implementation(index); }

    const scalar_type& operator[](size_t const& index) const
    { return m_implementation(index); }
    
    scalar_type& operator()(size_t const& index)
    { return m_implementation(index); }

    const scalar_type& operator()(size_t const& index) const
    { return m_implementation(index); }

public:
    vector_type& operator+=(const vector_type& other) { m_implementation += other.m_implementation; return *this; }
    vector_type operator+(const vector_type& other) const { auto t = m_implementation; t += other.m_implementation; return vector_type(t); }
    vector_type& operator-=(const vector_type& other) { m_implementation -= other.m_implementation; return *this; }
    vector_type operator-(const vector_type& other) const { auto t = m_implementation; t -= other.m_implementation; return vector_type(t); }
    vector_type& operator*=(const scalar_type& other) { m_implementation *= other; return *this; }
    vector_type operator*(const scalar_type& other) const { auto t = m_implementation; t *= other; return vector_type(t); }
    vector_type& operator/=(const scalar_type& other) { m_implementation /= other; return *this; }
    vector_type operator/(const scalar_type& other) const { auto t = m_implementation; t /= other; return vector_type(t); }
    vector_type operator-() const { return vector_type(-m_implementation); }
    vector_type operator+() const { return vector_type(+m_implementation); }

public:
    /// @brief Get if this vector is a unit vector.
    /// @return @a true if this vector is a unit vector, @a false otherwise
    /// @obsolete
    bool is_unit() const {
        auto t = squared_euclidean_norm(*this);
        return 0.99 < t && t < 1.01;
    }

    /// @brief Get if this vector is a zero vector.
    /// @return @a true if this vector is a zero vector, @a false otherwise
    /// @obsolete
    bool is_zero() const {
        auto t = squared_euclidean_norm(*this);
        return t < 0.01f;
    }

    /// @internal
    template <typename G, size_t...Is>
    static vector_type generate(const G& g, std::index_sequence<Is...>)
    {
        return vector_type((g(Is))...);
    }

    /// @brief Generate a vector with the values of a sequence generator.
    /// @tparam G the generator type
    /// @param g the generator
    /// @return the vector
    template <typename G>
    static vector_type generate(const G& g)
    {
        return generate(g, std::make_index_sequence<dimensionality()>{});
    }

    /// @brief Get a unit vector in which the component of the specified index is @a 1.
    /// @return the unit vector
    static vector_type unit(size_t index)
    {
        using a = constant_generator<scalar_type>;
        using b = constant_generator<scalar_type>;
        using c = conditional_generator<a, b>;
        return generate(c(index, a(one<scalar_type>()), b(zero<scalar_type>())));
    }

}; // struct vector

} // namespace idlib

namespace idlib {

template <typename Scalar, size_t Dimensionality>
struct zero_functor<vector<Scalar, Dimensionality>>
{
    using scalar_type = Scalar;
    using vector_type = vector<scalar_type, Dimensionality>;

    auto operator()() const
    { return vector_type::generate(constant_generator<scalar_type>(zero<scalar_type>())); }
};

template <typename Scalar, size_t Dimensionality>
struct one_functor<vector<Scalar, Dimensionality>>
{
    using scalar_type = Scalar;
    using vector_type = vector<scalar_type, Dimensionality>;

    auto operator()() const
    { return vector_type::generate(constant_generator<scalar_type>(one<scalar_type>())); }
};

/**
 * @brief Specialization of idlib::cross_product_functor for 3-dimensional vectors.
 * Computes the cross product of two 3-dimensional vectors.
 * @remark For any two vectors \f$v, w\f$ in a 3-dimensional vector space the cross product is defined as
 * \f[
 * \vec{u} \times \vec{v} =
 * \left[\begin{matrix}
 * v_y w_z - v_z w_y\\
 * v_z w_x - v_x w_z\\
 * v_x w_y - v_y w_x
 * \end{matrix}\right]
 * \f]
 * @remark
 * The cross product is distributive of vector addition i.e.
 * \f[
 * \vec{u} \times \left(\vec{v} + \vec{w}\right) = \vec{u} \times \vec{v} + \vec{u} \times \vec{w}
 * \f]
 * holds for any three vector \f$\vec{u},\vec{v},\vec{w}\in\mathbb{R}^3\f$.
 * This follows from
 * \f[
 *  &\vec{u} \times (\vec{v} + \vec{w})\\
 * =&\left[\begin{matrix}
 * u_y (v_z + w_z) - u_z (v_y + w_y)\\
 * u_z (v_x + w_x) - u_x (v_z + w_z)\\
 * u_x (v_y + w_y) - u_y (v_x + w_x)
 * \end{matrix}\right]\\
 * =&\left[\begin{matrix}
 * (u_y v_z - u_z v_y) + (u_y w_z - u_z w_y)\\
 * (u_z v_x - u_x v_z) + (u_z w_x - u_x w_z)\\
 * (u_x v_y - u_y v_x) + (u_x w_y - u_y w_x)
 * \end{matrix}\right]\\
 * =&\left[\begin{matrix}
 * u_y v_z - u_z v_y\\
 * u_z v_x - u_x v_z\\
 * u_x v_y - u_y v_x
 * \end{matrix}\right]
 * +
 * \left[\begin{matrix}
 * u_y w_z - u_z w_y\\
 * u_z w_x - u_x w_z\\
 * u_x w_y - u_y w_x
 * \end{matrix}\right]\\
 * =&\vec{u} \times \vec{v} + \vec{u} \times \vec{w}
 * \f]
 * @remark
 * The cross product is compatible with scalar multiplication i.e.
 * \f[
 * \left(s\vec{u}\right) \times \vec{v} = \vec{u} \times \left(s\vec{v}\right) = s \left(\vec{u} \times \vec{v}\right)
 * \f]
 * holds for any two vectors \f$\vec{u},\vec{v}\in\mathbb{R}^3\f$ and any scalar \f$s\in\mathbb{R}\f$.
 * This follows from
 * \f[
 *  \left(s\vec{u}\right) \times \vec{v}
 * =\left[\begin{matrix}
 * (s u_y) v_z - (s u_z) v_y\\
 * (s u_z) v_x - (s u_x) v_z\\
 * (s u_x) v_y - (s u_y) v_x
 * \end{matrix}\right]
 * =\left[\begin{matrix}
 * u_y (s v_z) - u_z (s v_y)\\
 * u_z (s v_x) - u_x (s v_z)\\
 * u_x (s v_y) - u_y (s v_x)
 * \end{matrix}\right]
 * =\vec{u} \times (s \vec{v})
 * \f]
 * and
 * \f[
 * \left(s\vec{u}\right) \times \vec{v}
 * =\left[\begin{matrix}
 * (s u_y) v_z - (s u_z) v_y\\
 * (s u_z) v_x - (s u_x) v_z\\
 * (s u_x) v_y - (s u_y) v_x
 * \end{matrix}\right]
 * = s \left[\begin{matrix}
 * u_y v_z - u_z v_y\\
 * u_z v_x - u_x v_z\\
 * u_x v_y - u_y v_x
 * \end{matrix}\right]
 * = s (\vec{u} \times \vec{v})
 * @remark
 * \f[
 * \vec{v} \times \vec{v} = \vec{0}
 * \f]
 * holds by
 * \f[
 * \vec{v} \times \vec{v} =
 * \left[\begin{matrix}
 * v_y v_z - v_z v_y\\
 * v_z v_x - v_x v_z\\
 * v_x v_y - v_y v_x
 * \end{matrix}\right]
 * = \vec{0}
 * \f]
 */
template <typename Scalar>
struct cross_product_functor<vector<Scalar, 3>>
{
    using vector_type = vector<Scalar, 3>;
    auto operator()(const vector_type& v, const vector_type& w) const
    {
        return
            vector_type
                (
                    v[1] * w[2] - v[2] * w[1],
                    v[2] * w[0] - v[0] * w[2],
                    v[0] * w[1] - v[1] * w[0]
                );
    }
};

template <typename Scalar, size_t Dimensionality>
struct dot_product_functor<vector<Scalar, Dimensionality>>
{
    using scalar_type = Scalar;
    using vector_type = vector<scalar_type, Dimensionality>;
    
    auto operator()(const vector_type& v, const vector_type& w) const
    { return impl(v, w); }

private:
    template <size_t...Is>
    static scalar_type impl(const vector_type& v, const vector_type& w, std::index_sequence<Is...>)
    { return idlib::plus_fold_expr()((v[Is] * w[Is])...); }

    static scalar_type impl(const vector_type& v, const vector_type& w)
    { return impl(v, w, std::make_index_sequence<vector_type::dimensionality()>{}); }
}; // struct dot_product_functor

template <typename Scalar, size_t Dimensionality>
struct squared_euclidean_norm_functor<vector<Scalar, Dimensionality>>
{
    using scalar_type = Scalar;
    using vector_type = vector<scalar_type, Dimensionality>;
    
    auto operator()(const vector_type& v) const
    { return impl(v); }
    
private:
    template <size_t...Is>
    static scalar_type impl(const vector_type& v, std::index_sequence<Is...>)
    { return idlib::plus_fold_expr()((v[Is] * v[Is])...); }

    static scalar_type impl(const vector_type& v)
    { return impl(v, std::make_index_sequence<vector_type::dimensionality()>{}); }

}; // struct squared_euclidean_norm_functor

template <typename Scalar, size_t Dimensionality>
struct euclidean_norm_functor<vector<Scalar, Dimensionality>>
{
    using scalar_type = Scalar;
    using vector_type = vector<scalar_type, Dimensionality>;
    
    auto operator()(const vector_type& v) const
    { return impl(v); }

private:
    template <size_t...Is>
    static scalar_type impl(const vector_type& v, std::index_sequence<Is...>)
    { return std::sqrt(idlib::plus_fold_expr()((v[Is] * v[Is])...)); }

    static scalar_type impl(const vector_type& v)
    { return impl(v, std::make_index_sequence<vector_type::dimensionality()>{}); }
    
}; // struct euclidean_norm_functor

template <typename Scalar, size_t Dimensionality>
struct manhattan_norm_functor<vector<Scalar, Dimensionality>>
{
    using scalar_type = Scalar;
    using vector_type = vector<scalar_type, Dimensionality>;
    
    auto operator()(const vector_type& v) const
    { return impl(v); }

private:
    template <size_t ... Is>
    static scalar_type impl(const vector_type& v, std::index_sequence<Is...>)
    { return idlib::plus_fold_expr()(std::abs(v[Is])...); }

    static scalar_type impl(const vector_type& v)
    { return impl(v, std::make_index_sequence<vector_type::dimensionality()>{}); }

}; // struct manhattan_norm_functor

/// @internal
/// @brief Specialization of idlib::maximum_norm_functor for idlib::vector<Scalar, Dimensionality>.
template <typename Scalar, size_t Dimensionality>
struct maximum_norm_functor<vector<Scalar, Dimensionality>>
{
    using scalar_type = Scalar;
    using vector_type = vector<scalar_type, Dimensionality>;
    
    auto operator()(const vector_type& v) const
    { return impl(v); }

private:
    template <size_t...Is>
    static scalar_type impl(const vector_type& v, std::index_sequence<Is...>)
    { return variadic::max(std::abs(v[Is])...); }

    static scalar_type impl(const vector_type& v)
    { return impl(v, std::make_index_sequence<vector_type::dimensionality()>{}); }

}; // struct maximum_norm_functor

/// @internal
/// @brief The result of a normalization of a vector.
/// If the old length is equal to the new length and the new length is @a 0
template <typename Scalar, size_t Dimensionality>
struct normalization_result
{
    using scalar_type = Scalar;
    using vector_type = vector<scalar_type, Dimensionality>;
    scalar_type m_length;
    vector_type m_vector;
    
    normalization_result(const vector_type& vector, const scalar_type& length)
        : m_vector(vector), m_length(length)
    {}
    
    scalar_type get_length() const
    { return m_length; }
    
    vector_type get_vector() const
    {
        if (m_length != zero<scalar_type>())
        { return m_vector; }
        else
        { throw std::domain_error("unable to normalize zero vector"); }
    }
    
    vector_type get_vector_or_default() const
    { return m_vector; }
};

/// @internal
/// @brief Specialization of idlib::normalize_functor for idlib::vector<Scalar, Dimensionality> values.
template <typename Scalar, size_t Dimensionality, typename Norm>
struct normalize_functor<vector<Scalar, Dimensionality>, Norm>
{
    using scalar_type = Scalar;
    using vector_type = vector<scalar_type, Dimensionality>;
    using norm_type = Norm;
    using result_type = normalization_result<scalar_type, Dimensionality>;

    auto operator()(const vector_type& v, const norm_type& n) const
    { return impl(v, n); }

private:
    static result_type impl(const vector_type& v, const norm_type& n)
    { 
        auto l = n(v);
        if (l == zero<scalar_type>())
        {
            return result_type(v, l);
        }
        else
        {
            return result_type(v / l, one<scalar_type>());
        }
    }

}; // struct normalize_functor

/// @internal
/// @brief Specialization of idlib::max_element_functor for idlib::vector<Scalar, Dimensionality> values.
template <typename Scalar, size_t Dimensionality>
struct max_element_functor<vector<Scalar, Dimensionality>,
                           std::enable_if_t<(Dimensionality > 0 )>>
{
    using vector_type = vector<Scalar, Dimensionality>;

    auto operator()(const vector_type& v) const
    { return impl(v); }
    
private:
    template<size_t...Is>
    auto impl(const vector_type& v, std::index_sequence<Is...>) const
    { return variadic::max((v[Is])...); }

    auto impl(const vector_type& v) const
    { return impl(v, std::make_index_sequence<vector_type::dimensionality()>{}); }
    
}; // struct max_element_functor

/// @internal
/// @brief Specialization of idlib::zip_max_functor for idlib::vector<Scalar, Dimensionality> values.
/// @remark
/// For two vectors \f$\vec{u},\vec{v}\in\mathbb{R}^n,n>0\f$ the zip max result is defined as
/// \f[
/// max\left(\vec{u},\vec{v}\right)=left(max(u_1,v_1),\ldots,max(u_n,v_n)\right)
/// \f]
template <typename Scalar, size_t Dimensionality>
struct zip_max_functor<vector<Scalar, Dimensionality>,
                       vector<Scalar, Dimensionality>,
                       std::enable_if_t<(Dimensionality > 0 )>>
{
    using vector_type = vector<Scalar, Dimensionality>;

    auto operator()(const vector_type& u, const vector_type& v) const
    { return impl(u, v); }

private:
    template<size_t...Is>
    auto impl(const vector_type& u, const vector_type& v, std::index_sequence<Is...>) const
    { return vector_type(std::max(u[Is], v[Is])...); }

    auto impl(const vector_type& u, const vector_type& v) const
    { return impl(u, v, std::make_index_sequence<vector_type::dimensionality()>{}); }

}; // struct zip_max_functor

/// @internal
/// @brief Specialization of idlib::min_element_functor for idlib::vector<Scalar, Dimensionality> values.
template <typename Scalar, size_t Dimensionality>
struct min_element_functor<vector<Scalar, Dimensionality>,
                           std::enable_if_t<(Dimensionality > 0 )>>
{
    using vector_type = vector<Scalar, Dimensionality>;

    auto operator()(const vector_type& v) const
    { return impl(v); }

private:
    template<size_t...Is>
    auto impl(const vector_type& v, std::index_sequence<Is...>) const
    { return variadic::min((v[Is])...); }

    auto impl(const vector_type& v) const
    { return impl(v, std::make_index_sequence<vector_type::dimensionality()>{}); }

}; // struct min_element_functor

/// @internal
/// @brief Specialization of idlib::zip_min_functor for idlib::vector<Scalar, Dimensionality> values.
/// @remark
/// For two vectors \f$\vec{u},\vec{v}\in\mathbb{R}^n,n>0\f$ the zip min result is defined as
/// \f[
/// min\left(\vec{u},\vec{v}\right)=left(min(u_1,v_1),\ldots,min(u_n,v_n)\right)
/// \f]
template <typename Scalar, size_t Dimensionality>
struct zip_min_functor<vector<Scalar, Dimensionality>,
                       vector<Scalar, Dimensionality>,
                       std::enable_if_t<(Dimensionality > 0 )>>
{
    using vector_type = vector<Scalar, Dimensionality>;

    auto operator()(const vector_type& u, const vector_type& v) const
    { return impl(u, v); }

private:
    template<size_t...Is>
    auto impl(const vector_type& u, const vector_type& v, std::index_sequence<Is...>) const
    { return vector_type(std::min(u[Is], v[Is])...); }

    auto impl(const vector_type& u, const vector_type& v) const
    { return impl(u, v, std::make_index_sequence<vector_type::dimensionality()>{}); }

}; // struct zip_min_functor

/// @internal
/// @brief Specialization of idlib::lineary_interpolate_functor for idlib::vector<Scalar, Dimensionality> values.
template <typename Scalar, size_t Dimensionality>
struct lineary_interpolate_functor<vector<Scalar, Dimensionality>,
                                   Scalar,
                                   std::enable_if_t<(Dimensionality > 0 )>>
{
    using parameter_type = Scalar;
    using value_type = vector<Scalar, Dimensionality>;

    auto operator()(const value_type& x, const value_type& y, parameter_type t) const
    { return (*this)(x, y, mu<parameter_type>(t)); }

    auto operator()(const value_type& x, const value_type& y, const mu<parameter_type>& mu) const
    { return x * mu.get_one_minus_mu() + y * mu.get_mu(); }

}; // struct lineary_interpolate_functor

/// @internal
/// @brief Specialization of idlb::random_functor for idlib::vector<Scalar, Dimensionality> values.
template <typename Scalar, size_t Dimensionality>
struct random_functor<vector<Scalar, Dimensionality>,
                      std::enable_if_t<(Dimensionality > 0)>>
{
    using scalar_type = Scalar;

    using vector_type = vector<scalar_type, Dimensionality>;
  
    vector_type operator()() const
    { return vector_type(random<typename vector_type::implementation_type>()); }
    
    vector_type operator()(rng *rng) const
    { return vector_type(random<typename vector_type::implementation_type>(rng)); }

    vector_type operator()(const interval<scalar_type>& interval) const
    { return vector_type(random<typename vector_type::implementation_type>(interval)); }
    
    vector_type operator()(rng *rng, const interval<scalar_type>& interval) const
    { return vector_type(random<typename vector_type::implementation_type>(rng, interval)); }

}; // struct random_functor

} // namespace idlib

namespace std {

template<typename Scalar, size_t Dimensionality, size_t...Is>
idlib::vector<Scalar, Dimensionality> abs(const idlib::vector<Scalar, Dimensionality>& v, index_sequence<Is...>)
{ return idlib::vector<Scalar, Dimensionality>(std::abs(v[Is])...); }

template<typename Scalar, size_t Dimensionality>
idlib::vector<Scalar, Dimensionality> abs(const idlib::vector<Scalar, Dimensionality>& v)
{ return abs(v, make_index_sequence<Dimensionality>{}); }

} // namespace std
