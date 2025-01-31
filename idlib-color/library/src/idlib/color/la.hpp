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

/// @file idlib/color/la.hpp
/// @brief Colors in LA color spaces.
/// @author Michael Heilmann

#pragma once

#if !defined(IDLIB_PRIVATE) || IDLIB_PRIVATE != 1
#error(do not include directly, include `idlib/color.hpp` instead)
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
struct color<ColorSpace, std::enable_if_t<internal::is_la<ColorSpace>::value>> :
    public equal_to_expr<color<ColorSpace>>,
    public plus_expr<color<ColorSpace>, color<ColorSpace>>,
    public minus_expr<color<ColorSpace>, color<ColorSpace>>
{
public:
    /// @brief The LA color space type.
    using color_space_type = ColorSpace;
    /// @brief The corresponding L color space type.
    using pure_color_space_type = pure_color_space_t<color_space_type>;
    /// @brief The corresponding A color space type.
    using pure_opacity_space_type = pure_opacity_space_t<color_space_type>;

    // Assert the color space is an LA color space.
    static_assert(internal::is_la<color_space_type>::value, "not an LA color space");

    // Define component types and component members.
    #include "idlib/color/la-header.in.h"

private:
    void assign(const color& other)
    {
        l = other.l;
        a = other.a;
    }

public:
    /// @brief The color "black" (0,0,0).
    /// @return the color "black"
    static const color& black()
    {
        static const color c(color<pure_color_space_t<color_space_type>>::black(),
                             color_space_type::a::syntax::range().max());
        return c;
    }

    /// @brief The color "grey" (75,75,75).
    /// @return the color "grey".
    static const color& grey()
    {
        static const color c(color<pure_color_space_t<color_space_type>>::grey(),
                             color_space_type::a::syntax::range().max());
        return c;
    }

    /// @brief The color "white" (255,255,255).
    /// @return the color "white"
    static const color& white()
    {
        static const color c(color<pure_color_space_t<color_space_type>>::white(),
                             color_space_type::a::syntax::range().max());
        return c;
    }

public:
    /// @brief Default construct with component values corresponding to "opaque black".
    color() :
        l(color_space_type::l::syntax::range().min()), a(color_space_type::a::syntax::range().max())
    {}

    /// @brief Construct this color with the values of another color.
    /// @param other the other color
    template<typename OtherColorSpace,
             std::enable_if_t<std::is_same<OtherColorSpace, ColorSpace>::value, int *> = 0>
    color(const color<OtherColorSpace>& other) :
        l(other.get_l()), a(other.get_a())
    {}

    /// @brief Construct this color with the specified luminance and alpha component values.
    /// @param l the component value of the luminance component
    /// @param a the component value of the alpha component
    /// @throws out_of_bounds_error @a l or @a a are not within the bounds of color_space::min() (inclusive) and color_space::max() (inclusive)
    color(component_l l, component_a a) :
        l(l), a(a)
    {
        if (color_space_type::l::syntax::range().outside(l))
        {
            throw argument_out_of_bounds_error(__FILE__, __LINE__, "luminance component out of bounds");
        }
        if (color_space_type::a::syntax::range().outside(a))
        {
            throw argument_out_of_bounds_error(__FILE__, __LINE__, "alpha component out of bounds");
        }
    }

    /// @brief Construct this color from an L color and a A component value.
    /// @param l the L color
    /// @param a the component value of the blue component
    /// @throws out_of_bounds_error @a a is not within the bounds of color_space::min() (inclusive) and color_space::max() (inclusive)
    color(const color<pure_color_space_type>& l, component_a a) :
        color(l, color<pure_opacity_space_type>(a))
    {}

    /// @brief Construct this color from the specified L color and A color.
    /// @param l the L color
    /// @param a the A color
    color(const color<pure_color_space_type>& l, color<pure_opacity_space_type>& a) :
        l(l.get_l()), a(a.get_a())
    {}

    /// @brief Construct this LA color from an L color and an A color.
    /// @param l the L color
    /// @param a the A color
    template<typename ThisColorSpace = ColorSpace, typename ColorSpaceL, typename ColorSpaceA>
    color(const color<ColorSpaceL>& l, const color<ColorSpaceA>& a,
          typename std::enable_if<std::is_same<ColorSpaceL, pure_color_space_type>::value &&
                                  std::is_same<ColorSpaceA, pure_opacity_space_type>::value, int *>::type = nullptr) :
        l(l.get_l()), a(a.get_a())
    {}

    /// @brief Convert construct this LA color from another LA color.
    /// @param other the other LA color
    template<typename ThisColorSpace = ColorSpace, typename OtherColorSpace>
    explicit color(const color<OtherColorSpace>& other,
                   typename std::enable_if<!std::is_same<color_space_type, OtherColorSpace>::value &&
                                           is_any_of<OtherColorSpace, LAb, LAf>::value, int *>::type = 0) :
        l(type::convert<typename color_space_type::l::syntax, typename OtherColorSpace::l::syntax>()(other.get_l())),
        a(type::convert<typename color_space_type::a::syntax, typename OtherColorSpace::a::syntax>()(other.get_a()))
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
        return get_l() == other.get_l()
            && get_a() == other.get_a();
    }

    // CRTP
    void add(const color& other)
    {
        l = type::add<typename color_space_type::l::syntax>()(get_l(), other.get_l());
        a = type::add<typename color_space_type::a::syntax>()(get_a(), other.get_a());
    }

    // CRTP
    void subtract(const color& other)
    {
        l = type::subtract<typename color_space_type::l::syntax>()(get_l(), other.get_l());
        a = type::subtract<typename color_space_type::a::syntax>()(get_a(), other.get_a());
    }

