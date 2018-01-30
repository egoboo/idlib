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
#include "idlib/tests/color/color_generator.hpp"

namespace idlib { namespace tests { namespace color { namespace brightening_darkening {

template <typename S, typename E = void>
struct basic_test1;

template <typename S>
struct basic_test1<S,std::enable_if_t<idlib::is_any_of<S, idlib::Lb, idlib::Lf, idlib::LAb, idlib::LAf, idlib::RGBb, idlib::RGBf, idlib::RGBAb, idlib::RGBAf>::value>>
{
    void operator()() const
    {
        using C = idlib::color<S>;
        static const std::vector<C> colors = color_generator<S>()();
        for (const auto& color : colors)
        {
            // darken(c,0) = c (1 - 0) = c
            // brighten(c,0) = c (1 + 0) = c
            ASSERT_EQ(color, idlib::darken(color, 0.0f));
            ASSERT_EQ(color, idlib::darken(color, 0.0));
            ASSERT_EQ(color, idlib::brighten(color, 0.0f));
            ASSERT_EQ(color, idlib::brighten(color, 0.0));
            // darken(c,-1) = c (1 - (-1)) = 2c
            // brighten(c,+1) = c (1 + (+1)) = 2c
            ASSERT_EQ(idlib::darken(color, -1.0), idlib::brighten(color, +1.0));
            ASSERT_EQ(idlib::darken(color, -1.0f), idlib::brighten(color, +1.0f));
            // darken(c,+2) = c (1 - (+2)) = -1c
            // brighten(c,-2) c (1 + (-2)) = -1c
            ASSERT_EQ(idlib::darken(color, +1.0), idlib::brighten(color, -1.0));
            ASSERT_EQ(idlib::darken(color, +1.0f), idlib::brighten(color, -1.0f));
        }
    }
};

TEST(brightening_darkening_lf, brighten_darken_lf)
{
    basic_test1<idlib::Lf>()();
}

TEST(brightening_darkening_lb, brighten_darken_lb)
{
    basic_test1<idlib::Lb>()();
}

TEST(brightening_darkening_laf, brighten_darken_laf)
{
    basic_test1<idlib::LAf>()();
}

TEST(brightening_darkening_lab, brighten_darken_lab)
{
    basic_test1<idlib::LAb>()();
}

TEST(brightening_darkening_rgbf, brighten_darken_rgbf)
{
    basic_test1<idlib::RGBf>()();
}

TEST(brightening_darkening_rgbb, brighten_darken_rgbb)
{
    basic_test1<idlib::RGBb>()();
}

TEST(brightening_darkening_rgbaf, brighten_darken_rgbaf)
{
    basic_test1<idlib::RGBAf>()();
}

TEST(brightening_darkening_rgbab, brighten_darken_rgbab)
{
    basic_test1<idlib::RGBAb>()();
}

} } } } // namespace idlib::tests::color::brightening_darkening
