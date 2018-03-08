///////////////////////////////////////////////////////////////////////////////////////////////////
//
// Idlib: A C++ utility library
// Copyright (C) 2017-2018 Michael Heilmann
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#if !defined(IDLIB_PRIVATE) || IDLIB_PRIVATE != 1
#error(do not include directly, include `idlib/color.hpp` instead)
#endif

#include "idlib/type.hpp"

namespace idlib {

namespace semantics {

/// @brief "red".
struct r {};
/// @brief "green".
struct g {};
/// @brief "blue".
struct b {};
/// @brief "alpha".
struct a {};
/// @brief "luminance".
struct l {};

}

template <typename Semantics, typename Syntax, size_t Index>
struct component
{ 
    using semantics = Semantics;
    using syntax = Syntax;
    static constexpr size_t index = Index;
};

template <typename ... Components>
struct space
{};

/// @brief The type of an L color space with floating-point components each within the range from 0 (inclusive) to 1 (inclusive).
/// A component value of 0 indicates minimal intensity of the component and 1 indicates maximal intensity of the component.
template <>
struct space<component<semantics::l, type::clamped_single_traits, 0>>
{
    /// @brief The L component.
    using l = component<semantics::l, type::clamped_single_traits, 0>;

    /// @brief If the color space has RGB components.
    /// @return @a true if the color space has RGB components, @a false otherwise
    static constexpr bool has_rgb = false;

    /// @brief If the color space has an A component.
    /// @return @a true if the color space has an A component, @a false otherwise
    static constexpr bool has_a = false;

    /// @brief If the color space has a L component.
    /// @return @a true if the color space has an L component, @a false otherwise
    static constexpr bool has_l = true;

    /// @brief Get the number of components of a color in the color space.
    /// @return the number of components of a color in the color space
    static constexpr size_t count = 1;
};

using Lf = space<component<semantics::l, type::clamped_single_traits, 0>>;

/// @brief The type of an LA color space with floating-point components each within the range from 0 (inclusive) to 1 (inclusive).
/// A component value of 0 indicates minimal intensity of the component and 1 indicates maximal intensity of the component.
template <>
struct space<component<semantics::l, type::clamped_single_traits, 0>,
             component<semantics::a, type::clamped_single_traits, 1>>
{
    /// @brief The L component.
    using l = component<semantics::l, type::clamped_single_traits, 0>;

    /// @brief The A component.
    using a = component<semantics::a, type::clamped_single_traits, 1>;

    /// @brief If the color space has RGB components.
    /// @return @a true if the color space has RGB components, @a false otherwise
    static constexpr bool has_rgb = false;

    /// @brief If the color space has an A component.
    /// @return @a true if the color space has an A component, @a false otherwise
    static constexpr bool has_a = true;

    /// @brief If the color space has a L component.
    /// @return @a true if the color space has an L component, @a false otherwise
    static constexpr bool has_l = true;

    /// @brief The number of components of a color in the color space.
    /// @return the number of components of a color in the color space
    static constexpr size_t count = 2;
};

using LAf = space<component<semantics::l, type::clamped_single_traits, 0>,
                  component<semantics::a, type::clamped_single_traits, 1>>;

/// @brief The type of an L color space with unsigned integer components each within the range from 0 (inclusive) to 255 (inclusive).
/// A component value of 0 indicates minimal intensity of the component and 255 indicates maximal intensity of the component.
template <>
struct space<component<semantics::l, type::uint8_traits, 0>>
{
    /// @brief The L component.
    using l = component<semantics::l, type::uint8_traits, 0>;

    /// @brief If the color space has RGB components.
    /// @return @a true if the color space has RGB components, @a false otherwise
    static constexpr bool has_rgb = false;

    /// @brief If the color space has an A component.
    /// @return @a true if the color space has an A component, @a false otherwise
    static constexpr bool has_a = false;

    /// @brief If the color space has a L component.
    /// @return @a true if the color space has an L component, @a false otherwise
    static constexpr bool has_l = true;

