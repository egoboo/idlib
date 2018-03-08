#pragma once

#if !defined(IDLIB_PRIVATE) || IDLIB_PRIVATE != 1
#error(do not include directly, include `idlib/numeric.hpp` instead)
#endif

#pragma push_macro("IDLIB_PRIVATE")
#undef IDLIB_PRIVATE
#define IDLIB_PRIVATE (1)

#include "idlib/numeric/interval.hpp"
#include "idlib/numeric/zero_floating_point.hpp"

#undef IDLIB_PRIVATE
#pragma pop_macro("IDLIB_PRIVATE")

#include "idlib/exception.hpp"
#include <limits>
#include <cmath>

namespace idlib {

/// @brief Specialization of idlib::interval for floating point values.
template <typename Value>
struct interval<Value, std::enable_if_t<std::is_floating_point<Value>::value>>
{
    /// @brief The value type.
    using value_type = Value;

    /// @brief The interval type.
    using interval_type = interval<value_type>;

private:
    /// @brief The lowerbound (inclusive).
    value_type l;
    /// @brief The upperbound (inclusive).
    value_type u;

public:
    /// @brief Construct this range with default values.
    /// @remark The default values are the lowerbound of \f$0\f$ and the upperbound of \f$0\f$.
    interval() :
        l(zero<value_type>()), u(zero<value_type>())
    { /* Intentionally empty. */}

    /// @brief Copy-construct this range from another range.
    /// @param other the other range
    interval(const interval& other) :
        l(other.l), u(other.u) {}

    /// @brief Construct this range with the specified values.
    /// @param l the lowerbound
    /// @param u the upperbound
    /// @pre <c>l &lt;= u</c>
    /// @throw idlib::invalid_argument_error <c>!(l &lt;= u)</c>
    interval(const value_type& l, const value_type& u) :
        l(l), u(u)
    {
        if (!(l <= u))
        {
            throw idlib::invalid_argument_error(__FILE__, __LINE__, "precondition `l <= u` failed");
        }
    }

public:
    /// @brief Assign this interval with the values of another interval.
    /// @param other the other interval
    /// @return this interval
    /// @post This interval was assigned the values of the other interval.
    const interval_type& operator=(const interval& other)
    {
        l = other.l;
        u = other.u;
        return *this;
    }

public:
    bool operator==(const interval& other) const
    {
        return l == other.l
            && u == other.u;
    }

    bool operator!=(const interval& other) const
    {
        return l != other.l
            || u != other.u;
    }

public:
    /// @brief Compute a new interval with a lowerbound (upperbound) that is equal to the lowerbound (upperbound) of this interval multiplied by a value.
    /// @param v the value
    /// @return the interval
    /// @remark Given an interval \f$a=[l,u]\f$ and a value \f$v\f$, this method computes a new interval \f$a' = v \cdot a = v \cdot [l,u] = [v\cdot l, v\cdot u]\f$.
    interval_type operator*(const value_type& v) const
    { return interval_type(l * v, u * v); }

    /// @brief Compute a new interval with a lowerbound (upperbound) that is equal to the lowerbound (upperbound) of this interval multiplied by a value.
    /// and assign the result to this interval.
    /// @param v the value
    /// @return this interval
    const interval_type& operator*=(const value_type& v)
    {
        (*this) = (*this) * v;
        return *this;
    }

public:
    /// @brief Compute a new interval with a lowerbound (upperbound) that is equal to the lowerbound (upperbound) of this interval divided by a value.
    /// @param v the value
    /// @return the interval
    /// @remark Given an interval \f$a=[l,u]\f$ and a value \f$v\f$, this method computes a new interval \f$a' = \frac{a}{v} = \frac{[l,u]}{v} = [\frac{l}{v}, \frac{u}{v}]\f$.
    interval_type operator/(const value_type& v) const
    { return interval_type(l / v, u / v); }

    /// @brief Compute a new interval with a lowerbound (upperbound) that is equal to the lowerbound (upperbound) of this interval divided by a value.
    /// and assign the result to this interval.
    /// @param v the value
    /// @return this interval
    const interval_type& operator/=(const value_type& v)
    {
        (*this) = (*this) / v;
        return *this;
    }

public:
    /// @brief Compute a new interval with a lowerbound (upperbound) that is equal to the lowerbound (upperbound) of this interval added by a value.
    /// @param v the value
    /// @return the interval
    /// @remark Given an interval \f$a=[l,u]\f$ and a value \f$v\f$, this method computes a new interval \f$a' = a + v = [l,u] + v = [l + v, u + v]\f$.
    interval_type operator+(const value_type& v) const
    { return interval_type(l + v, u + v); }

    /// @brief Compute a new interval with a lowerbound (upperbound) that is equal to the lowerbound (upperbound) of this interval added by a value.
    /// and assign the result to this range.
    /// @param v the value
    /// @return this interval
    const interval_type& operator+=(const value_type& v)
    {
        (*this) = (*this) + v;
        return *this;
    }

public:
    /// @brief Compute a new interval with a lowerbound (upperbound) that is equal to the lowerbound (upperbound) subtracted by a scalar.
    /// @param v the scalar
    /// @return the interval
    /// @remark Given an interval \f$a=[l,u]\f$ and a scalar \f$s\f$, this method computes a new interval \f$a' = a - s = [l,u] - s = [l - s, u - s]\f$.
    interval_type operator-(const value_type& v) const
    { return interval_type(l - v, u - v); }

    /// @brief Compute a new interval with a lowerbound (upperbound) that is equal to the lowerbound (upperbound) of this interval subtracted by a scalar
    /// and assign the result to this range.
    /// @param v the scalar
    /// @return this interval
    const interval_type& operator-=(const value_type& v)
    { 
        (*this) = (*this) - v;
        return *this;
    }

public:
    /// @brief Get the lowerbound.
    /// @return the lowerbound
    /// @invariant <c>getLowerbound() &lt;= getUpperbound()</c>
    const value_type& lower() const
    { return l; }

    /// @brief Get the upperbound.
    /// @return the uppebound
    /// @invariant <c>getLowerbound() &lt;= getUpperbound()</c>
    const value_type& upper() const
    { return u; }

    /// @brief Get the length of this interval.
    /// @return the length of this interval
    auto length() const
    { return upper() - lower(); }

public:
    /// @brief Get if this interval is equivalent to the interval \f$[0,0]\f$.
    /// @return @a true if this interval is equivalent to the interval \f$[0,0]\f$, @a false otherwise
    bool is_zero() const
    { return std::abs(l) + std::abs(u) < std::numeric_limits<value_type>::epsilon(); }

}; // struct interval

} // namespace idlib
