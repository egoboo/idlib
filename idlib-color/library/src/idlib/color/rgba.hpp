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

/// @file idlib/color/rgba.hpp
/// @brief Colors in RGBA color spaces.
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

/// @brief A color in RGBA color space.
template <typename ColorSpace>
struct color<ColorSpace, std::enable_if_t<internal::is_rgba<ColorSpace>::value>> :
    public equal_to_expr<color<ColorSpace>>,
    public plus_expr<color<ColorSpace>, color<ColorSpace>>,
    public minus_expr<color<ColorSpace>, color<ColorSpace>>
{
public:
    /// @brief The RGBA color space type.
    using color_space_type = ColorSpace;
    /// @brief The corresponding RGB color space type.
    using pure_color_space_type = pure_color_space_t<color_space_type>;
    /// @brief The corresponding A color space type.
    using pure_opacity_space_type = pure_opacity_space_t<color_space_type>;

    // Assert the color space is an RGBA color space.
    static_assert(internal::is_rgba<color_space_type>::value, "not an RGBA color space");

    // Define component types and component members.
    #include "idlib/color/rgba-header.in.h"

public:
    using this_type = color<color_space_type>;

private:
    void assign(const this_type& other)
    {
        r = other.r;
        g = other.g;
        b = other.b;
        a = other.a;
    }

public:
    /// @brief The color "red".
    /// @return the color "red"
    /// @see color<RGBb>::red()
    static const color& red()
    {
        static const color c(color<pure_color_space_t<color_space_type>>::red(),
                             color_space_type::a::syntax::range().max());
        return c;
    }

    /// @brief The color "green".
    /// @return the color "green"
    /// @see color<RGBb>::green()
    static const color& green()
    {
        static const color c(color<pure_color_space_t<color_space_type>>::green(),
                             color_space_type::a::syntax::range().max());
        return c;
    }

    /// @brief The color "blue".
    /// @return the color "blue"
    /// @see color<RGBb>::blue()
    static const color& blue()
    {
        static const color c(color<pure_color_space_t<color_space_type>>::blue(),
                             color_space_type::a::syntax::range().max());
        return c;
    }

    /// @brief The color "white".
    /// @return the color "white"
    /// @see color<RGBb>::white()
    static const color& white()
    {
        static const color c(color<pure_color_space_t<color_space_type>>::white(),
                             color_space_type::a::syntax::range().max());
        return c;
    }

    /// @brief The color "black".
    /// @return the color "black"
    /// @see color<RGBb>::black()
    static const color& black()
    {
        static const color c(color<pure_color_space_t<color_space_type>>::black(),
                             color_space_type::a::syntax::range().max());
        return c;
    }

    /// @brief The color "cyan".
    /// @return the color "cyan"
    /// @see color<RGBb>::cyan()
    static const color& cyan()
    {
        static const color c(color<pure_color_space_t<color_space_type>>::cyan(),
                             color_space_type::a::syntax::range().max());
        return c;
    }

    /// @brief The color "magenta".
    /// @return the color "magenta"
    /// @see color<RGBb>::magenta()
    static const color& magenta()
    {
        static const color c(color<pure_color_space_t<color_space_type>>::magenta(),
                             color_space_type::a::syntax::range().max());
        return c;
    }

    /// @brief The color "yellow".
    /// @return the color "yellow"
    /// @see color<RGBb>::yellow()
    static const color& yellow()
    {
        static const color c(color<pure_color_space_t<color_space_type>>::yellow(),
                             color_space_type::a::syntax::range().max());
        return c;
    }

    /// @brief The color "purple".
    /// @return the color "purple"
    /// @see color<RGBb>::purple()
    static const color& purple()
    {
        static const color c(color<pure_color_space_t<color_space_type>>::purple(),
                             color_space_type::a::syntax::range().max());
        return c;
    }

    /// @brief The color "grey".
    /// @return the color "grey"
    /// @see color<RGBb>::grey()
    static const color& grey()
    {
        static const color c(color<pure_color_space_t<color_space_type>>::grey(),
                             color_space_type::a::syntax::range().max());
        return c;
    }

public:
    /// @brief Default construct with component values corresponding to "opaque black".
    color() :
        r(color_space_type::r::syntax::range().min()),
        g(color_space_type::g::syntax::range().min()),
        b(color_space_type::b::syntax::range().min()),
        a(color_space_type::a::syntax::range().max())
    {}

    /// @brief Construct this color from the component values of a another color.
    /// @param other the other color
    template<typename OtherColorSpace,
             std::enable_if_t<std::is_same<OtherColorSpace, ColorSpace>::value, int *> = nullptr>
    color(const color<OtherColorSpace>& other) :
        r(other.get_r()), g(other.get_g()), b(other.get_b()), a(other.get_a())
    {
        // Intentionally empty.
    }

    /// @brief Construct this color from an RGB color and an A component value.
    /// @param rgb the RGB color
    /// @param a the A component value
    /// @throws out_of_bounds_error @a a is not within the bounds of color_space::min() (inclusive) and color_space::max() (inclusive)
    color(const color<pure_color_space_type>& rgb, component_a a) :
        color(rgb, color<pure_opacity_space_type>(a))
    {}

    /// @brief Construct this color from an RGB color and an A color.
    /// @param rgb the RGB color
    /// @param a the A color
    color(const color<pure_color_space_type>& rgb, color<pure_opacity_space_type>& a) :
        r(rgb.get_r()), g(rgb.get_g()), b(rgb.get_b()),
        a(a.get_a())
    {}

    /// @brief Construct this RGBA color from another RGBA color.
    /// @param other the other RGBA color
    template<typename ThisColorSpace = ColorSpace, typename OtherColorSpace>
    explicit color(const color<OtherColorSpace>& other,
                   typename std::enable_if<!std::is_same<ThisColorSpace, OtherColorSpace>::value &&
                                           is_any_of<OtherColorSpace, RGBAb, RGBAf>::value, int *>::type = nullptr) :
        r(type::convert<typename color_space_type::r::syntax, typename OtherColorSpace::r::syntax>()(other.get_r())),
        g(type::convert<typename color_space_type::g::syntax, typename OtherColorSpace::g::syntax>()(other.get_g())),
        b(type::convert<typename color_space_type::b::syntax, typename OtherColorSpace::b::syntax>()(other.get_b())),
        a(type::convert<typename color_space_type::a::syntax, typename OtherColorSpace::a::syntax>()(other.get_a()))
    {}

    /// @brief Construct this RGBA clamped float color from an LA clamped float color.
    /// @param other the LA clamped float color
    template<typename ThisColorSpace = ColorSpace, typename OtherColorSpace>
    explicit color(const color<OtherColorSpace>& other,
                   typename std::enable_if<std::is_same<ThisColorSpace, RGBAf>::value &&
                                           std::is_same<OtherColorSpace, LAf>::value, int *>::type = nullptr) :
        r(other.get_l()), g(other.get_l()), b(other.get_l()), a(other.get_a())
    {}

    /// @brief Construct this RGBA byte color from an LA byte color.
    /// @param other the LA byte color
    template<typename ThisColorSpace = ColorSpace, typename OtherColorSpace>
    explicit color(const color<OtherColorSpace>& other,
                   typename std::enable_if<std::is_same<ThisColorSpace, RGBAb>::value &&
                                           std::is_same<OtherColorSpace, LAb>::value, int *>::type = nullptr) :
        r(other.get_l()), g(other.get_l()), b(other.get_l()), a(other.get_a())
    {}

    /// @brief Construct this RGBA color from an RGB color and an A color.
    /// @param rgb the RGB color
    /// @param a the A color
    template<typename ColorSpaceRgb, typename ColorSpaceA,
             typename std::enable_if<std::is_same<ColorSpaceRgb, pure_color_space_type>::value &&
                                     std::is_same<ColorSpaceA, pure_opacity_space_type>::value, int *>::type = nullptr>
    color(const color<ColorSpaceRgb>& rgb, const color<ColorSpaceA>& a) :
        r(rgb.get_r()), g(rgb.get_g()), b(rgb.get_b()), a(a.get_a())
    {}

    /// @brief Construct this color from the specified component values.
    /// @param r the component value of the red component
    /// @param g the component value of the green component
    /// @param b the component value of the blue component
    /// @param a the component value of the alpha component
    /// @throws out_of_bounds_error @a a, @a g, @a b or @a a are not within the range of color_space::min() (inclusive) and color_space::max() (inclusive)
    color(component_r r, component_g g, component_b b, component_a a) :
        r(r), g(g), b(b), a(a)
    {
        if (color_space_type::r::syntax::range().outside(r))
        {
            throw argument_out_of_bounds_error(__FILE__, __LINE__, "red component out of bounds");
        }
        if (color_space_type::g::syntax::range().outside(g))
        {
            throw argument_out_of_bounds_error(__FILE__, __LINE__, "green component out of bounds");
        }
        if (color_space_type::b::syntax::range().outside(b))
        {
            throw argument_out_of_bounds_error(__FILE__, __LINE__, "blue component out of bounds");
        }
        if (color_space_type::a::syntax::range().outside(a))
        {
            throw argument_out_of_bounds_error(__FILE__, __LINE__, "alpha component out of bounds");
        }
    }

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
        return get_r() == other.get_r()
            && get_g() == other.get_g()
            && get_b() == other.get_b()
            && get_a() == other.get_a();
    }

    // CRTP
    void add(const color& other)
    {
        r = type::add<typename color_space_type::r::syntax>()(get_r(), other.get_r());
        g = type::add<typename color_space_type::g::syntax>()(get_g(), other.get_g());
        b = type::add<typename color_space_type::b::syntax>()(get_b(), other.get_b());
        a = type::add<typename color_space_type::a::syntax>()(get_a(), other.get_a());
    }

    // CRTP
    void subtract(const color& other)
    {
        r = type::subtract<typename color_space_type::r::syntax>()(get_r(), other.get_r());
        g = type::subtract<typename color_space_type::g::syntax>()(get_g(), other.get_g());
        b = type::subtract<typename color_space_type::b::syntax>()(get_b(), other.get_b());
        a = type::subtract<typename color_space_type::a::syntax>()(get_a(), other.get_a());
    }

