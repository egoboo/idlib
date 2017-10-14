// Copyright Michael Heilmann 2016, 2017.
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

/// @file idlib/math/one_zero.hpp
/// @brief Functionality to determine the zero and one values of set of values.
/// @detail Further reading "Why Not Specialize Function Templates?"
/// (http://www.gotw.ca/publications/mill17.htm).
/// @author Michael Heilmann

#pragma once

#include <type_traits>

namespace id {

/// @ingroup math
/// @brief The zero element of a domain of values (e.g. int, float, user-defined types, ...)
/// over which the operations addition and subtraction are defined has the properties
/// - \f$0 + x = x\f$
/// - \f$x + 0 = x\f$
/// - \f$0 \cdot x = 0\f$
/// - \f$x \cdot 0 = 0\f$
/// If in addition the negation operation is defined then in addition the property
/// - \f$-0 = 0\f$
/// holds.
/// @tparam T the type of the values
/// @tparam E SFINAE support
/// @remark Feel free to provide your own implementation.
/// Specialization for all integral types excluding @a bool are provided.
/// Specializations for @a float and @a double are provided.
template <typename T, typename E = void>
struct zero_functor;

/// @internal
template <typename T>
struct zero_functor<T, std::enable_if_t<std::is_integral<T>::value && !std::is_same<T, bool>::value>>
{
    constexpr T operator()() noexcept
    {
        return 0;
    }
};

/// @brief The one element of a domain of values (e.g. int, float, user-defined types, ...)
/// over which the operations addition and subtraction are defined has the properties
/// - \f$1 \cdot x = x\f$.
/// @tparam T the type of the values
/// @tparam E SFINAE support
/// @remark Feel free to provide your own implementation.
/// Specialization for all integral types excluding @a bool are provided.
/// Specializations for @a float and @a double are provided.
template <typename T, typename E = void>
class one_functor;

/// @internal
template <typename T>
class one_functor<T, std::enable_if_t<std::is_integral<T>::value && !std::is_same<T, bool>::value>>
{
public:
    constexpr T operator()() noexcept
    {
        return 1;
    }
};

/// @brief Get the zero value the type @a T.
/// @tparam T the type
/// @return the zero value of the type @a T
template <typename T>
decltype(auto) zero()
{
	return zero_functor<T>()();
}

/// @brief Get the one value of the type @a T.
/// @tparam T the type
/// @return the one value of the type @a T
template <typename T>
decltype(auto) one()
{
	return one_functor<T>()();
}

} // namespace id
