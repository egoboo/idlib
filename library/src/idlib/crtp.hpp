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

/// @file idlib/crtp.hpp
/// @brief CRTP (Curiously Recurring Template Pattern) for misc. operators.
/// @author Michael Heilmann

#pragma once

#if !defined(IDLIB_PRIVATE) || IDLIB_PRIVATE != 1
#error(do not include directly, include `idlib/idlib.hpp` instead)
#endif

#include "idlib/utility/platform.hpp"

namespace id {

/// @brief
/// Inherit from this class to define the postfix increment and prefix increment operators.
/// The derived class needs to define a <tt>void increment();</tt> function.
/// @code
/// class foo : increment_expr<foo>
/// {
/// ...
/// protected:
///    void increment() override { ... }
/// ...
/// }
/// @endcode
template <typename Derived>
class increment_expr
{
public:
    Derived& operator++()
    { 
        static_cast<Derived *>(this)->increment();
        return *static_cast<Derived*>(this); 
    }
    Derived operator++(int)
    {
        auto it = *static_cast<Derived *>(this);
        ++(*static_cast<Derived *>(this));
        return *static_cast<Derived *>(&it);
    }
};

/// @brief Inherit from this class to define the postfix decrement and prefix decremen operators.
/// The derived class needs to define a <tt>void decrement();</tt> function.
template <typename Derived>
class decrement_expr
{
public:
    Derived& operator--()
    { 
        static_cast<Derived *>(this)->decrement();
        return *static_cast<Derived *>(this); 
    }
    Derived operator--(int)
    {
        auto it = *static_cast<Derived *>(this);
        --(*static_cast<Derived *>(this));
        return *static_cast<Derived *>(&it);
    }
};

/// @brief Inherit from this class to define the equality and inequality operators.
/// The derived class needs to define a <tt>bool equal_to(const Derived&) const;</tt> function.
template <typename Derived>
class equal_to_expr
{
public:
    bool operator==(const Derived& other) const
    {
        return static_cast<const Derived *>(this)->equal_to(other);
    }
    bool operator!=(const Derived& other) const
    {
        return !(*static_cast<const Derived *>(this) == other);
    }
};

/// @brief Inherit from this class to define the
/// lower than, lower than or equal to, greater than, and greater than or equal to operators.
/// The derived class needs to define a <tt>bool lower_than(const Derived&) const;</tt> function.
template <typename Derived>
class lower_than_expr
{
public:
	bool operator<(const Derived& other) const
    {
        return static_cast<const Derived *>(this)->lower_than(other);
    }
    bool operator>(const Derived& other) const
    {
        return other < *static_cast<const Derived *>(this);
    }
    bool operator<=(const Derived& other) const
    {
        return !(*static_cast<const Derived *>(this) > other);
    }
    bool operator>=(const Derived& other) const
    {
        return !(*static_cast<const Derived *>(this) < other);
    }
};

/// @brief Inherit from this class to define the addition and compount addition assignment operators.
/// The derived class needs to define a <tt>void add(const RHS&);</tt> function.
template <typename LHS, typename RHS>
class plus_expr
{
public:
    LHS& operator+=(const RHS& rhs) // compound addition assignment (does not need to be a member,
    {                                       // but often is, to modify the private members)
        static_cast<LHS *>(this)->add(rhs);
        return *static_cast<LHS *>(this); // return the result by reference
    }
    // friends defined inside class body are inline and are hidden from non-ADL lookup
    friend LHS operator+(LHS lhs,        // passing lhs by value helps optimize chained a+b+c
                         const RHS& rhs) // otherwise, both parameters may be const references
    {
        lhs += rhs; // reuse compound assignment
        return lhs; // return the result by value (uses move constructor)
    }
};

/// @brief Inherit from this class to define the subtraction and compound subtraction assignment operators.
/// The derived class needs to define a <tt>void subtract(const RHS&);</tt> function.
template <typename LHS, typename RHS>
class minus_expr
{
public:
    LHS& operator-=(const RHS& rhs) // compound assignment (does not need to be a member,
    {                               // but often is, to modify the private members)
        static_cast<LHS *>(this)->subtract(rhs);
        return *static_cast<LHS *>(this); // return the result by reference
    }
    // friends defined inside class body are inline and are hidden from non-ADL lookup
    friend LHS operator-(LHS lhs,        // passing lhs by value helps optimize chained a+b+c
                         const RHS& rhs) // otherwise, both parameters may be const references
    {
        lhs -= rhs; // reuse compound assignment
        return lhs; // return the result by value (uses move constructor)
    }
};

/// @brief Inherit from this class to define the unary plus operator.
/// The derived class needs to define a <tt>Derived unary_plus() const;</tt> function.
template <typename Derived>
class unary_plus_expr
{
public:
    Derived operator+() const
    {
        return static_cast<const Derived *>(this)->unary_plus();
    }
};

/// @brief Inherit from this class to define the unary minus operator.
/// The derived class needs to define a <tt>Derived unary_minus() const;</tt> function.
template <typename Derived>
class unary_minus_expr
{
public:
    Derived operator-() const
    {
        return static_cast<const Derived *>(this)->unary_minus();
    }
};

/// @brief Inherit from this class to define the binary star operator.
/// The derived class needs to define a <tt>void multiply(const RHS&);</tt> function.
template <typename LHS, typename RHS>
class binary_star_expr
{
public:
	// friends defined inside class body are inline and are hidden from non-ADL lookup
	friend LHS operator*(LHS lhs,        // passing lhs by value helps optimize chained a+b+c
		                const RHS& rhs) // otherwise, both parameters may be const references
	{
		lhs *= rhs; // reuse compound assignment
		return lhs; // return the result by value (uses move constructor)
	}
	
	LHS& operator*=(const RHS& rhs)
	{
		static_cast<LHS *>(this)->multiply(rhs);
		return *static_cast<LHS *>(this);
	}
};

/// @brief Inherit from this class to define the binary slash operator.
/// The derived class needs to define a <tt>void divide(const RHS&);</tt> function.
template <typename LHS, typename RHS>
class binary_slash_expr
{
	// friends defined inside class body are inline and are hidden from non-ADL lookup
	friend LHS operator/(LHS lhs,        // passing lhs by value helps optimize chained a+b+c
		                 const RHS& rhs) // otherwise, both parameters may be const references
	{
		lhs /= rhs; // reuse compound assignment
		return lhs; // return the result by value (uses move constructor)
	}

	LHS& operator/=(const RHS& rhs)
	{
		static_cast<LHS *>(this)->divide(rhs);
		return *static_cast<LHS *>(this);
	}
};
 
} // namespace id
