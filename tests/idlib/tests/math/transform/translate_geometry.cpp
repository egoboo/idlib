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

namespace idlib::tests {
	
using vector_3s = idlib::vector<single, 3>;
using point_3s = idlib::point<vector_3s>;
using AxisAlignedBox3f = idlib::axis_aligned_box<point_3s>;
using Line3f = idlib::line<point_3s>;
using AxisAlignedCube3f = idlib::axis_aligned_cube<point_3s>;
using Sphere3f = idlib::sphere<point_3s>;
using Ray3f = idlib::ray<point_3s>;
using Plane3f = idlib::plane<point_3s>;

TEST(translate_test, point_3s)
{
    auto t = vector_3s(+1.0f, +1.0f, +1.0f);
    auto x = point_3s(-1.0f, -1.0f, -1.0f);
    auto y = translate(x, t);
    y = translate(y, -t);
    ASSERT_EQ(x, y);
}

TEST(translate_test, axis_aligned_box_3s)
{
    auto t = vector_3s(+1.0f, +1.0f, +1.0f);
    auto x = AxisAlignedBox3f(point_3s(-1.0f, -1.0f, -1.0f), point_3s(+1.0f, +1.0f, +1.0f));
    auto y = translate(x, t);
    y = translate(y, -t);
    ASSERT_EQ(x, y);
}

TEST(translate_test, axis_aligned_cube_3s)
{
    auto t = vector_3s(+1.0f, +1.0f, +1.0f);
    auto x = AxisAlignedCube3f(point_3s(0.0f, 0.0f, 0.0f), 1.0f);
    auto y = translate(x, t);
    y = translate(y, -t);
    ASSERT_EQ(x, y);
}

TEST(translate_test, sphere_3s)
{
    auto t = vector_3s(+1.0f, +1.0f, +1.0f);
    auto x = Sphere3f(point_3s(0.0f, 0.0f, 0.0f), +1.0f);
    auto y = translate(x, t);
    y = translate(y, -t);
    ASSERT_EQ(x, y);
}

TEST(translate_test, line_3s)
{
    auto t = vector_3s(+1.0f, +1.0f, +1.0f);
    auto x = Line3f(point_3s(-1.0f, -1.0f, -1.0f), point_3s(-1.0f, -1.0f, -1.0f));
    auto y = translate(x, t);
    y = translate(y, -t);
    ASSERT_EQ(x, y);
}

TEST(translate_test, ray_3s)
{
    auto t = vector_3s(+1.0f, +1.0f, +1.0f);
    auto x = Ray3f(point_3s(0.0f, 0.0f, 0.0f), vector_3s(+1.0f,+1.0f,+1.0f));
    auto y = translate(x, t);
    y = idlib::translate(y, -t);
    ASSERT_EQ(x, y);
}

TEST(translate_test, plane_3s)
{
    auto t = vector_3s(+1.0f, +1.0f, +1.0f);
    auto x = Plane3f();
    auto y = translate(x, t);
    y = translate(y, -t);
    ASSERT_EQ(x, y);
}

} // namespace idlib::tests
