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

/// @file idlib/color/rgb.hpp
/// @brief Colors in RGB color spaces.
/// @author Michael Heilmann

#pragma once

#if !defined(IDLIB_PRIVATE) || IDLIB_PRIVATE != 1
#error(do not include directly, include `idlib/idlib.hpp` instead)
#endif

#include "idlib/color/color.hpp"
#include "idlib/crtp.hpp"
#include "idlib/math/interpolate.hpp"
#include "idlib/math/floating_point.hpp"
#include "idlib/math/invert.hpp"
#include "idlib/utility/is_any_of.hpp"
#include "idlib/color/brighten.hpp"
#include "idlib/color/darken.hpp"
#include "idlib/type.hpp"

namespace idlib {

/// @brief A color in RGB color space.
template <typename ColorSpace>
struct color<ColorSpace, std::enable_if_t<internal::is_rgb<ColorSpace>::value>> :
    public equal_to_expr<color<ColorSpace>>,
    public plus_expr<color<ColorSpace>, color<ColorSpace>>,
    public minus_expr<color<ColorSpace>, color<ColorSpace>>
{
public:
    /// @brief The color space type.
    using color_space_type = ColorSpace;

    // Assert the color space is an RGB color space.
    static_assert(internal::is_rgb<color_space_type>::value, "not an RGB color space");

    // Define component types and component members.
    #include "idlib/color/rgb-header.in.h"

private:
    void assign(const color& other)
    {
        r = other.r;
        g = other.g;
        b = other.b;
    }

public:
    /// @brief The color "red" (255,0,0).
    /// @return the color "red"
    static const color& red()
    {
        static const color c(color<RGBb>(255, 0, 0));
        return c;
    }

    /// @brief The color "green" (0,255,0).
    /// @return the color "green"
    static const color& green()
    {
        static const color c(color<RGBb>(0, 255, 0));
        return c;
    }

    /// @brief The color "blue" (0,0,255).
    /// @return the color "blue"
    static const color& blue()
    {
        static const color c(color<RGBb>(0, 0, 255));
        return c;
    }

    /// @brief The color "white" (255,255,255).
    /// @return the color "white"
    static const color& white()
    {
        static const color c(color<RGBb>(255, 255, 255));
        return c;
    }

    /// @brief The color "black" (0,0,0).
    /// @return the color "black"
    static const color& black()
    {
        static const color c(color<RGBb>(0, 0, 0));
        return c;
    }

    /// @brief The color "cyan" (0,255,255).
    /// @return the color "cyan"
    /// @remark The color "cyan" is the complementary color of the color "red".
    static const color& cyan()
    {
        static const color c(color<RGBb>(0, 255, 255));
        return c;
    }

    /// @brief The color "magenta" (255,0,255).
    /// @return the color "magenta"
    /// @remark The color "magenta" is the complementary color of the color "green".
    static const color& magenta()
    {
        static const color c(color<RGBb>(255, 0, 255));
        return c;
    }

    /// @brief The color "yellow" (255,255,0).
    /// @return the color "yellow"
    /// @remark The color "yellow" is the complementary color of the color "blue".
    static const color& yellow()
    {
        static const color c(color<RGBb>(255, 255, 0));
        return c;
    }

    /// @brief The color "mauve" (224, 176, 255) [Maerz and Paul].
    /// @return the color "mauve".
    static const color& mauve()
    {
        static const color c(color<RGBb>(224, 176, 255));
        return c;
    }

    /// @brief The color "purple" (128, 0, 128).
    /// @return the color "purple".
    static const color& purple()
    {
        static const color c(color<RGBb>(128, 0, 128));
        return c;
    }

    /// @brief The color "grey" (75, 75, 75).
    /// @return the color "grey".
    static const color& grey()
    {
        static const color c(color<RGBb>(75, 75, 75));
        return c;
    }

public:
    /// @brief Default construct with component values corresponding to "opaque black".
    color() :
        r(color_space_type::r::syntax::range().min()),
        g(color_space_type::g::syntax::range().min()),
        b(color_space_type::b::syntax::range().min())
    {}

    /// @brief Construct this color from the component values of a another color.
    /// @param other the other color
    template<typename ThisColorSpace = ColorSpace, typename OtherColorSpace>
    color(const color<OtherColorSpace>& other,
          typename std::enable_if<std::is_same<ThisColorSpace, OtherColorSpace>::value, int *>::type = nullptr) :
        r(other.get_r()), g(other.get_g()), b(other.get_b())
    {}

    /// @brief Construct this color from the specified component values
    /// @param r the component value of the red component
    /// @param g the component value of the green component
    /// @param b the component value of the blue component
    /// @throws out_of_bounds_error @a r, @a g, or @a b a are not within the range of color_space::min() (inclusive) and color_space::max() (inclusive)
    color(component_r r, component_g g, component_b b) :
        r(r), g(g), b(b)
    {
        if (color_space_type::r::syntax::range().outside(r))
        {
            throw out_of_bounds_error(__FILE__, __LINE__, "red component out of bounds");
        }
        if (color_space_type::g::syntax::range().outside(g))
        {
            throw out_of_bounds_error(__FILE__, __LINE__, "green component out of bounds");
        }
        if (color_space_type::b::syntax::range().outside(b))
        {
            throw out_of_bounds_error(__FILE__, __LINE__, "blue component out of bounds");
        }
    }

    /// @brief Convert construct this RGB color from another RGB color.
    /// @param other the other RGB color
    template<typename ThisColorSpace = ColorSpace, typename OtherColorSpace>
    explicit color(const color<OtherColorSpace>& other,
                   typename std::enable_if<!std::is_same<ThisColorSpace, OtherColorSpace>::value &&
                                           is_any_of<OtherColorSpace, RGBb, RGBf>::value, int *>::type = nullptr) :
        r(type::convert<typename color_space_type::r::syntax, typename OtherColorSpace::r::syntax>()(other.get_r())),
        g(type::convert<typename color_space_type::g::syntax, typename OtherColorSpace::g::syntax>()(other.get_g())),
        b(type::convert<typename color_space_type::b::syntax, typename OtherColorSpace::b::syntax>()(other.get_b()))
    {}

    /// @brief Convert construct this RGB byte color from an L byte color.
    /// @param other L byte color
    template<typename ThisColorSpace = ColorSpace, typename OtherColorSpace>
    explicit color(const color<OtherColorSpace>& other,
                   typename std::enable_if<std::is_same<ColorSpace, RGBb>::value &&
                                           std::is_same<OtherColorSpace, Lb>::value, int *>::type = nullptr) :
        r(other.get_l()), g(other.get_l()), b(other.get_l())
    {}

    /// @brief Convert construct this RGB clamped float color from an L clamped float color.
    /// @param other the L clamped float color
    template<typename ThisColorSpace = ColorSpace, typename OtherColorSpace>
    explicit color(const color<OtherColorSpace>& other,
                   typename std::enable_if<std::is_same<ThisColorSpace, RGBf>::value &&
                                           std::is_same<OtherColorSpace, Lf>::value, int *>::type = nullptr) :
        r(other.get_l()), g(other.get_l()), b(other.get_l())
    {}

    /// @brief Decompose construct this RGB color from an RGBA color.
    /// @param other the RGBA color
    template <typename ThisColorSpace = ColorSpace, typename OtherColorSpace>
    explicit color(const color<OtherColorSpace>& other,
                   typename std::enable_if<std::is_same<color_space_type,
                                           pure_color_space_t<OtherColorSpace>>::value, int *>::type = 0) :
        r(other.get_r()), g(other.get_g()), b(other.get_b())
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
        return get_r() == other.get_r()
            && get_g() == other.get_g()
            && get_b() == other.get_b();
    }

