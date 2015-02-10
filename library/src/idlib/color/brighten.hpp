/// @file id/math/interpolate.hpp
/// @brief Functionality to brighten colors.
/// @author Michael Heilmann

#pragma once

namespace id {

/// @brief A functor to brighten a color value.
/// @detail
/// Defines an @code{C operator()(const C& c, F f) const} which brightens the color @a c by the factor @a t.
/// If a brighten functor for some @a C is defined, it shall seek to support @a float and @a double for @a T.
/// @tparam C the color type
/// @tparam E for SFINAE
/// @remark
/// A brighten functor shall not modify the opacity of a color value.
/// @remark
/// The normal approach to brighten a color value can be defined in terms of a brightening a single component value @a c.
/// Given a component value $c$ in the range of $c_min$ (inclusive) and $c_max$ (inclusive) where $c_min \leq c_max$,
/// the brightened component value is usually computed by
/// $clamp(c * (1 + f),c_min, c_max)$.
/// Note that this function can be used to actually darken a color if $f$ is negative,
/// however, using id::darken_functor is then preferred.
template <typename C, typename E = void>
struct brighten_functor;

template <typename C>
decltype(auto) brighten(const C& c, float t)
{
    return brighten_functor<C>()(c, t);
}

template <typename C>
decltype(auto) brighten(const C& c, double t)
{
    return brighten_functor<C>()(c, t);
}

} // namespace id
