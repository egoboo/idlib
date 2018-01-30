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

namespace copy_construction {

TEST(copy_construction_lb_lb, copy_construct_lb_lb)
{
    idlib::color<idlib::Lb> x;
    auto y = idlib::color<idlib::Lb>(x);
    ASSERT_EQ(x, y);
}

TEST(copy_construction_lf_lf, copy_construct_lf_lf)
{
    idlib::color<idlib::Lf> x;
    auto y = idlib::color<idlib::Lf>(x);
    ASSERT_EQ(x, y);
}

TEST(copy_construction_lab_lab, copy_construct_lab_lab)
{
    idlib::color<idlib::LAb> x;
    auto y = idlib::color<idlib::LAb>(x);
    ASSERT_EQ(x, y);
}

TEST(copy_construction_laf_laf, copy_construct_laf_laf)
{
    idlib::color<idlib::LAf> x;
    auto y = idlib::color<idlib::LAf>(x);
    ASSERT_EQ(x, y);
}

TEST(copy_construction_rgbb_rgbb, copy_construct_rgbb_rgbb)
{
    idlib::color<idlib::RGBb> x;
    auto y = idlib::color<idlib::RGBb>(x);
    ASSERT_EQ(x, y);
}

TEST(copy_construction_rgbf_rgbf, copy_construct_rgbf_rgbf)
{
    idlib::color<idlib::RGBf> x;
    auto y = idlib::color<idlib::RGBf>(x);
    ASSERT_EQ(x, y);
}

TEST(copy_construction_rgbab_rgbab, copy_construct_rgbab_rgbab)
{
    idlib::color<idlib::RGBAb> x;
    auto y = idlib::color<idlib::RGBAb>(x);
    ASSERT_EQ(x, y);
}

TEST(copy_construction_rgbaf_rgbaf, copy_construct_rgbaf_rgbaf)
{
    idlib::color<idlib::RGBAf> x;
    auto y = idlib::color<idlib::RGBAf>(x);
    ASSERT_EQ(x, y);
}

} // namespace copy_construction

} } } // namespace idlib::tests::color
