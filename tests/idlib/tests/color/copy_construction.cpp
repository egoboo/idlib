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
