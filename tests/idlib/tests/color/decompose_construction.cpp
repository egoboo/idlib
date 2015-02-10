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

namespace decompose_construction {

TEST(decompose_construction_lb_ab_lab, decompose_construct_lb_ab_lab)
{
    auto source = id::color<id::LAb>::white();
    auto prefix = id::color<id::Lb>(source);
    auto suffix = id::color<id::Ab>(source);
    auto target = id::color<id::LAb>(prefix, suffix);
    ASSERT_EQ(target, source);
}

TEST(decompose_construction_rgbb_ab_rgbab, decompose_construct_lb_ab_lab)
{
    auto source = id::color<id::RGBAb>::white();
    auto prefix = id::color<id::RGBb>(source);
    auto suffix = id::color<id::Ab>(source);
    auto target = id::color<id::RGBAb>(prefix, suffix);
    ASSERT_EQ(target, source);
}

} // namespace decompose_construction

} } } // namespace id::tests::color