public:
    #include "idlib/color/la.in.h"

    /// @{
    /// @brief Set the value of the luminance component.
    /// @param l the value of the luminance component
    /// @throws out_of_bounds_error @a l is not within the bounds of color_space::min() (inclusive) and color_space::max() (inclusive)
#if defined(ID_COLOR_SETTERS) && 1 == ID_COLOR_SETTERS
    void set_luminance(component_l l)
    {
        if (color_space_type::l::syntax::range().outside(l))
        {
            throw argument_out_of_bounds_error(__FILE__, __LINE__, "luminance component out of bounds");
        }
        this->l = l;
    }
#if defined(ID_COLOR_SHORT_SETTERS) && 1 == ID_COLOR_SHORT_SETTERS
    void set_l(component_l l)
    { set_luminance(l); }
#endif
#endif
    /// @}

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

/// @brief Brighten functor for idlib::color<idlib::LAb> and idlib::color<idlib::LAf> values.
template <typename ColorSpace>
struct brighten_functor<color<ColorSpace>,
                        std::enable_if_t<is_any_of<ColorSpace, LAb, LAf>::value>>
{
    using color_space_type = ColorSpace;
    using color_type = color<color_space_type>;
    using pure_color_type = color<pure_color_space_t<color_space_type>>;
    using pure_opacity_type = color<pure_opacity_space_t<color_space_type>>;

    color_type operator()(const color_type& c, float f)
    {
        return color_type(brighten(pure_color_type(c), f),
                          pure_opacity_type(c));
    }

    color_type operator()(const color_type& c, double f)
    {
        return color_type(brighten(pure_color_type(c), f),
                          pure_opacity_type(c));
    }

}; // struct brighten_functor

/// @brief Darken functor for idlib::color<idlib::LAb> and idlib::color<idlib::LAf> values.
template <typename ColorSpace>
struct darken_functor<color<ColorSpace>,
                      std::enable_if_t<is_any_of<ColorSpace, LAb, LAf>::value>>
{
    using color_space_type = ColorSpace;
    using color_type = color<color_space_type>;
    using pure_color_type = idlib::color<pure_color_space_t<color_space_type>>;
    using pure_opacity_type = idlib::color<pure_opacity_space_t<color_space_type>>;

    color_type operator()(const color_type& c, float f)
    {
        return color_type(darken(pure_color_type(c), f),
                          pure_opacity_type(c));
    }

    color_type operator()(const color_type& c, double f)
    {
        return color_type(darken(pure_color_type(c), f),
                          pure_opacity_type(c));
    }

}; // struct darken_functor

/// @brief Inversion functor for idlib::color<idlib::LAf> and idlib::color<idlib::LAb> values.
/// @remark Given a color \f$(r,g,b)\f$ in real-valued, normalized LA space,
/// then corresponding inverted color is \f$(1-l,1-a)\f$. Inverting a
/// color twice yields the same color (modula floating-point precision).
/// @remark The corresponding inverted color is also known as the complementary color.
template <typename ColorSpace>
struct invert_functor<color<ColorSpace>,
                      std::enable_if_t<is_any_of<ColorSpace, LAb, LAf>::value>>
{
    using color_space_type = ColorSpace;
    using color_type = color<color_space_type>;

    color_type operator()(const color_type& x) const
    {
        return color_type(type::invert<typename color_space_type::l::syntax>()(x.get_l()),
                          type::invert<typename color_space_type::a::syntax>()(x.get_a()));
    }
}; // struct invert_functor

/// @brief Lineary interpolate functor for idlib::color<idlib::LAf> values.
template <typename ColorSpace>
struct lineary_interpolate_functor<color<ColorSpace>, float, std::enable_if_t<std::is_same<LAf, ColorSpace>::value>>
{
    using color_space_type = ColorSpace;
    using color_type = color<color_space_type>;

    color_type operator()(const color_type& x, const color_type& y, float t) const
    {
        return (*this)(x, y, mu<float>(t));
    }

    color_type operator()(const color_type& x, const color_type& y, const mu<float>& mu) const
    {
        static const auto& range_l = color_space_type::l::syntax::range();
        static const auto& range_a = color_space_type::a::syntax::range();
        return color_type(range_l.clamp(lineary_interpolate(x.get_l(), y.get_l(), mu)),
                          range_a.clamp(lineary_interpolate(x.get_a(), y.get_a(), mu)));
    }

}; // struct lineary_interpolate_functor

} // namespace idlib