    /// @brief The number of components of a color in the color space.
    /// @return the number of components of a color in the color space
    static constexpr size_t count = 1;
};

using Lb = space<component<semantics::l, type::uint8_traits, 0>>;

/// @brief The type of an LA color space with unsigned integer components each within the range from 0 (inclusive) to 255 (inclusive).
/// A component value of 0 indicates minimal intensity of the component and 255 indicates maximal intensity of the component.
template <>
struct space<component<semantics::l, type::uint8_traits, 0>,
             component<semantics::a, type::uint8_traits, 1>>
{
    /// @brief The L component.
    using l = component<semantics::l, type::uint8_traits, 0>;

    /// @brief The A component.
    using a = component<semantics::a, type::uint8_traits, 1>;

    /// @brief If the color space has RGB components.
    /// @return @a true if the color space has RGB components, @a false otherwise
    static constexpr bool has_rgb = false;

    /// @brief If the color space has an A component.
    /// @return @a true if the color space has an A component, @a false otherwise
    static constexpr bool has_a = true;

    /// @brief If the color space has a L component.
    /// @return @a true if the color space has an L component, @a false otherwise
    static constexpr bool has_l = true;

    /// @brief The number of components of a color in the color space.
    /// @return the number of components of a color in the color space
    static constexpr size_t count = 2;
};

using LAb = space<component<semantics::l, type::uint8_traits, 0>,
                  component<semantics::a, type::uint8_traits, 1>>;

/// @brief The type of an RGB color space with floating-point components each within the range from 0 (inclusive) to 1 (inclusive).
/// A component value of 0 indicates minimal intensity of the component and 1 indicates maximal intensity of the component.
template <>
struct space<component<semantics::r, type::clamped_single_traits, 0>,
             component<semantics::g, type::clamped_single_traits, 1>,
             component<semantics::b, type::clamped_single_traits, 2>>
{
    /// @brief The R component.
    using r = component<semantics::r, type::clamped_single_traits, 0>;

    /// @brief The G component.
    using g = component<semantics::g, type::clamped_single_traits, 1>;

    /// @brief The B component.
    using b = component<semantics::b, type::clamped_single_traits, 2>;

    /// @brief If the color space has RGB components.
    /// @return @a true if the color space has RGB components, @a false otherwise
    static constexpr bool has_rgb = true;

    /// @brief If the color space has an A component.
    /// @return @a true if the color space has an A component, @a false otherwise
    static constexpr bool has_a = false;

    /// @brief If the color space has a L component.
    /// @return @a true if the color space has an L component, @a false otherwise
    static constexpr bool has_l = false;

    /// @brief The number of components of a color in the color space.
    /// @return the number of components of a color in the color space
    static constexpr size_t count = 3;
};

using RGBf = space<component<semantics::r, type::clamped_single_traits, 0>,
                   component<semantics::g, type::clamped_single_traits, 1>,
                   component<semantics::b, type::clamped_single_traits, 2>>;

/// @brief The type of an RGBA color space with floating-point components each within the range from 0 (inclusive) to 1 (inclusive).
/// A component value of 0 indicates minimal intensity of the component and 1 indicates maximal intensity of the component.
template <>
struct space<component<semantics::r, type::clamped_single_traits, 0>,
             component<semantics::g, type::clamped_single_traits, 1>,
             component<semantics::b, type::clamped_single_traits, 2>,
             component<semantics::a, type::clamped_single_traits, 3>>
{
    /// @brief The R component.
    using r = component<semantics::r, type::clamped_single_traits, 0>;

    /// @brief The G component.
    using g = component<semantics::g, type::clamped_single_traits, 1>;

    /// @brief The B component.
    using b = component<semantics::b, type::clamped_single_traits, 2>;

    /// @brief The A component.
    using a = component<semantics::a, type::clamped_single_traits, 3>;

    /// @brief If the color space has RGB components.
    /// @return @a true if the color space has RGB components, @a false otherwise
    static constexpr bool has_rgb = true;

    /// @brief If the color space has an A component.
    /// @return @a true if the color space has an A component, @a false otherwise
    static constexpr bool has_a = true;

    /// @brief If the color space has an L component.
    /// @return @a true if the color space has an L component, @a false otherwise
    static constexpr bool has_l = false;

    /// @brief The number of components of a color in the color space.
    /// @return the number of components of a color in the color space
    static constexpr size_t count = 4;
};

using RGBAf = space<component<semantics::r, type::clamped_single_traits, 0>,
                    component<semantics::g, type::clamped_single_traits, 1>,
                    component<semantics::b, type::clamped_single_traits, 2>,
                    component<semantics::a, type::clamped_single_traits, 3>>;

/// @brief The type of an RGB color space with unsigned integer components each within the range from 0 (inclusive) to 255 (inclusive).
/// A component value of 0 indicates minimal intensity of the component and 255 indicates maximal intensity of the component.
template <>
struct space<component<semantics::r, type::uint8_traits, 0>,
             component<semantics::g, type::uint8_traits, 1>,
             component<semantics::b, type::uint8_traits, 2>>
{
    /// @brief The R component.
    using r = component<semantics::r, type::uint8_traits, 0>;

    /// @brief The G component.
    using g = component<semantics::g, type::uint8_traits, 1>;

    /// @brief The B component.
    using b = component<semantics::b, type::uint8_traits, 2>;

    /// @brief If the color space has RGB components.
    /// @return @a true if the color space has RGB components, @a false otherwise
    static constexpr bool has_rgb = true;

    /// @brief If the color space has an A component.
    /// @return @a true if the color space has an A component, @a false otherwise
    static constexpr bool has_a = false;

    /// @brief If the color space has an L component.
    /// @return @a true if the color space has an L component, @a false otherwise
    static constexpr bool has_l = false;

    /// @brief The number of components of a color in the color space.
    /// @return the number of components of a color in the color space
    static constexpr size_t count = 3;
};

using RGBb = space<component<semantics::r, type::uint8_traits, 0>,
                   component<semantics::g, type::uint8_traits, 1>,
                   component<semantics::b, type::uint8_traits, 2>>;

/// @brief The type of an RGBA color space with unsigned integer components each within the range from 0 (inclusive) to 255 (inclusive).
/// A component value of 0 indicates minimal intensity of the component and 255 indicates maximal intensity of the component.
template <>
struct space<component<semantics::r, type::uint8_traits, 0>,
             component<semantics::g, type::uint8_traits, 1>,
             component<semantics::b, type::uint8_traits, 2>,
             component<semantics::a, type::uint8_traits, 3>>
{
    /// @brief The R component.
    using r = component<semantics::r, type::uint8_traits, 0>;

    /// @brief The G component.
    using g = component<semantics::g, type::uint8_traits, 1>;

    /// @brief The B component.
    using b = component<semantics::b, type::uint8_traits, 2>;

    /// @brief The A component.
    using a = component<semantics::a, type::uint8_traits, 3>;

    /// @brief If the color space has RGB components.
    /// @return @a true if the color space has RGB components, @a false otherwise
    static constexpr bool has_rgb = true;

    /// @brief If the color space has an A component.
    /// @return @a true if the color space has an A component, @a false otherwise
    static constexpr bool has_a = true;

    /// @brief If the color space has an L component.
    /// @return @a true if the color space has an L component, @a false otherwise
    static constexpr bool has_l = false;

    /// @brief The number of components in the color space.
    /// @return the number of components of a color in the color space
    static constexpr size_t count = 4;
};

using RGBAb = space<component<semantics::r, type::uint8_traits, 0>,
                    component<semantics::g, type::uint8_traits, 1>,
                    component<semantics::b, type::uint8_traits, 2>,
                    component<semantics::a, type::uint8_traits, 3>>;

/// @brief The type of an A color space with floating-point components each within the range from 0 (inclusive) to 1 (inclusive).
/// A component value of 0 indicates minimal intensity of the component and 1 indicates maximal intensity of the component.
template <>
struct space<component<semantics::a, type::clamped_single_traits, 0>>
{
    /// @brief The A component.
    using a = component<semantics::a, type::clamped_single_traits, 0>;

