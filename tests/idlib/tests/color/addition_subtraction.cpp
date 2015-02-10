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

namespace id { namespace tests { namespace color { namespace addition_subtraction {

TEST(addition_subtraction_ab, add_subtract_ab)
{
    using color = id::color<id::Ab>;
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
    using color = id::color<id::Af>;
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
    using color = id::color<id::Lb>;
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
    using color = id::color<id::Lf>;
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
    using color = id::color<id::LAb>;
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
    using color = id::color<id::LAf>;
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
    using color = id::color<id::RGBAf>;
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
    using color = id::color<id::RGBf>;
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
    using color = id::color<id::RGBAb>;
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
    using color = id::color<id::RGBAf>;
    color::black() + color::black();
    color::black() + color::white();
    color::white() + color::black();
    color::white() + color::white();
    color::black() - color::black();
    color::black() - color::white();
    color::white() - color::black();
    color::white() - color::white();
}

} } } } // namespace id::tests::color::addition_subtraction