public:
	#include "idlib/color/rgba.in.h"

public:
    /// @{
    /// @brief Set the value of the red component.
    /// @param r the value of the red component
    /// @throws out_of_bounds_error @a r is not within the bounds of color_space::min() (inclusive) and color_space::max() (inclusive)
#if defined(ID_COLOR_SETTERS) && 1 == ID_COLOR_SETTERS
    void set_red(component_r r)
    {
        if (color_space_type::r::syntax::range().outside(r))
        {
            throw argument_out_of_bounds_error(__FILE__, __LINE__, "red component out of bounds");
        }
        this->r = r;
    }
#if defined(ID_COLOR_SHORT_SETTERS) && 1 == ID_COLOR_SHORT_SETTERS
    void set_r(component_r r)
    { set_red(r); }
#endif
#endif
    /// @}

    /// @{
    /// @brief Set the value of the green component.
    /// @param g the value of the green component
    /// @throws out_of_bounds_error @a g is not within the bounds of color_space::min() (inclusive) and color_space::max() (inclusive)
#if defined(ID_COLOR_SETTERS) && 1 == ID_COLOR_SETTERS
    void set_green(component_g g)
    {
        if (color_space_type::g::syntax::range().outside(g))
        {
            throw argument_out_of_bounds_error(__FILE__, __LINE__, "green component out of bounds");
        }
        this->g = g;
    }
