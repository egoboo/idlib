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

/// @file idlib/numeric/mu_floating_point.hpp
/// @brief Type representing of values within the bounds of idlib::zero and idlib::one.
/// @author Michael Heilmann

#pragma once

#if !defined(IDLIB_PRIVATE) || IDLIB_PRIVATE != 1
#error(do not include directly, include `idlib/numeric.hpp` instead)
#endif

#pragma push_macro("IDLIB_PRIVATE")
#undef IDLIB_PRIVATE
#define IDLIB_PRIVATE (1)

#include "idlib/numeric/mu.hpp"
#include "idlib/numeric/one_floating_point.hpp"
#include "idlib/numeric/zero_floating_point.hpp"
#include "idlib/exception.hpp"

#undef IDLIB_PRIVATE
#pragma pop_macro("IDLIB_PRIVATE")

namespace idlib {

template <typename T>
class mu<T, std::enable_if_t<std::is_floating_point<T>::value>>
{
private:
    T m_one_minus_mu;
    T m_mu;
public:
    /// @brief Construct this mu.
    /// @param mu the float value this mu represents
    /// @throw out_of_bounds_error @a mu is smaller than @a 0 or greater than @a 1
    mu(T mu) :
        m_mu(mu)
    {
        if (mu < zero<T>()) throw argument_out_of_bounds_error(__FILE__, __LINE__, "mu is smaller than zero<T>");
        else if (mu > one<T>()) throw argument_out_of_bounds_error(__FILE__, __LINE__, "mu is greater than one<T>");
        m_one_minus_mu = one<T>() - mu;
    }

    /// @brief Copy-construct this mu.
    /// @param mu the other mu
    /// @return this mu
    mu(const mu& other) noexcept :
        m_mu(other.m_mu),
        m_one_minus_mu(other.m_one_minus_mu)
    {}

    /// @brief Copy-assign this mue from another mu.
    /// @param other the other mu
    /// @return this mu
    mu& operator=(const mu& other) noexcept
    {
        m_mu = other.m_mu;
        m_one_minus_mu = other.m_one_minus_mu;
        return *this;
    }

    /// @brief Get the value of \f$\mu\f$.
    /// @return the value of \f$mu\f$
    const T& get_mu() const noexcept
    {
        return m_mu;
    }

    /// @brief Get the value of \f$1 - \mu\f$.
    /// @return the value of \f$1 - \mu\f$
    const T& get_one_minus_mu() const noexcept
    {
        return m_one_minus_mu;
    }

}; // class mu

} // namespace idlib
