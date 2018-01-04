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

#pragma once

#include "idlib/utility/fold_expressions.hpp"
#include "idlib/math/operators.hpp"
#include "idlib/math/one_zero.hpp"
#include <algorithm>

namespace id {
	
/// @brief The following templates obtain the relation of one the boolean values in a variadic template argument list @a size_t compile-time constants.
template <bool...> struct bool_pack;

/// @brief Provide a member constant value <tt>value</tt>.
/// That constant is equal to <tt>true</tt> if all boolean values in the variadic template argument list are true.
/// Otherwise it is equal to <tt>false</tt>.
template <bool... v>
using all_true  = std::is_same<bool_pack<true, v...>, bool_pack<v..., true>>;

/// @brief Provide a mamber constant value <tt>value</tt>.
/// That constant is equal to <tt>true</tt> if all boolean values in the variadic template argument list are true.
/// Otherwise it is equal to <tt>false</tt>.
template <bool... v>
using all_false = std::is_same<bool_pack<false, v...>, bool_pack<v..., false>>;

/// @brief Provide member constant value <tt>value</tt>.
/// That constant is equal to <tt>true</tt> if the argument types in the variadic template argument list are convertible into the specified target type.
/// Otherwise it is equal to <tt>false</tt>.
template <typename TargetType, typename ... ArgumentTypes>
using all_convertible = all_true<std::is_convertible<ArgumentTypes, TargetType>::value ...>;

/// @brief An arithmetic tuple.
/// @tparam E the element type
/// @tparam S the size i.e. the number of element values
/// A partial specialization for the size of @a 0 is provided.
/// @tparam Z a functor type returning the zero element value
template <typename E, std::size_t S, typename Z>
struct arithmetic_tuple
{
public:
	/// @brief The element type.
	using element_type = E;

	/// @brief Get the size.
	/// @return the size
	constexpr static std::size_t size() noexcept
	{ return S; }

private:	
	/// @brief The elements.
	E m_elements[S];
	
public:
	/// @brief Default construct with the zero element value.
	arithmetic_tuple()
	{ std::fill_n(&(m_elements[0]), S, Z()()); }
	
	/// @brief Construct this tuple with the specified element values.
	/// @param first, ... rest the element values
    /// @pre The number of specified element values must be equal to the size of the tuple type.

	template<typename A, typename ... As,
             typename =  std::enable_if_t<((1 + sizeof...(As)) == S) &&
										  (all_convertible<E, typename std::decay<A>::type>::value && all_convertible<E, typename std::decay<As>::type...>::value)>>
	arithmetic_tuple(A&& a, As&& ... as) :
        m_elements{ static_cast<E>(a), static_cast<E>(as) ... }
    { static_assert(S == 1 + sizeof ... (as), "wrong number of arguments"); }

	arithmetic_tuple(const arithmetic_tuple& other) = default;
	arithmetic_tuple(arithmetic_tuple&& other) = default;
	arithmetic_tuple& operator=(const arithmetic_tuple& other) = default;
	arithmetic_tuple& operator=(arithmetic_tuple&& other) = default;
	
private:
	template <std::size_t ... Is>
	static arithmetic_tuple<E, S, Z> unary_minus(const arithmetic_tuple& a, std::index_sequence<Is...>)
	{ return arithmetic_tuple<E, S, Z>((-a.m_elements[Is])...); }
	
	template <std::size_t ... Is>
	static arithmetic_tuple<E, S, Z> unary_plus(const arithmetic_tuple& a, std::index_sequence<Is...>)
	{ return arithmetic_tuple<E, S, Z>((+a.m_elements[Is])...); }
	
public:
    arithmetic_tuple<E, S, Z> operator+() const
    { return unary_plus(*this, std::make_index_sequence<S>{}); }

    arithmetic_tuple<E, S, Z> operator-() const
    { return unary_minus(*this, std::make_index_sequence<S>{}); }
	
private:
	template <std::size_t ... Is>
	static arithmetic_tuple<E, S, Z> add(const arithmetic_tuple& a, const arithmetic_tuple& b, std::index_sequence<Is...>)
	{ return arithmetic_tuple<E, S, Z>((a.m_elements[Is] + b.m_elements[Is])...); }

public:
	arithmetic_tuple<E, S, Z>& operator += (const arithmetic_tuple& other)
	{
		(*this) = add(*this, other, std::make_index_sequence<S>{});
		return *this;
	}
	
	arithmetic_tuple<E, S, Z> operator+(const arithmetic_tuple& other) const
	{ return add(*this, other, std::make_index_sequence<S>{}); }
	
private:
	template <std::size_t ... Is>
	static arithmetic_tuple<E, S, Z> subtract(const arithmetic_tuple& a, const arithmetic_tuple& b, std::index_sequence<Is...>)
	{ return arithmetic_tuple<E, S, Z>((a.m_elements[Is] - b.m_elements[Is])...); }

public:
	arithmetic_tuple<E, S, Z>& operator -= (const arithmetic_tuple& other)
	{
		(*this) = subtract(*this, other, std::make_index_sequence<S>{});
		return *this;
	}
	
