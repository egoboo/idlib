#pragma once

namespace id { namespace variadic { 

namespace detail {

// base case
template <class A>
constexpr A const &max(A const &a)
{ return a; }
  
// inductive case
template <class A, class...As> // requires SameType<A, As...>
constexpr A const &max(A const &a0, A const &a1, As const &...as)
{ return max(a0 > a1 ? a0 : a1, as...); }

} // namespace detail

// public interface
template <class A, class...As> // requires SameType<A, As...>
inline constexpr A const &max(A const &a, As const &... as)
{ return detail::max(a, as...); }

} } // namespace id::variadic
