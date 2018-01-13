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

namespace id { namespace tests { namespace color { namespace interpolation {

namespace lf_interpolation {

using color = id::color<id::Lf>;

static void test(const color& x, const color& y)
{
    ASSERT_EQ(x, id::lineary_interpolate(x, y, 0.0f));
    ASSERT_EQ(y, id::lineary_interpolate(x, y, 1.0f));
}

TEST(lf_interpolation, interpolate_lf)
{
    test(color::black(), color::black());
    test(color::black(), color::white());
    test(color::white(), color::black());
    test(color::white(), color::white());
}

}

namespace laf_interpolation {

using color = id::color<id::Lf>;

static void test(const color& x, const color& y)
{
    ASSERT_EQ(x, id::lineary_interpolate(x, y, 0.0f));
    ASSERT_EQ(y, id::lineary_interpolate(x, y, 1.0f));
}

TEST(laf_interpolation, interpolate_laf)
{
    test(color::black(), color::black());
    test(color::black(), color::white());
    test(color::white(), color::black());
    test(color::white(), color::white());
}

}

namespace rgbf_interpolation {

using color = id::color<id::RGBf>;

static void test(const color& x, const color& y)
{
    ASSERT_EQ(x, id::lineary_interpolate(x, y, 0.0f));
    ASSERT_EQ(y, id::lineary_interpolate(x, y, 1.0f));
}

TEST(rgbf_interpolation, interpolate_rgbf)
{
    test(color::red(), color::red());
    test(color::red(), color::green());
    test(color::red(), color::blue());

    test(color::green(), color::green());
    test(color::green(), color::blue());
    test(color::green(), color::red());

    test(color::blue(), color::blue());
    test(color::blue(), color::green());
    test(color::blue(), color::red());
}

}

namespace rgbaf_interpolation {

using color = id::color<id::RGBAf>;

static void test(const color& x, const color& y)
{
    ASSERT_EQ(x, id::lineary_interpolate(x, y, 0.0f));
    ASSERT_EQ(y, id::lineary_interpolate(x, y, 1.0f));
}

TEST(rgbaf_interpolation, interpolate_rgbaf)
{
    test(color::red(), color::red());
    test(color::red(), color::green());
    test(color::red(), color::blue());

    test(color::green(), color::green());
    test(color::green(), color::blue());
    test(color::green(), color::red());

    test(color::blue(), color::blue());
    test(color::blue(), color::green());
    test(color::blue(), color::red());
}

}

} } } } // namespace id::tests::color::interpolation
