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

/// @file idlib/math/interpolate.hpp
/// @brief Functionality to interpolate between values.
/// @author Michael Heilmann

#pragma once

#include "idlib/math/one_zero.hpp"
#include "idlib/utility/out_of_bounds_error.hpp"

namespace id {

/// @ingroup math
/// @brief Representation of \f$\mu\f$ (mu).
/// @detail The greek letter \f$\mu\f$ (mu) is the name for the interpolation parameter in interpolation.
/// @detail Objects of type @a mu are caches and contracts at the same time:
/// - they are caches as they store two values of which one is one minus the other value (cache)
/// - they guarantee that both values are within the bounds of \f$[0,1]\f$
/// @remark Specializations for @a float and @a double are provided.
template <typename T, typename E = void>
class mu;

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
        if (mu < zero<T>()) throw out_of_bounds_error(__FILE__, __LINE__, "mu is smaller than zero<T>");
        else if (mu > one<T>()) throw out_of_bounds_error(__FILE__, __LINE__, "mu is greater than one<T>");
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

} // namespace id