    /// @brief If the color space has RGB components.
    /// @return @a true if the color space has RGB components, @a false otherwise
    static constexpr bool has_rgb = false;

    /// @brief If the color space has an A component.
    /// @return @a true if the color space has an A component, @a false otherwise
    static constexpr bool has_a = true;

    /// @brief If the color space has a L component.
    /// @return @a true if the color space has an L component, @a false otherwise
    static constexpr bool has_l = false;

    /// @brief The number of components of a color in the color space.
    /// @return the number of components of a color in the color space
    static constexpr size_t count = 1;
};

using Af = space<component<semantics::a, type::clamped_single_traits, 0>>;

/// @brief The type of an A color space with unsigned integer components each within the range from 0 (inclusive) to 255 (inclusive).
/// A component value of 0 indicates minimal intensity of the component and 255 indicates maximal intensity of the component.
template <>
struct space<component<semantics::a, type::uint8_traits, 0>>
{
    /// @brief The A component.
    using a = component<semantics::a, type::uint8_traits, 0>;

    /// @brief If the color space has RGB components.
    /// @return @a true if the color space has RGB components, @a false otherwise
    static constexpr bool has_rgb = false;

    /// @brief If the color space has an A component.
    /// @return @a true if the color space has an A component, @a false otherwise
    static constexpr bool has_a = true;

