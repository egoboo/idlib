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
#include <idlib/idlib.hpp>

namespace idlib { namespace tests { namespace color { namespace inversion {

TEST(lb_inversion, invert_lb)
{
    using color_space = idlib::Lb;
    using color = idlib::color<color_space>;

    ASSERT_EQ(color::white(), idlib::invert(color::black()));
    ASSERT_EQ(color::black(), idlib::invert(color::white()));
}

TEST(lab_inversion, invert_lab)
{
    using color_space = idlib::LAb;
    using color = idlib::color<color_space>;

    using opaque_color_space = idlib::pure_color_space_t<color_space>;
    using opaque_color = idlib::color<opaque_color_space>;

    using alpha_color_space = idlib::Ab;
    using alpha_color = idlib::color<alpha_color_space>;

    ASSERT_EQ(color(opaque_color::black(), alpha_color::transparent()), idlib::invert(color::white()));
    ASSERT_EQ(color(opaque_color::white(), alpha_color::transparent()), idlib::invert(color::black()));
}

TEST(rgbb_inversion, invert_rgbb)
{
    using color_space = idlib::RGBb;
    using color = idlib::color<color_space>;

    ASSERT_EQ(color::black(), idlib::invert(color::white()));
    ASSERT_EQ(color::white(), idlib::invert(color::black()));
    ASSERT_EQ(color::cyan(), idlib::invert(color::red()));
    ASSERT_EQ(color::magenta(), idlib::invert(color::green()));
    ASSERT_EQ(color::yellow(), idlib::invert(color::blue()));
    ASSERT_EQ(color::red(), idlib::invert(color::cyan()));
    ASSERT_EQ(color::green(), idlib::invert(color::magenta()));
    ASSERT_EQ(color::blue(), idlib::invert(color::yellow()));
}

TEST(rgbab_inversion, invert_rgbab)
{
    using color_space = idlib::RGBAb;
    using color = idlib::color<color_space>;

    using opaque_color_space = idlib::pure_color_space_t<color_space>;
    using opaque_color = idlib::color<opaque_color_space>;

    using alpha_color_space = idlib::Ab;
    using alpha_color = idlib::color<alpha_color_space>;

    ASSERT_EQ(color(opaque_color::black(), alpha_color::transparent()), idlib::invert(color::white()));
    ASSERT_EQ(color(opaque_color::white(), alpha_color::transparent()), idlib::invert(color::black()));
    ASSERT_EQ(color(opaque_color::cyan(), alpha_color::transparent()), idlib::invert(color::red()));
    ASSERT_EQ(color(opaque_color::magenta(), alpha_color::transparent()), idlib::invert(color::green()));
    ASSERT_EQ(color(opaque_color::yellow(), alpha_color::transparent()), idlib::invert(color::blue()));
    ASSERT_EQ(color(opaque_color::red(), alpha_color::transparent()), idlib::invert(color::cyan()));
    ASSERT_EQ(color(opaque_color::green(), alpha_color::transparent()), idlib::invert(color::magenta()));
    ASSERT_EQ(color(opaque_color::blue(), alpha_color::transparent()), idlib::invert(color::yellow()));
}

} } } } // namespace idlib::tests::color::inversion