    // CRTP
    void add(const color& other)
    {
        r = type::add<typename color_space_type::r::syntax>()(get_r(), other.get_r());
        g = type::add<typename color_space_type::g::syntax>()(get_g(), other.get_g());
        b = type::add<typename color_space_type::b::syntax>()(get_b(), other.get_b());
    }

    // CRTP
    void subtract(const color& other)
    {
        r = type::subtract<typename color_space_type::r::syntax>()(get_r(), other.get_r());
        g = type::subtract<typename color_space_type::g::syntax>()(get_g(), other.get_g());
        b = type::subtract<typename color_space_type::b::syntax>()(get_b(), other.get_b());
    }

public:
	#include "idlib/color/rgb.in.h"

    /// @{
    /// @brief Set the value of the red component.
    /// @param r the value of the red component
    /// @throws out_of_bounds_error @a r is not within the bounds of color_space::min() (inclusive) and color_space::max() (inclusive)
#if defined(ID_COLOR_SETTERS) && 1 == ID_COLOR_SETTERS
    void set_red(component_r r)
    {
        if (color_space_type::r::syntax::range().outside(r))
        {
            throw out_of_bounds_error(__FILE__, __LINE__, "red component out of bounds");
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
            throw out_of_bounds_error(__FILE__, __LINE__, "green component out of bounds");
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
            throw out_of_bounds_error(__FILE__, __LINE__, "blue component out of bounds");
        }
        this->b = b;
    }
#if defined(ID_COLOR_SHORT_SETTERS) && 1 == ID_COLOR_SHORT_SETTERS
    void set_b(component_b b)
    { set_blue(b); }
#endif
#endif
    /// @}

}; // struct color

