#pragma once

namespace id { namespace variadic { 

namespace detail {

// case
template <class A>
constexpr A const &min(A const &a)
{ return a; }
  
// variadic inductive case
template <class A, class...As> // requires SameType<A, As...>
constexpr A const &min(A const &a0, A const &a1, As const &...as)
{ return min(a0 < a1 ? a0 : a1, as...); }

} // namespace detail

// public interface
template <class A, class...As> // requires SameType<A, As...>
inline constexpr A const &min(A const &a, As const &...as)
{ return detail::min(a, as...); }

} } // namespace id::variadic
