// Copyright Michael Heilmann 2016, 2017.
//
// This file is part of Idlib.
//
// Idlib is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Idlib is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Idlib. If not, see <http://www.gnu.org/licenses/>.

#include "gtest/gtest.h"
#include <idlib/idlib.hpp>

namespace id { namespace tests { namespace color { namespace inversion {

TEST(lb_inversion, invert_lb)
{
    using color_space = id::Lb;
    using color = id::color<color_space>;

    ASSERT_EQ(color::white(), id::invert(color::black()));
    ASSERT_EQ(color::black(), id::invert(color::white()));
}

TEST(lab_inversion, invert_lab)
{
    using color_space = id::LAb;
    using color = id::color<color_space>;

    using opaque_color_space = id::pure_color_space_t<color_space>;
    using opaque_color = id::color<opaque_color_space>;

    using alpha_color_space = id::Ab;
    using alpha_color = id::color<alpha_color_space>;

    ASSERT_EQ(color(opaque_color::black(), alpha_color::transparent()), id::invert(color::white()));
    ASSERT_EQ(color(opaque_color::white(), alpha_color::transparent()), id::invert(color::black()));
}

TEST(rgbb_inversion, invert_rgbb)
{
    using color_space = id::RGBb;
    using color = id::color<color_space>;

    ASSERT_EQ(color::black(), id::invert(color::white()));
    ASSERT_EQ(color::white(), id::invert(color::black()));
    ASSERT_EQ(color::cyan(), id::invert(color::red()));
    ASSERT_EQ(color::magenta(), id::invert(color::green()));
    ASSERT_EQ(color::yellow(), id::invert(color::blue()));
    ASSERT_EQ(color::red(), id::invert(color::cyan()));
    ASSERT_EQ(color::green(), id::invert(color::magenta()));
    ASSERT_EQ(color::blue(), id::invert(color::yellow()));
}

TEST(rgbab_inversion, invert_rgbab)
{
    using color_space = id::RGBAb;
    using color = id::color<color_space>;

    using opaque_color_space = id::pure_color_space_t<color_space>;
    using opaque_color = id::color<opaque_color_space>;

    using alpha_color_space = id::Ab;
    using alpha_color = id::color<alpha_color_space>;

    ASSERT_EQ(color(opaque_color::black(), alpha_color::transparent()), id::invert(color::white()));
    ASSERT_EQ(color(opaque_color::white(), alpha_color::transparent()), id::invert(color::black()));
    ASSERT_EQ(color(opaque_color::cyan(), alpha_color::transparent()), id::invert(color::red()));
    ASSERT_EQ(color(opaque_color::magenta(), alpha_color::transparent()), id::invert(color::green()));
    ASSERT_EQ(color(opaque_color::yellow(), alpha_color::transparent()), id::invert(color::blue()));
    ASSERT_EQ(color(opaque_color::red(), alpha_color::transparent()), id::invert(color::cyan()));
    ASSERT_EQ(color(opaque_color::green(), alpha_color::transparent()), id::invert(color::magenta()));
    ASSERT_EQ(color(opaque_color::blue(), alpha_color::transparent()), id::invert(color::yellow()));
}

} } } } // namespace id::tests::color::inversion
