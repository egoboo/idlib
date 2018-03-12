#pragma once

#include "idlib/math/angle-degrees-radians-turns.hpp"
#include "idlib/math/is_acute_angle.hpp"

namespace idlib {

template <typename Syntactics, typename Semantics>
struct is_acute_angle_functor<Syntactics, Semantics,
                              std::enable_if_t<std::is_same<Semantics, degrees>::value &&
                                               std::is_floating_point<Syntactics>::value>>
{
    using angle_type = angle<Syntactics, Semantics>;
    bool operator()(const angle_type& x) const
    {
        return angle_type(zero<Syntactics>()) <= x
            && x < angle_type(fraction<Syntactics, 90, 1>());
    }
};

template <typename Syntactics, typename Semantics>
struct is_acute_angle_functor<Syntactics, Semantics,
                              std::enable_if_t<std::is_same<Semantics, radians>::value &&
                                               std::is_floating_point<Syntactics>::value>>
{
    using angle_type = angle<Syntactics, Semantics>;
    bool operator()(const angle_type& x) const
    {
        return angle_type(zero<Syntactics>()) <= x
            && x < angle_type(pi<Syntactics>());
    }
};

template <typename Syntactics, typename Semantics>
struct is_acute_angle_functor<Syntactics, Semantics,
                              std::enable_if_t<std::is_same<Semantics, turns>::value &&
                                               std::is_floating_point<Syntactics>::value>>
{
    using angle_type = angle<Syntactics, Semantics>;
    bool operator()(const angle_type& x) const
    {
        return angle_type(zero<Syntactics>()) <= x
            && x < angle_type(fraction<Syntactics, 1, 4>());
    }
};

} // namespace idlib
