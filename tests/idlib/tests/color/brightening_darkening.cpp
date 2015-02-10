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
#include "idlib/tests/color/color_generator.hpp"

namespace id { namespace tests { namespace color { namespace brightening_darkening {

template <typename S, typename E = void>
struct basic_test1;

template <typename S>
struct basic_test1<S,std::enable_if_t<id::is_any_of<S, id::Lb, id::Lf, id::LAb, id::LAf, id::RGBb, id::RGBf, id::RGBAb, id::RGBAf>::value>>
{
    void operator()() const
    {
        using C = id::color<S>;
        static const std::vector<C> colors = color_generator<S>()();
        for (const auto& color : colors)
        {
            // darken(c,0) = c (1 - 0) = c
            // brighten(c,0) = c (1 + 0) = c
            ASSERT_EQ(color, id::darken(color, 0.0f));
            ASSERT_EQ(color, id::darken(color, 0.0));
            ASSERT_EQ(color, id::brighten(color, 0.0f));
            ASSERT_EQ(color, id::brighten(color, 0.0));
            // darken(c,-1) = c (1 - (-1)) = 2c
            // brighten(c,+1) = c (1 + (+1)) = 2c
            ASSERT_EQ(id::darken(color, -1.0), id::brighten(color, +1.0));
            ASSERT_EQ(id::darken(color, -1.0f), id::brighten(color, +1.0f));
            // darken(c,+2) = c (1 - (+2)) = -1c
            // brighten(c,-2) c (1 + (-2)) = -1c
            ASSERT_EQ(id::darken(color, +1.0), id::brighten(color, -1.0));
            ASSERT_EQ(id::darken(color, +1.0f), id::brighten(color, -1.0f));
        }
    }
};

TEST(brightening_darkening_lf, brighten_darken_lf)
{
    basic_test1<id::Lf>()();
}

TEST(brightening_darkening_lb, brighten_darken_lb)
{
    basic_test1<id::Lb>()();
}

TEST(brightening_darkening_laf, brighten_darken_laf)
{
    basic_test1<id::LAf>()();
}

TEST(brightening_darkening_lab, brighten_darken_lab)
{
    basic_test1<id::LAb>()();
}

TEST(brightening_darkening_rgbf, brighten_darken_rgbf)
{
    basic_test1<id::RGBf>()();
}

TEST(brightening_darkening_rgbb, brighten_darken_rgbb)
{
    basic_test1<id::RGBb>()();
}

TEST(brightening_darkening_rgbaf, brighten_darken_rgbaf)
{
    basic_test1<id::RGBAf>()();
}

TEST(brightening_darkening_rgbab, brighten_darken_rgbab)
{
    basic_test1<id::RGBAb>()();
}

} } } } // namespace id::tests::color::brightening_darkening
