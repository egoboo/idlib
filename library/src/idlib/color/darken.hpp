/// @file id/math/interpolate.hpp
/// @brief Functionality to darken colors.
/// @author Michael Heilmann

#pragma once

namespace id {

/// @brief A functor to darken a color value.
/// @detail
/// Defines an @code{C operator()(const C& c, F f) const} which darkens the color @a c by the factor @a t.
/// If a darken functor for some @a C is defined, it shall seek to support @a float and @a double for @a F.
/// @tparam C the color type
/// @tparam E for SFINAE
/// @remark
/// A brighten functor shall not modify the opacity of a color value.
/// @remark
/// The normal approach to darken a color value can be defined in terms of a darkening a single component value @a c.
/// Given a component value $c$ in the range of $c_min$ (inclusive) and $c_max$ (inclusive) where $c_min \leq c_max$,
/// the darkened component value is usually computed by
/// $clamp(c * (1 - f),c_min, c_max)$.
/// Note that this function can be used to actually brightening a color if $f$ is negative,
/// however, using id::brighten_functor is then preferred.
template <typename C, typename E = void>
struct darken_functor;

template <typename C>
decltype(auto) darken(const C& c, float t)
{
    return darken_functor<C>()(c, t);
}

template <typename C>
decltype(auto) darken(const C& c, double t)
{
    return darken_functor<C>()(c, t);
}

} // namespace id
