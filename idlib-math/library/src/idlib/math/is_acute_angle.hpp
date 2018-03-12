/// @file idlib/math/is_acute_angle.hpp
/// @author Michael Heilmann

#pragma once

namespace idlib {

/// @remark An acute angle is an angle which has a measure between that of a right angle and that of a zero angle.
/// @remark An angle \f$\alpha\f$ in degrees is an acute angle if \f$0 \leq a < 90\f$.
/// @remark An angle \f$\alpha\f$ in radians is an acute angle if \f$0 \leq a < \frac{\pi}{2}\f$.
/// @remark An angle \f$\alpha\f$ in turns   is an acute angle if \f$0 \leq a < \frac{1}{4}\f$.
template <typename Syntactics, typename Semantics, typename Enabled = void>
struct is_acute_angle_functor;

template <typename Syntactics, typename Semantics>
auto is_acute_angle(const angle<Syntactics, Semantics>& x) -> decltype(is_acute_angle_functor<Syntactics, Semantics>()(x))
{ return is_acute_angle_functor<Syntactics, Semantics>(x); }

} // namespace idlib
