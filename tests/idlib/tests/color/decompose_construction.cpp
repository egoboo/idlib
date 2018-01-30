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

namespace decompose_construction {

TEST(decompose_construction_lb_ab_lab, decompose_construct_lb_ab_lab)
{
    auto source = idlib::color<idlib::LAb>::white();
    auto prefix = idlib::color<idlib::Lb>(source);
    auto suffix = idlib::color<idlib::Ab>(source);
    auto target = idlib::color<idlib::LAb>(prefix, suffix);
    ASSERT_EQ(target, source);
}

TEST(decompose_construction_rgbb_ab_rgbab, decompose_construct_lb_ab_lab)
{
    auto source = idlib::color<idlib::RGBAb>::white();
    auto prefix = idlib::color<idlib::RGBb>(source);
    auto suffix = idlib::color<idlib::Ab>(source);
    auto target = idlib::color<idlib::RGBAb>(prefix, suffix);
    ASSERT_EQ(target, source);
}

} // namespace decompose_construction

} } } // namespace idlib::tests::color
