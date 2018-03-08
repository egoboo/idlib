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

namespace idlib::tests::color::addition_subtraction {

TEST(addition_subtraction_ab, add_subtract_ab)
{
    using color = idlib::color<idlib::Ab>;
    color::transparent() + color::transparent();
    color::transparent() + color::opaque();
    color::opaque() + color::transparent();
    color::opaque() + color::opaque();
    color::transparent() - color::transparent();
    color::transparent() - color::opaque();
    color::opaque() - color::transparent();
    color::opaque() - color::opaque();
}

TEST(addition_subtraction_af, add_subtract_af)
{
    using color = idlib::color<idlib::Af>;
    color::transparent() + color::transparent();
    color::transparent() + color::opaque();
    color::opaque() + color::transparent();
    color::opaque() + color::opaque();
    color::transparent() - color::transparent();
    color::transparent() - color::opaque();
    color::opaque() - color::transparent();
    color::opaque() - color::opaque();
}


TEST(addition_subtraction_lb, add_subtract_lb)
{
    using color = idlib::color<idlib::Lb>;
    color::black() + color::black();
    color::black() + color::white();
    color::white() + color::black();
    color::white() + color::white();
    color::black() - color::black();
    color::black() - color::white();
    color::white() - color::black();
    color::white() - color::white();
}

TEST(addition_subtraction_lf, add_subtract_lf)
{
    using color = idlib::color<idlib::Lf>;
    color::black() + color::black();
    color::black() + color::white();
    color::white() + color::black();
    color::white() + color::white();
    color::black() - color::black();
    color::black() - color::white();
    color::white() - color::black();
    color::white() - color::white();
}

TEST(addition_subtraction_lab, add_subtract_lab)
{
    using color = idlib::color<idlib::LAb>;
    color::black() + color::black();
    color::black() + color::white();
    color::white() + color::black();
    color::white() + color::white();
    color::black() - color::black();
    color::black() - color::white();
    color::white() - color::black();
    color::white() - color::white();
}

TEST(addition_subtraction_laf, add_subtract_laf)
{
    using color = idlib::color<idlib::LAf>;
    color::black() + color::black();
    color::black() + color::white();
    color::white() + color::black();
    color::white() + color::white();
    color::black() - color::black();
    color::black() - color::white();
    color::white() - color::black();
    color::white() - color::white();
}

TEST(addition_subtraction_rgbb, add_subtract_rgbb)
{
    using color = idlib::color<idlib::RGBAf>;
    color::black() + color::black();
    color::black() + color::white();
    color::white() + color::black();
    color::white() + color::white();
    color::black() - color::black();
    color::black() - color::white();
    color::white() - color::black();
    color::white() - color::white();
}

TEST(addition_subtraction_rgbf, add_subtract_rgbf)
{
    using color = idlib::color<idlib::RGBf>;
    color::black() + color::black();
    color::black() + color::white();
    color::white() + color::black();
    color::white() + color::white();
    color::black() - color::black();
    color::black() - color::white();
    color::white() - color::black();
    color::white() - color::white();
}

TEST(addition_subtraction_rgbab, add_subtract_rgbab)
{
    using color = idlib::color<idlib::RGBAb>;
    color::black() + color::black();
    color::black() + color::white();
    color::white() + color::black();
    color::white() + color::white();
    color::black() - color::black();
    color::black() - color::white();
    color::white() - color::black();
    color::white() - color::white();
}

TEST(addition_subtraction_rgbaf, add_subtract_rgbaf)
{
    using color = idlib::color<idlib::RGBAf>;
    color::black() + color::black();
    color::black() + color::white();
    color::white() + color::black();
    color::white() + color::white();
    color::black() - color::black();
    color::black() - color::white();
    color::white() - color::black();
    color::white() - color::white();
}

} // namespace idlib::tests::color::addition_subtraction
