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

/// @file idlib/numeric/fraction.hpp
/// @brief Functor providing floating-point representations/approximations of important fractions.
/// @author Michael Heilmann

#pragma once

#include "idlib/platform.hpp"
#include <type_traits>

namespace idlib {

/// @brief Functor returning a representation of the fraction \f$\frac{n}{d}\f$.
/// @tparam T the type
/// @tparam N the nominator
/// @tparam D the denominator
/// @remark The following specializations are provided:
/// - single, double, N = 0, D any value
/// - single, double, N == D
/// - single, double, N any value, D = 1
/// - single, double, N = 1, D = 255
/// - single, double, N = 1, D = 256
/// - single, double, N = 1, D = 65535
/// - single, double, N = 1, D = 4
template <typename T, int N, int D, typename E = void>
struct fraction_functor;

template <typename T, int N, int D>
auto fraction()
{ return fraction_functor<T, N, D>()(); }

// \f$\frac{0}{d}\f$
template <int D>
struct fraction_functor<single, 0, D, std::enable_if_t<D != 0>>
{
    single operator()() const
    { return 0.0f; }
};
template <int D>
struct fraction_functor<double, 0, D, std::enable_if_t<D != 0>>
{
    single operator()() const
    { return 0.0; }
};

// \f$\frac{n}{d}, n == d\f$
template <int N, int D>
struct fraction_functor<single, N, D, std::enable_if_t<N == D>>
{
    single operator()() const
    { return 1.0f; }
};
template <int N, int D>
struct fraction_functor<double, N, D, std::enable_if_t<N == D>>
{
    double operator()() const
    { return 1.0; }
};

// \f$\frac{n}{1}\f$
template <int N>
struct fraction_functor<single, N, 1, void>
{
    single operator()() const
    { return static_cast<single>(N); }
};
template <int N>
struct fraction_functor<double, N, 1, void>
{
    double operator()() const
    { return static_cast<double>(N); }
};


/// \f$\frac{1}{255}\f$.
template <>
struct fraction_functor<single, 1, 255, void>
{
    single operator()() const
    { return 0.003921568627450980392156862745098f; }
};
template <>
struct fraction_functor<double, 1, 255, void>
{
    double operator()() const
    { return 0.003921568627450980392156862745098; }
};

/// \f$\frac{1}{256}\f$.
template <>
struct fraction_functor<single, 1, 256, void>
{
    single operator()() const
    { return 0.00390625f; }
};
template <>
struct fraction_functor<double, 1, 256, void>
{
    double operator()() const
    { return 0.00390625; }
};

// \f$\frac{1}{65535}\f$
template <>
struct fraction_functor<single, 1, 65535, void>
{
    single operator()() const
    { return 0.000015259021896696421759365224689097f; }
};
template <>
struct fraction_functor<double, 1, 65535, void>
{
    double operator()() const
    { return 0.000015259021896696421759365224689097; }
};

// \f$\frac{1}{4}\f$
template <>
struct fraction_functor<single, 1, 4, void>
{
    single operator()() const
    { return 0.25f; }
};
template <>
struct fraction_functor<double, 1, 4, void>
{
    double operator()() const
    { return 0.25; }
};

} // namespace idlib

namespace idlib {

/// @brief Functor returning a representation/approximation of \f$\pi\f$.
/// @remark Specializations for single and double are provided.
template <typename T>
struct pi_functor;

template <typename T>
auto pi()
{ return pi_functor<T>()(); }

template <>
struct pi_functor<single>
{
    single operator()() const
    { return 3.1415926535897932384626433832795f; }
};

template <>
struct pi_functor<double>
{
    double operator()() const
    { return 3.1415926535897932384626433832795; }
};

} // namespace idlib