#if defined(ID_COLOR_SHORT_SETTERS) && 1 == ID_COLOR_SHORT_SETTERS
    void set_g(component_g g)
    { set_green(g); }
#endif
#endif
    /// @}

    /// @{
    /// @brief Set the value of the blue component.
    /// @param b the value of the blue component
    /// @throws out_of_bounds_error @a b is not within the bounds of color_space::min() (inclusive) and color_space::max() (inclusive)
#if defined(ID_COLOR_SETTERS) && 1 == ID_COLOR_SETTERS
    void set_blue(component_b b)
    {
        if (color_space_type::b::syntax::range().outside(b))
        {
            throw argument_out_of_bounds_error(__FILE__, __LINE__, "blue component out of bounds");
        }
        this->b = b;
    }
#if defined(ID_COLOR_SHORT_SETTERS) && 1 == ID_COLOR_SHORT_SETTERS
    void set_b(component_b b)
    { set_blue(b); }
#endif
#endif
    /// @}

    /// @{
    /// @brief Set the value of the alpha component.
    /// @param a the value of the alpha component
    /// @throws out_of_bounds_error @a a is not within the bounds of color_space::min() (inclusive) and color_space::max() (inclusive)
#if defined(ID_COLOR_SETTERS) && 1 == ID_COLOR_SETTERS
    void set_alpha(const component_a a)
    {
        if (color_space_type::a::syntax::range().outside(a))
        {
            throw argument_out_of_bounds_error(__FILE__, __LINE__, "alpha component out of bounds");
        }
        this->a = a;
    }