/// @brief Brighten functor for idlib::color<idlib::RGBb> and idlib::color<idlib::RGBf> values.
template <typename ColorSpace>
struct brighten_functor<color<ColorSpace>,
                        std::enable_if_t<is_any_of<ColorSpace, RGBb, RGBf>::value>>
{
    using color_space_type = ColorSpace;
    using color_type = color<color_space_type>;

    color_type operator()(const color_type& c, float f)
    {
        float t = (1.0f + f);
        return color_type(type::scale<typename color_space_type::r::syntax>()(c.get_r(), t),
                          type::scale<typename color_space_type::g::syntax>()(c.get_g(), t),
                          type::scale<typename color_space_type::b::syntax>()(c.get_b(), t));
    }

    color_type operator()(const color_type& c, double f)
    {
        double t = (1.0 + f);
        return color_type(type::scale<typename color_space_type::r::syntax>()(c.get_r(), t),
                          type::scale<typename color_space_type::g::syntax>()(c.get_g(), t),
                          type::scale<typename color_space_type::b::syntax>()(c.get_b(), t));
    }

}; // struct brighten_functor

/// @brief Darken functor for idlib::color<idlib::RGBb> and idlib::color<idlib::RGBf> values.
template <typename ColorSpace>
struct darken_functor<color<ColorSpace>,
                      std::enable_if_t<is_any_of<ColorSpace, RGBb, RGBf>::value>>
{
    using color_space_type = ColorSpace;
    using color_type = color<color_space_type>;

    color_type operator()(const color_type& c, float f)
    {
        float t = (1.0f - f);
        return color_type(type::scale<typename color_space_type::r::syntax>()(c.get_r(), t),
                          type::scale<typename color_space_type::g::syntax>()(c.get_g(), t),
                          type::scale<typename color_space_type::b::syntax>()(c.get_b(), t));
    }

    color_type operator()(const color_type& c, double f)
    {
        double t = (1.0 - f);
        return color_type(type::scale<typename color_space_type::r::syntax>()(c.get_r(), t),
                          type::scale<typename color_space_type::g::syntax>()(c.get_g(), t),
                          type::scale<typename color_space_type::b::syntax>()(c.get_b(), t));
    }

}; // struct darken_functor

/// @brief Inversion functor for idlib::color<idlib::RGBf> and idlib::color<idlib::RGBb> values.
/// @remark Given a color \f$(r,g,b)\f$ in real-valued, normalized RGBA space,
/// then corresponding inverted color is \f$(1-r,1-g,1-b)\f$. Inverting a
/// color twice yields the same color (modula floating-point precision).
/// @remark The corresponding inverted color is also known as the complementary color.
template <typename ColorSpace>
struct invert_functor<color<ColorSpace>,
                      std::enable_if_t<is_any_of<ColorSpace, RGBb, RGBf>::value>>
{
    using color_space_type = ColorSpace;
    using color_type = color<color_space_type>;

    color_type operator()(const color_type& x) const
    {
        return color_type(type::invert<typename color_space_type::r::syntax>()(x.get_r()),
                          type::invert<typename color_space_type::g::syntax>()(x.get_g()),
                          type::invert<typename color_space_type::b::syntax>()(x.get_b()));
    }

}; // struct invert_functor

/// @brief Lineary interpolate functor for idlib::color<idlib::RGBf> values.
template <typename ColorSpace>
struct lineary_interpolate_functor<color<ColorSpace>, float, std::enable_if_t<std::is_same<ColorSpace, RGBf>::value>>
{
    using color_space_type = ColorSpace;
    using color_type = color<color_space_type>;
	
    color_type operator()(const color_type& x, const color_type& y, float t) const
    {
        return (*this)(x, y, mu<float>(t));
    }

    color_type operator()(const color_type& x, const color_type& y, const mu<float>& mu) const
    {
        return color_type(color_space_type::r::syntax::range().clamp(lineary_interpolate(x.get_r(), y.get_r(), mu)),
                          color_space_type::g::syntax::range().clamp(lineary_interpolate(x.get_g(), y.get_g(), mu)),
                          color_space_type::b::syntax::range().clamp(lineary_interpolate(x.get_b(), y.get_b(), mu)));
    }

}; // struct lineary_interpolate_functor

} // namespace idlib