namespace idlib {
    
/// @brief Functor returning a representation/approximation of \f$\frac{1}{\pi}\f$.
/// @remark Specializations for single and double are provided.
template <typename T>
struct inv_pi_functor;

template <typename T>
auto inv_pi()
{ return inv_pi_functor<T>()(); }

template <>
struct inv_pi_functor<single>
{
    single operator()() const
    { return 0.31830988618379067153776752674503f; }
};

template <>
struct inv_pi_functor<double>
{
    double operator()() const
    { return 0.31830988618379067153776752674503; }
};

} // namespace idlib

namespace idlib {
    
/// @brief Functor returning a representation/approximation of \f$2\pi\f$.
/// @remark Specializations for single and double are provided.
template <typename T>
struct two_pi_functor;

template <typename T>
auto two_pi()
{ return two_pi_functor<T>()(); }

template <>
struct two_pi_functor<single>
{
    single operator()() const
    { return 6.283185307179586476925286766559f; }
};

template <>
struct two_pi_functor<double>
{
    double operator()() const
    { return 6.283185307179586476925286766559; }
};

} // namespace idlib

namespace idlib {
    
/// @brief Functor returning a representation/approximation of \f$\frac{1}{2\pi}\f$.
/// @remark Specializations for single and double are provided.
template <typename T>
struct inv_two_pi_functor;

template <typename T>
auto inv_two_pi()
{ return inv_two_pi_functor<T>()(); }

template <>
struct inv_two_pi_functor<single>
{
    single operator()() const
    { return 0.15915494309189533576888376337251f; }
};

template <>
struct inv_two_pi_functor<double>
{
    double operator()() const
    { return 0.15915494309189533576888376337251; }
};

} // namespace idlib

namespace idlib {

/// @brief Functor returning a representation/approximation of \f$\frac{\pi}{d}\f$.
/// @remark Specializations for
/// - single, double, d = 2
/// - single, double, d = 4
/// are provided.
template <typename T, int D>
struct pi_over_functor;

template <typename T, int D>
auto pi_over()
{ return pi_over_functor<T, D>()(); }

/// \f$\frac{\pi}{2}\f$
template <>
struct pi_over_functor<single, 2>
{
    single operator()() const
    { return 1.5707963267948966192313216916398f; }
}; // struct pi_over_functor
template <>
struct pi_over_functor<double, 2>
{
    double operator()() const
    { return 1.5707963267948966192313216916398; }
}; // struct pi_over_functor

/// \f$\frac{\pi}{4}\f$
template <>
struct pi_over_functor<single, 4>
{
    single operator()() const
    { return 0.78539816339744830961566084581988f; }
}; // struct pi_over_functor
template <>
struct pi_over_functor<double, 4>
{
    double operator()() const
    { return 0.78539816339744830961566084581988; }
}; // struct pi_over_functor

} // namespace idlib

namespace idlib {

/// @brief Functor returning a representation/approximation of \f$\sqrt{2}\f$.
/// @remark Specializations for single and double are provided.
template <typename T>
struct sqrt_two_functor;

template <typename T>
auto sqrt_two()
{ return sqrt_two_functor<T>()(); }

template <>
struct sqrt_two_functor<single>
{
    single operator()() const
    { return 1.4142135623730950488016887242097f; }
}; // struct sqrt_two_functor

template <>
struct sqrt_two_functor<double>
{
    double operator()() const
    { return 1.4142135623730950488016887242097; }
}; // struct sqrt_two_functor

} // namespace idlib

namespace idlib {

/// @brief Functor returning a representation/approximation of \f$\frac{1}{\sqrt{2}}\f$.
/// @remark Specializations for single and double are provided.
template <typename T>
struct inv_sqrt_two_functor;

template <typename T>
auto inv_sqrt_two()
{ return inv_sqrt_two_functor<T>()(); }

template <>
struct inv_sqrt_two_functor<single>
{
    single operator()() const
    { return 0.70710678118654752440084436210485f; }
}; // struct inv_sqrt_two_functor

template <>
struct inv_sqrt_two_functor<double>
{ 
    double operator()() const
    { return 0.70710678118654752440084436210485; }
}; // struct inv_sqrt_two_functor

} // namespace idlib