	arithmetic_tuple<E, S, Z> operator-(const arithmetic_tuple& other) const
	{ return subtract(*this, other, std::make_index_sequence<S>{}); }
	
private:
	template <std::size_t...Is>
	static arithmetic_tuple<E, S, Z> multiply(const arithmetic_tuple& a, const element_type& s, std::index_sequence<Is...>)
	{ return arithmetic_tuple<E, S, Z>((a.m_elements[Is] * s)...); }

public:
	arithmetic_tuple<E, S, Z>& operator *= (const element_type& other)
	{
		(*this) = multiply(*this, other, std::make_index_sequence<S>{});
		return *this;
	}
	
	arithmetic_tuple<E, S, Z> operator*(const element_type& other) const
	{ return multiply(*this, other, std::make_index_sequence<S>{}); }
	
private:
	template <std::size_t...Is>
	static arithmetic_tuple<E, S, Z> divide(const arithmetic_tuple& a, const element_type& s, std::index_sequence<Is...>)
	{ return arithmetic_tuple<E, S, Z>((a.m_elements[Is] / s)...); }

public:
	arithmetic_tuple<E, S, Z>& operator /= (const element_type& other)
	{
		(*this) = divide(*this, other, std::make_index_sequence<S>{});
		return *this;
	}

	arithmetic_tuple<E, S, Z> operator/(const element_type& other) const
	{ return divide(*this, other, std::make_index_sequence<S>{}); }
	
private:
	template <std::size_t...Is>
	static bool equal_to(const arithmetic_tuple& a, const arithmetic_tuple& b, std::index_sequence<Is...>)
	{ 
		return id::and_fold_expr()((a.m_elements[Is] == b.m_elements[Is])...);
	}		
	
public:
	bool operator==(const arithmetic_tuple& other) const
	{ return equal_to(*this, other, std::make_index_sequence<S>{}); }

private:
	template <std::size_t...Is>
	static bool not_equal_to(const arithmetic_tuple& a, const arithmetic_tuple& b, std::index_sequence<Is...>)
	{
		return id::or_fold_expr()((a.m_elements[Is] != b.m_elements[Is])...);
	}
	
public:
	bool operator!=(const arithmetic_tuple& other) const
	{ return not_equal_to(*this, other, std::make_index_sequence<S>{}); }
	
public:
	/// @{
	/// @brief Get the tuple element at the specified index.
	/// @param index the index
	/// @return the tuple element at the specified index
	/// @pre The index is within bounds.
	element_type& at(size_t const& index)
	{ return m_elements[index]; }

	element_type& operator[](size_t const& index)
	{ return m_elements[index]; }

	const element_type& at(size_t const& index) const
	{ return m_elements[index]; }

	const element_type& operator[](size_t const& index) const
	{ return m_elements[index]; }
	
	/// @}
	
private:
	template <typename G, std::size_t...Is>
	static arithmetic_tuple<E, S, Z> generate(const G& g, std::index_sequence<Is...>)
	{ return arithmetic_tuple<E, S, Z>((g(Is))...); }

public:
	template <typename G>
	static arithmetic_tuple<E, S, Z> generate(const G& g)
	{ return generate(g, std::make_index_sequence<S>{}); }
	
}; // struct arithmetic_tuple

/// @brief Partial specialization of id::arithmetic_tuple for a size if @a 0.
/// @tparam E the element type
/// @tparam Z a functor returning the zero element value
template <typename E, typename Z>
struct arithmetic_tuple<E, 0, Z>
{
public:
	/// @brief The element type.
	using element_type = E;

	/// @brief Get the size.
	/// @return the size
	constexpr static std::size_t size() noexcept
	{ return 0; }

public:
	/// @brief Default construct this arithmetic tuple.
	arithmetic_tuple()
	{}

	arithmetic_tuple(const arithmetic_tuple& other) = default;
	arithmetic_tuple(arithmetic_tuple&& other) = default;
	arithmetic_tuple& operator=(const arithmetic_tuple& other) = default;
	arithmetic_tuple& operator=(arithmetic_tuple&& other) = default;
	
    arithmetic_tuple<E, 0, Z> operator+() const
    { return *this; }

    arithmetic_tuple<E, 0, Z> operator-() const
    { return *this; }

	arithmetic_tuple<E, 0, Z>& operator += (const arithmetic_tuple& other)
	{ return *this; }
	
	arithmetic_tuple<E, 0, Z> operator+(const arithmetic_tuple& other) const
	{ return *this; }

	arithmetic_tuple<E, 0, Z>& operator -= (const arithmetic_tuple& other)
	{ return *this; }
	
	arithmetic_tuple<E, 0, Z> operator-(const arithmetic_tuple& other) const
	{ return *this; }

	arithmetic_tuple<E, 0, Z>& operator *= (const element_type& other)
	{ return *this; }
	
	arithmetic_tuple<E, 0, Z> operator*(const element_type& other) const
	{ return *this; }

	arithmetic_tuple<E, 0, Z>& operator /= (const element_type& other)
	{ return *this; }

	arithmetic_tuple<E, 0, Z> operator/(const element_type& other) const
	{ return *this; }

	bool operator==(const arithmetic_tuple& other) const
	{ return true; }

	bool operator!=(const arithmetic_tuple& other) const
	{ return false; }

	template <typename G>
	static arithmetic_tuple<E, 0, Z> generate(const G& g)
	{ return arithmetic_tuple<E, 0, Z>(); }
	
}; // struct arithmetic_tuple

} // namespace id
