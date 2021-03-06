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

/// @file idlib/math/angle-degrees-radians-turns.hpp
/// @brief Implementation of floating-point angles in degrees/radians/turns.
/// @author Michael Heilmann

#pragma once

#include "idlib/math/angle.hpp"
#include "idlib/math/angle_units.hpp"
#include "idlib/numeric.hpp"
#include "idlib/semantic_cast.hpp"

#include <cmath>

namespace idlib {

namespace internal {

/// Convert an angle in a unit into an equivalent angle in another unit.
template <typename TargetType, typename TargetUnit, 
          typename SourceType, typename SourceUnit>
struct convert;

// Conversion between the same unit and the same type (identity).
template <typename T, typename U>
struct convert<T, U, T, U>
{
    T operator()(T x) const
    { return x; }
};

// Conversion between Degrees and Radians.

/// The conversion of an angle \f$\alpha\f$ in degrees into an equivalent angle
/// \f$\beta\f$ in radians is defined by \f$\beta = \alpha \frac{2\pi}{360}\f$.
template <typename T>
struct convert<T, idlib::radians, 
               T, std::enable_if_t<std::is_floating_point<T>::value, idlib::degrees>>
{ 
    T operator()(T x) const
    { return x * (idlib::pi<T>() / idlib::fraction<T, 180, 1>()); }
}; // struct convert

/// The conversion of an angle \f$\alpha\f$ in radians into an equivalent angle
/// \f$\beta\f$ in degrees is defined by \f$\beta = \alpha \frac{360}{2\pi}\f$.
template <typename T>
struct convert<T, idlib::degrees, 
               T, std::enable_if_t<std::is_floating_point<T>::value, idlib::radians>>
{
    T operator()(T x) const
    { return x * (idlib::fraction<T, 180, 1>() * idlib::inv_pi<T>()); }
}; // struct convert

// Conversion between Degrees and Turns.

/// The conversion of an angle \f$\alpha\f$ in degrees into an equivalent angle
/// \f$\beta\f$ in turns is defined as \f$\beta = \alpha \frac{1}{360}\f$.
template <typename T>
struct convert<T, idlib::turns,
               T, std::enable_if_t<std::is_floating_point<T>::value, idlib::degrees>>
{
    T operator()(T x) const
    { return x * (idlib::one<T>() / idlib::fraction<T, 360, 1>()); }
}; // struct convert

/// The conversion of an angle \f$\alpha\f$ in turns into an equivalent angle
/// \f$\beta\f$ in degrees is defined as \f$\beta = \alpha 360\f$.
template <typename T>
struct convert<T, idlib::degrees,
               T, std::enable_if_t<std::is_floating_point<T>::value, idlib::turns>>
{
    T operator()(T x) const
    { return x * idlib::fraction<T, 360, 1>(); }
}; // struct convert

// Conversion between Radians and Turns.

/// The conversion of an angle \f$\alpha\f$ in radians into an equivalent angle
/// \f$\beta\f$ in turns is defined as \$\beta = \alpha \frac{1}{2 \pi}\f$.
template <typename T>
struct convert<T, idlib::turns, 
               T, std::enable_if_t<std::is_floating_point<T>::value, idlib::radians>>
{
    T operator()(T x) const
    { return x * idlib::inv_two_pi<float>(); }
}; // struct convert

/// The conversion of an angle \f$\alpha\f$ in turns into an equivalent angle
/// \f$\beta\f$ in radians is defined as \$\beta = \alpha 2 \pi\f$.
template <typename T>
struct convert<T, idlib::radians,
               T, std::enable_if_t<std::is_floating_point<T>::value, idlib::turns>>
{
    T operator()(T x) const
    { return x * idlib::two_pi<float>(); }
}; // struct convert

} // namespace internal

/// @brief Specialization of idlib::angle where Syntax is a floating point value
/// and @a Semantics is one of idlib::degrees, idlib::radians, or idlib::turns.
/// @tparam Semantics the type of the semantics (how are the values interpreted)
template <typename Syntactics, typename Semantics>
struct angle<Syntactics, Semantics,
             std::enable_if_t<(std::is_same<Semantics, degrees>::value ||
                               std::is_same<Semantics, radians>::value ||
                               std::is_same<Semantics, turns>::value) &&
                               std::is_floating_point<Syntactics>::value>>
{
    using syntactics_type = Syntactics;
    using semantics_type = Semantics;

    /// Construct this angle with its default values.
    angle() :
        m_angle(zero<syntactics_type>())
    {}
    
    /// Construct this angle with the specified values.
    explicit angle(syntactics_type angle) :
        m_angle(angle)
    {}

    angle(const angle& other) = default;
    angle& operator=(const angle& other) = default;

    bool operator==(const angle& other) const
    { return m_angle == other.m_angle; }

    bool operator!=(const angle& other) const
    { return m_angle != other.m_angle; }

    bool operator<(const angle& other) const
    { return m_angle < other.m_angle; }

    bool operator<=(const angle& other) const
    { return m_angle <= other.m_angle; }

    bool operator>(const angle& other) const
    { return m_angle > other.m_angle; }

    bool operator>=(const angle& other) const
    { return m_angle >= other.m_angle; }


    angle operator+(const angle& other) const
    {
        auto t = *this;
        t += other;
        return t;
    }

    angle operator+=(const angle& other)
    {
        m_angle += other.m_angle;
        return *this;
    }


    angle operator-(const angle& other) const
    {
        auto t = *this;
        t -= other;
        return t;
    }

    angle operator-=(const angle& other)
    {
        m_angle -= other.m_angle;
        return *this;
    }


    angle operator*(syntactics_type other) const
    { return angle(m_angle * other); }

    const angle& operator*=(syntactics_type other)
    {
        m_angle *= other;
        return *this;
    }


    angle operator/(syntactics_type other) const
    { return angle(m_angle * other); }

    const angle& operator/=(syntactics_type other)
    {
        m_angle /= other;
        return *this;
    }

public:
    syntactics_type get_value() const
    { return m_angle; }

    explicit operator syntactics_type() const
    { return m_angle; }

private:
    syntactics_type m_angle;

}; // struct angle

template <typename Syntactics, typename Semantics>
inline angle<Syntactics, Semantics> operator*(Syntactics x, const angle<Syntactics, Semantics>& y)
{ return angle<Syntactics, Semantics>(x * y.get_value()); }

template <typename Syntactics, typename Semantics>
inline angle<Syntactics, Semantics> operator/(Syntactics x, const angle<Syntactics, Semantics>& y)
{ return angle<Syntactics, Semantics>(x / y.get_value()); }

// conversion from/to degrees
template <typename Syntactics>
struct semantic_cast_functor<angle<Syntactics, degrees>, angle<Syntactics, turns>,
                             std::enable_if_t<std::is_floating_point<Syntactics>::value>>
{
    auto operator()(const angle<Syntactics, turns>& x) const
    {
        return angle<Syntactics, degrees>(internal::convert<Syntactics, degrees,
                                                            Syntactics, turns>()(x.get_value()));
    }
};

template <typename Syntactics>
struct semantic_cast_functor<angle<Syntactics, degrees>, angle<Syntactics, radians>,
                             std::enable_if_t<std::is_floating_point<Syntactics>::value>>
{
    angle<Syntactics, degrees> operator()(const angle<Syntactics, radians>& x) const
    {
        return angle<Syntactics, degrees>(internal::convert<Syntactics, degrees,
                                                            Syntactics, radians>()(x.get_value()));
    }
};

// conversion from/to turns
template <typename Syntactics>
struct semantic_cast_functor<angle<Syntactics, turns>, angle<Syntactics, degrees>,
                             std::enable_if_t<std::is_floating_point<Syntactics>::value>>
{
    auto operator()(const angle<Syntactics, degrees>& x) const
    {
        return angle<Syntactics, turns>(internal::convert<Syntactics, turns,
                                                          Syntactics, degrees>()(x.get_value()));
    }
};

template <typename Syntactics>
struct semantic_cast_functor<angle<Syntactics, turns>, angle<Syntactics, radians>,
                             std::enable_if_t<std::is_floating_point<Syntactics>::value>>
{
    angle<Syntactics, turns> operator()(const angle<Syntactics, radians>& x) const
    {
        return angle<Syntactics, turns>(internal::convert<Syntactics, turns,
                                                          Syntactics, radians>()(x.get_value()));
    }
};

// conversion from/to radians
template <typename Syntactics>
struct semantic_cast_functor<angle<Syntactics, radians>, angle<Syntactics, degrees>,
                             std::enable_if_t<std::is_floating_point<Syntactics>::value>>
{
    auto operator()(const angle<Syntactics, degrees>& x) const
    {
        return angle<Syntactics, radians>(internal::convert<Syntactics, radians,
                                                            Syntactics, degrees>()(x.get_value()));
    }
};

template <typename Syntactics>
struct semantic_cast_functor<angle<Syntactics, radians>, angle<Syntactics, turns>,
                             std::enable_if_t<std::is_floating_point<Syntactics>::value>>
{
    auto operator()(const angle<Syntactics, turns>& x) const
    {
        return angle<Syntactics, radians>(internal::convert<Syntactics, radians,
                                                            Syntactics, turns>()(x.get_value()));
    }
};

/// @brief Specialization of idlib::lineary_interpolate_functor for lineary interpolation of idlib::angle<Syntactics, Semantics> values.
template <typename Syntactics, typename Semantics>
struct lineary_interpolate_functor<angle<Syntactics, Semantics>, Syntactics,
                                   std::enable_if_t<std::is_floating_point<Syntactics>::value>>
{
    using angle_type = idlib::angle<Syntactics, Semantics>;
    
    using parameter_type = Syntactics;
    using value_type = angle_type;

    auto operator()(const value_type& x, const value_type& y, parameter_type t) const
    { return (*this)(x, y, mu<parameter_type>(t)); }

    auto operator()(const value_type& x, const value_type& y, const mu<parameter_type>& mu) const
    { return angle_type(x.get_value() * mu.get_one_minus_mu() + y.get_value() * mu.get_mu()); }

}; // struct lineary_interpolate_functor

} // namespace idlib