    /// @brief If the color space has a L component.
    /// @return @a true if the color space has an L component, @a false otherwise
    static constexpr bool has_l = false;

    /// @brief The number of components of a color in the color space.
    /// @return the number of components of a color in the color space
    static constexpr size_t count = 1;
};

using Ab = space<component<semantics::a, type::uint8_traits, 0>>;

/// @brief Get the color space containing only the opacity components of a color space if the color space has any.
/// Undefined otherwise.
template <typename ColorSpace>
struct pure_opacity_space;

template <>
struct pure_opacity_space<RGBAb>
{ using type = Ab; };

template <>
struct pure_opacity_space<RGBAf>
{ using type = Af; };

template <>
struct pure_opacity_space<LAb>
{ using type = Ab; };

template <>
struct pure_opacity_space<LAf>
{ using type = Af; };

template <typename ColorSpace>
using pure_opacity_space_t = typename pure_opacity_space<ColorSpace>::type;

/// @brief Get the color space containing only the color components of a color space if the color space has any.
/// Undefined otherwise.
template <typename ColorSpace>
struct pure_color_space;

template <>
struct pure_color_space<RGBb>
{ using type = RGBb; };

template <>
struct pure_color_space<RGBf>
{ using type = RGBf; };

template <>
struct pure_color_space<Lb>
{ using type = Lb; };

template <>
struct pure_color_space<Lf>
{ using type = Lf; };

template <>
struct pure_color_space<RGBAb>
{ using type = RGBb; };

template <>
struct pure_color_space<RGBAf>
{ using type = RGBf; };

template <>
struct pure_color_space<LAb>
{ using type = Lb; };

template <>
struct pure_color_space<LAf>
{ using type = Lf; };

template <typename ColorSpace>
using pure_color_space_t = typename pure_color_space<ColorSpace>::type;

namespace internal {

template <typename ColorSpace>
struct is_l
{
    static constexpr bool value =
           !ColorSpace::has_rgb
        &&  ColorSpace::has_l
        && !ColorSpace::has_a;
};
template <typename ColorSpace>
using is_l_v = typename is_l<ColorSpace>::value;

template <typename ColorSpace>
struct is_a
{
    static constexpr bool value =
           !ColorSpace::has_rgb
        && !ColorSpace::has_l
        &&  ColorSpace::has_a;
};
template <typename ColorSpace>
using is_a_v = typename is_a<ColorSpace>::value;

template <typename ColorSpace>
struct is_la
{
    static constexpr bool value =
           !ColorSpace::has_rgb
        &&  ColorSpace::has_l
        &&  ColorSpace::has_a;
};
template <typename ColorSpace>
using is_la_v = typename is_la<ColorSpace>::value;

template <typename ColorSpace>
struct is_rgb
{
    static constexpr bool value = 
            ColorSpace::has_rgb
        && !ColorSpace::has_l
        && !ColorSpace::has_a;
};
template <typename ColorSpace>
using is_rgb_v = typename is_rgb<ColorSpace>::value;

template <typename ColorSpace>
struct is_rgba
{
    static constexpr bool value =
            ColorSpace::has_rgb
        && !ColorSpace::has_l
        &&  ColorSpace::has_a;
};
template <typename ColorSpace>
using is_rgba_v = typename is_rgba<ColorSpace>::value;

} // namespace internal

} // namespace idlib
