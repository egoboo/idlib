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

/// @file idlib/color/a.hpp
/// @brief Colors in A color spaces.
/// @author Michael Heilmann

#pragma once

#if !defined(IDLIB_PRIVATE) || IDLIB_PRIVATE != 1
#error(do not include directly, include `idlib/idlib.hpp` instead)
#endif

#include "idlib/color/color.hpp"
#include "idlib/crtp.hpp"
#include "idlib/numeric.hpp"
#include "idlib/utility/is_any_of.hpp"
#include "idlib/color/brighten.hpp"
#include "idlib/color/darken.hpp"
#include "idlib/type.hpp"

namespace idlib {

/// @brief A color in LA color space.
template <typename ColorSpace>
struct color<ColorSpace, std::enable_if_t<internal::is_a<ColorSpace>::value>> :
    public equal_to_expr<color<ColorSpace>>,
    public plus_expr<color<ColorSpace>, color<ColorSpace>>,
    public minus_expr<color<ColorSpace>, color<ColorSpace>>
{
public:
    /// @brief The type of color space.
    using color_space_type = ColorSpace;

    // Assert the color space is an A color space.
    static_assert(internal::is_a<color_space_type>::value, "not an A color space");

    // Define component types and component members.
    #include "idlib/color/a-header.in.h"

private:
    void assign(const color& other)
    {
        a = other.a;
    }

public:
    /// @brief The color "transparent" (l) = (0).
    /// @return the color "transparent"
    static const color& transparent()
    {
        static const color c(color<Ab>(0));
        return c;
    }

    /// @brief The color "opaque" (l) = (255).
    /// @return the color "opaque".
    static const color& opaque()
    {
        static const color c(color<Ab>(255));
        return c;
    }

public:
    /// @brief Default construct with component values corresponding to "opaque".
    color() :
        a(color_space_type::a::syntax::range().max())
    {}

    /// @brief Construct this color with the values of another color.
    /// @param other the other color
    template<typename OtherColorSpace,
             std::enable_if_t<std::is_same<OtherColorSpace, ColorSpace>::value, int *> = 0>
    color(const color<OtherColorSpace>& other) :
        a(other.get_a())
    {}

    /// @brief Construct this color with the specified alpha component values.
    /// @param a the component value of the alpha component
    /// @throws out_of_bounds_error @a a is not within the bounds of color_space::min() (inclusive) and color_space::max() (inclusive)
    color(component_a a) :
        a(a)
    {
        if (color_space_type::a::syntax::range().outside(a))
        {
            throw argument_out_of_bounds_error(__FILE__, __LINE__, "alpha component out of bounds");
        }
    }

    /// @brief Convert construct this A color from another A color.
    /// @param other the other A color
    template <typename ThisColorSpace = ColorSpace, typename OtherColorSpace>
    explicit color(const color<OtherColorSpace>& other,
                   typename std::enable_if<!std::is_same<ThisColorSpace, OtherColorSpace>::value &&
                                           is_any_of<OtherColorSpace, Ab, Af>::value, int *>::type dummy = nullptr) :
        a(type::convert<typename color_space_type::a::syntax, typename OtherColorSpace::a::syntax>()(other.get_a()))
    {}

    /// @brief Decompose construct this A color from an LA or RGBA color.
    /// @param other the LA or RGBA color
    template <typename ThisColorSpace = ColorSpace, typename OtherColorSpace>
    explicit color(const color<OtherColorSpace>& other,
                   typename std::enable_if<(std::is_same<ThisColorSpace, Af>::value && is_any_of<OtherColorSpace, LAf, RGBAf>::value) ||
                                           (std::is_same<ThisColorSpace, Ab>::value && is_any_of<OtherColorSpace, LAb, RGBAb>::value), int *>::type dummy = nullptr) :
        a(other.get_a())
    {}

public:
    /// @brief Assign this color from another color.
    /// @param other the other color
    /// @return this color
    const color& operator=(const color& other)
    {
        this->assign(other);
        return *this;
    }

public:
    // CRTP
    bool equal_to(const color& other) const
    {
        return get_a() == other.get_a();
    }

    // CRTP
    void add(const color& other)
    {
        a = type::add<typename color_space_type::a::syntax>()(get_a(), other.get_a());
    }

    // CRTP
    void subtract(const color& other)
    {
        a = type::subtract<typename color_space_type::a::syntax>()(get_a(), other.get_a());
    }

public:
    #include "idlib/color/a.in.h"

    /// @{
    /// @brief Set the value of the alpha component.
    /// @param a the value of the alpha component
    /// @throws out_of_bounds_error @a a is not within the bounds of color_space::min() (inclusive) and color_space::max() (inclusive)
#if defined(ID_COLOR_SETTERS) && 1 == ID_COLOR_SETTERS
    void set_alpha(component_a a)
    {
        if (color_space_type::a::syntax::range().outside(a))
        {
            throw argument_out_of_bounds_error(__FILE__, __LINE__, "alpha component out of bounds");
        }
        this->a = a;
    }
#if defined(ID_COLOR_SHORT_SETTERS) && 1 == ID_COLOR_SHORT_SETTERS
    void set_a(component_a a)
    { set_alpha(a); }
#endif
#endif
    /// @}

}; // struct color

/// @brief Invert functor for idlib::color<idlib::Af> and idlib::color<idlib::Ab> values.
/// @remark Given a color \f$(a)\f$ in real-valued, normalized A space,
/// then corresponding inverted color is \f$(1-a)\f$. Inverting a
/// color twice yields the same color (modula floating-point precision).
/// @remark The corresponding inverted color is also known as the complementary color.
template <typename ColorSpace>
struct invert_functor<color<ColorSpace>,
                      std::enable_if_t<is_any_of<ColorSpace, Ab, Af>::value>>
{
    using color_space_type = ColorSpace;
    using color_type = color<color_space_type>;

    color_type operator()(const color_type& x) const
    {
        return color_type(type::invert<typename color_space_type::a::syntax>()(x.get_a()));
    }

}; // struct invert_functor

/// @brief Interpolate functor for idlib::color<idlib::Af> values.
template <typename ColorSpace>
struct lineary_interpolate_functor<color<ColorSpace>, single, std::enable_if_t<std::is_same<Af, ColorSpace>::value>>
{
    using color_space_type = ColorSpace;
    using color_type = color<color_space_type>;

    color_type operator()(const color_type& x, const color_type& y, single t) const
    {
        return (*this)(x, y, mu<single>(t));
    }

    color_type operator()(const color_type& x, const color_type& y, const mu<single>& mu) const
    {
        static const auto& range_a = color_space_type::a::syntax::range();
        return color_type(range_a.clamp(lineary_interpolate(x.get_a(), y.get_a(), mu)));
    }

}; // struct interpolate_functor

} // namespace idlib
