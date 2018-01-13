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

namespace id { namespace tests { namespace color {

namespace copy_construction {

TEST(copy_construction_lb_lb, copy_construct_lb_lb)
{
    id::color<id::Lb> x;
    auto y = id::color<id::Lb>(x);
    ASSERT_EQ(x, y);
}

TEST(copy_construction_lf_lf, copy_construct_lf_lf)
{
    id::color<id::Lf> x;
    auto y = id::color<id::Lf>(x);
    ASSERT_EQ(x, y);
}

TEST(copy_construction_lab_lab, copy_construct_lab_lab)
{
    id::color<id::LAb> x;
    auto y = id::color<id::LAb>(x);
    ASSERT_EQ(x, y);
}

TEST(copy_construction_laf_laf, copy_construct_laf_laf)
{
    id::color<id::LAf> x;
    auto y = id::color<id::LAf>(x);
    ASSERT_EQ(x, y);
}

TEST(copy_construction_rgbb_rgbb, copy_construct_rgbb_rgbb)
{
    id::color<id::RGBb> x;
    auto y = id::color<id::RGBb>(x);
    ASSERT_EQ(x, y);
}

TEST(copy_construction_rgbf_rgbf, copy_construct_rgbf_rgbf)
{
    id::color<id::RGBf> x;
    auto y = id::color<id::RGBf>(x);
    ASSERT_EQ(x, y);
}

TEST(copy_construction_rgbab_rgbab, copy_construct_rgbab_rgbab)
{
    id::color<id::RGBAb> x;
    auto y = id::color<id::RGBAb>(x);
    ASSERT_EQ(x, y);
}

TEST(copy_construction_rgbaf_rgbaf, copy_construct_rgbaf_rgbaf)
{
    id::color<id::RGBAf> x;
    auto y = id::color<id::RGBAf>(x);
    ASSERT_EQ(x, y);
}

} // namespace copy_construction

} } } // namespace id::tests::color