#if defined(ID_COLOR_SHORT_SETTERS) && 1 == ID_COLOR_SHORT_SETTERS
    void set_a(const component_a a)
    { set_alpha(a); }
#endif
#endif
    /// @}

}; // struct color

/// @brief Brighten functor for idlib::color<idlib::RGBAb> and idlib::color<idlib::RGBAf> values.
template <typename ColorSpace>
struct brighten_functor<color<ColorSpace>,
                        std::enable_if_t<is_any_of<ColorSpace, RGBAb, RGBAf>::value>>
{
    using color_space_type = ColorSpace;
    using color_type = color<color_space_type>;
    using pure_color_type = idlib::color<pure_color_space_t<color_space_type>>;
    using pure_opacity_type = idlib::color<pure_opacity_space_t<color_space_type>>;

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

/// @brief Darken functor for idlib::color<idlib::RGBAb> and idlib::color<idlib::RGBAf> values.
template <typename ColorSpace>
struct darken_functor<color<ColorSpace>,
                      std::enable_if_t<is_any_of<ColorSpace, RGBAb, RGBAf>::value>>
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

/// @brief Inversion functor for idlib::color<idlib::RGBAf> values.
/// @remark Given a color \f$(r,g,b,a)\f$ in real-valued, normalized RGBA space,
/// then corresponding inverted color is \f$(1-r,1-g,1-b,1-a)\f$. Inverting a
/// color twice yields the same color (modula floating-point precision).
/// @remark The corresponding inverted color is also known as the complementary color.
template <typename ColorSpace>
struct invert_functor<color<ColorSpace>,
                      std::enable_if_t<is_any_of<ColorSpace, RGBAb, RGBAf>::value>>
{
    using color_space_type = ColorSpace;
    using color_type = color<color_space_type>;

    color_type operator()(const color_type& x) const
    {
        return color_type(type::invert<typename color_space_type::r::syntax>()(x.get_r()),
                          type::invert<typename color_space_type::g::syntax>()(x.get_g()),
                          type::invert<typename color_space_type::b::syntax>()(x.get_b()),
                          type::invert<typename color_space_type::a::syntax>()(x.get_a()));
    }
};

/// @brief Lineary interpolate functor for idlib::color<idlib::RGBAf> values.
template <typename ColorSpace>
struct lineary_interpolate_functor<color<ColorSpace>, float, std::enable_if_t<std::is_same<ColorSpace, RGBAf>::value>>
{
    using color_space_type = ColorSpace;
    using color_type = color<color_space_type>;

    color_type operator()(const color_type& x, const color_type& y, float t) const
    {
        return (*this)(x, y, mu<float>(t));
    }

    color_type operator()(const color_type& x, const color_type& y, const mu<float>& mu) const
    {
        static const auto& range_r = color_space_type::r::syntax::range();
        static const auto& range_g = color_space_type::g::syntax::range();
        static const auto& range_b = color_space_type::b::syntax::range();
        static const auto& range_a = color_space_type::a::syntax::range();
        return color_type(range_r.clamp(lineary_interpolate(x.get_r(), y.get_r(), mu)),
                          range_g.clamp(lineary_interpolate(x.get_g(), y.get_g(), mu)),
                          range_b.clamp(lineary_interpolate(x.get_b(), y.get_b(), mu)),
                          range_a.clamp(lineary_interpolate(x.get_a(), y.get_a(), mu)));
    }

}; // struct lineary_interpolate_functor

} // namespace idlib
