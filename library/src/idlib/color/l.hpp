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

/// @file idlib/color/l.hpp
/// @brief Colors in L color spaces.
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

/// @brief A color in L color space.
template <typename ColorSpace>
struct color<ColorSpace, std::enable_if_t<internal::is_l<ColorSpace>::value>> :
    public equal_to_expr<color<ColorSpace>>,
    public plus_expr<color<ColorSpace>, color<ColorSpace>>,
    public minus_expr<color<ColorSpace>, color<ColorSpace>>
{
public:
    /// @brief The type of the color space.
    using color_space_type = ColorSpace;

    // Assert the color space is an L color space.
    static_assert(internal::is_l<color_space_type>::value, "not an L color space");

    // Define component types and component members.
    #include "idlib/color/l-header.in.h"

private:
    void assign(const color& other)
    {
        l = other.l;
    }

public:
    /// @brief The color "black" (0,0,0).
    /// @return the color "black"
    static const color& black()
    {
        static const color c(color<Lb>(0));
        return c;
    }

    /// @brief The color "grey" (75,75,75).
    /// @return the color "grey".
    static const color& grey()
    {
        static const color c(color<Lb>(75));
        return c;
    }

    /// @brief The color "white" (255,255,255).
    /// @return the color "white"
    static const color& white()
    {
        static const color c(color<Lb>(255));
        return c;
    }

public:
    /// @brief Default construct with component values corresponding to "opaque black".
    color() :
        l(color_space_type::l::syntax::range().min())
    {}

    /// @brief Construct this color with the specified luminance component color.
    /// @param l the component value of the luminance component
    /// @throws out_of_bounds_error @a l is not within the bounds of color_space::min() (inclusive) and color_space::max() (inclusive)
    color(component_l l) :
        l(l)
    {
        if (color_space_type::l::syntax::range().outside(l))
        {
            throw out_of_bounds_error(__FILE__, __LINE__, "luminance component out of bounds");
        }
    }

    /// @brief Copy construct this color with the component values of another color.
    /// @param other the other color
    template <typename ThisColorSpace = ColorSpace, typename OtherColorSpace>
    color(const color<OtherColorSpace>& other,
          typename std::enable_if<std::is_same<ThisColorSpace, OtherColorSpace>::value, int *>::type = nullptr) :
        l(other.get_l())
    {}

    /// @brief Convert construct this L color from another L color.
    /// @param other the other L color
    template <typename ThisColorSpace = ColorSpace, typename OtherColorSpace>
    color(const color<OtherColorSpace>& other,
          typename std::enable_if<!std::is_same<color_space_type, OtherColorSpace>::value &&
                                  is_any_of<OtherColorSpace, Lb, Lf>::value, int *>::type = nullptr) :
        l(type::convert<typename color_space_type::l::syntax, typename OtherColorSpace::l::syntax>()(other.get_l()))
    {}

    /// @brief Decompose construct this L color from an LA color.
    /// @param other the LA or RGBA color
    template <typename ThisColorSpace = ColorSpace, typename OtherColorSpace>
    color(const color<OtherColorSpace>& other,
          typename std::enable_if<std::is_same<color_space_type, pure_color_space_t<OtherColorSpace>>::value, int *>::type = 0) :
        l(other.get_l())
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
        return get_l() == other.get_l();
    }

    // CRTP
    void add(const color& other)
    {
        l = type::add<typename color_space_type::l::syntax>()(get_l(), other.get_l());
    }

    // CRTP
    void subtract(const color& other)
    {
        l = type::subtract<typename color_space_type::l::syntax>()(get_l(), other.get_l());
    }

public:
	#include "idlib/color/l.in.h"

    /// @{
    /// @brief Set the value of the luminance component.
    /// @param l the value of the luminance component
    /// @throws out_of_bounds_error @a l is not within the bounds of color_space::min() (inclusive) and color_space::max() (inclusive)
#if defined(ID_COLOR_SETTERS) && 1 == ID_COLOR_SETTERS
    void set_luminance(component_l l)
    {
        if (color_space_type::l::syntax::range().outside(l))
        {
            throw out_of_bounds_error(__FILE__, __LINE__, "luminance component out of bounds");
        }
        this->l = l;
    }

#if defined(ID_COLOR_SHORT_SETTERS) && 1 == ID_COLOR_SHORT_SETTERS
    void set_l(component_l l)
    { set_luminance(l); }
#endif
#endif
    /// @}

}; // struct color

/// @brief Brighten functor for idlib::color<idlib::Lb> and idlib::color<idlib::Lf> values.
template <typename ColorSpace>
struct brighten_functor<color<ColorSpace>,
                        std::enable_if_t<is_any_of<ColorSpace, Lb, Lf>::value>>
{
    using color_space_type = ColorSpace;
    using color_type = color<color_space_type>;

    color_type operator()(const color_type& c, float f)
    {
        float t = (1.0f + f);
        return color_type(type::scale<typename color_space_type::l::syntax>()(c.get_l(), t));
    }

    color_type operator()(const color_type& c, double f)
    {
        double t = (1.0 + f);
        return color_type(type::scale<typename color_space_type::l::syntax>()(c.get_l(), t));
    }

}; // struct brighten_functor

/// @brief Darken functor for idlib::color<idlib::Lb> and idlib::color<idlib::Lf> values.
template <typename ColorSpace>
struct darken_functor<color<ColorSpace>,
                      std::enable_if_t<is_any_of<ColorSpace, Lb, Lf>::value>>
{
    using color_space_type = ColorSpace;
    using color_type = color<color_space_type>;

    color_type operator()(const color_type& c, float f)
    {
        float t = (1.0f - f);
        return color_type(type::scale<typename color_space_type::l::syntax>()(c.get_l(), t));
    }

    color_type operator()(const color_type& c, double f)
    {
        double t = (1.0 - f);
        return color_type(type::scale<typename color_space_type::l::syntax>()(c.get_l(), t));
    }

}; // struct darken_functor

/// @brief Inversion functor for idlib::color<idlib::Lf> and idlib::color<idlib::Lb> values.
/// @remark Given a color \f$(l)\f$ in real-valued, normalized L space,
/// then corresponding inverted color is \f$(1-l)\f$. Inverting a
/// color twice yields the same color (modula floating-point precision).
/// @remark The corresponding inverted color is also known as the complementary color.
template <typename ColorSpace>
struct invert_functor<color<ColorSpace>,
                      std::enable_if_t<is_any_of<ColorSpace, Lb, Lf>::value>>
{
    using color_space_type = ColorSpace;
    using color_type = color<color_space_type>;

    color_type operator()(const color_type& x) const
    {
        return color_type(type::invert<typename color_space_type::l::syntax>()(x.get_l()));
    }

}; // struct invert_functor

/// @brief Lineary interpolate functor for idlib::color<idlib::Lf> values.
template <typename ColorSpace>
struct lineary_interpolate_functor<color<ColorSpace>, float, std::enable_if_t<std::is_same<ColorSpace, Lf>::value>>
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
        return color_type(range_l.clamp(lineary_interpolate(x.get_l(), y.get_l(), mu)));
    }

}; // struct lineary_interpolate_functor

} // namespace idlib