namespace std {

template <typename Syntactics, typename Semantics>
std::enable_if_t<std::is_floating_point<Syntactics>::value, Syntactics>
sin(const idlib::angle<Syntactics, Semantics>& x)
{
    using T = idlib::angle<Syntactics, idlib::radians>;
    return sin(idlib::semantic_cast<T>(x).get_value());
}

template <typename Syntactics, typename Semantics>
std::enable_if_t<std::is_floating_point<Syntactics>::value, Syntactics>
cos(const idlib::angle<Syntactics, Semantics>& x)
{
    using T = idlib::angle<Syntactics, idlib::radians>;
    return cos(idlib::semantic_cast<T>(x).get_value());
}

template <typename Syntactics, typename Semantics>
std::enable_if_t<std::is_floating_point<Syntactics>::value, Syntactics>
tan(const idlib::angle<Syntactics, Semantics>& x)
{
    using T = idlib::angle<Syntactics, idlib::radians>;
    return tan(idlib::semantic_cast<T>(x).get_value());
}

template <typename Syntactics, typename Semantics>
std::enable_if_t<std::is_floating_point<Syntactics>::value,
                 idlib::angle<Syntactics, Semantics>> 
abs(const idlib::angle<Syntactics, Semantics>& x)
{ return idlib::angle<Syntactics, Semantics>(std::abs(x.get_value())); }

} // namespace std
