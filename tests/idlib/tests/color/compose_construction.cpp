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

#include "gtest/gtest.h"
#include "idlib/idlib.hpp"

namespace idlib { namespace tests { namespace color {

namespace compose_construction {

TEST(compose_construction_rgbb_lb, compose_construct_rgbb_lb)
{
    using source = idlib::color<idlib::Lb>;
    using target = idlib::color<idlib::RGBb>;
    ASSERT_EQ(target::white(), target(source::white()));
    ASSERT_EQ(target::black(), target(source::black()));
}

TEST(compose_construction_rgbf_lf, compose_construct_rgbf_Lf)
{
    using source = idlib::color<idlib::Lf>;
    using target = idlib::color<idlib::RGBf>;
    ASSERT_EQ(target::white(), target(source::white()));
    ASSERT_EQ(target::black(), target(source::black()));
}

TEST(compose_construction_rgbab_lab, compose_construct_rgbab_lab)
{
    using source = idlib::color<idlib::LAb>;
    using target = idlib::color<idlib::RGBAb>;
    ASSERT_EQ(target::white(), target(source::white()));
    ASSERT_EQ(target::black(), target(source::black()));
}

TEST(compose_construction_rgbaf_laf, compose_construct_rgbaf_laf)
{
    using source = idlib::color<idlib::LAf>;
    using target = idlib::color<idlib::RGBAf>;
    ASSERT_EQ(target::white(), target(source::white()));
    ASSERT_EQ(target::black(), target(source::black()));
}

} // namespace compose_construction

namespace compose_construction {

TEST(compose_construction_lab_lb_ab, compose_construct_lab_lb_ab)
{
    using color_space = idlib::LAb;
    using color = idlib::color<color_space>;

    using pure_color_space = idlib::pure_color_space_t<color_space>;
    using pure_color = idlib::color<pure_color_space>;

    using pure_opacity_space = idlib::pure_opacity_space_t<color_space>;
    using pure_opacity = idlib::color<pure_opacity_space>;

    ASSERT_EQ(color(pure_color::white(), pure_opacity::opaque()), color::white());
    ASSERT_EQ(color(pure_color::black(), pure_opacity::opaque()), color::black());
    ASSERT_EQ(color(pure_color::grey(), pure_opacity::opaque()), color::grey());
}

TEST(compose_construction_lab_lb_ab, compose_construct_rgbab_rgbb_ab)
{
    using color_space = idlib::RGBAb;
    using color = idlib::color<color_space>;

    using pure_color_space = idlib::pure_color_space_t<color_space>;
    using pure_color = idlib::color<pure_color_space>;

    using pure_opacity_space = idlib::pure_opacity_space_t<color_space>;
    using pure_opacity = idlib::color<pure_opacity_space>;

    ASSERT_EQ(color(pure_color::white(), pure_opacity::opaque()), color::white());
    ASSERT_EQ(color(pure_color::black(), pure_opacity::opaque()), color::black());
    ASSERT_EQ(color(pure_color::red(), pure_opacity::opaque()), color::red());
    ASSERT_EQ(color(pure_color::green(), pure_opacity::opaque()), color::green());
    ASSERT_EQ(color(pure_color::blue(), pure_opacity::opaque()), color::blue());
    ASSERT_EQ(color(pure_color::cyan(), pure_opacity::opaque()), color::cyan());
    ASSERT_EQ(color(pure_color::magenta(), pure_opacity::opaque()), color::magenta());
    ASSERT_EQ(color(pure_color::yellow(), pure_opacity::opaque()), color::yellow());
}

} // namespace compose_construction

} } } // namespace idlib::tests::color
