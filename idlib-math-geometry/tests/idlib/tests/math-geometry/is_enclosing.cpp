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

#include "idlib/tests/math-geometry/utilities.hpp"

namespace idlib::tests {

TEST(is_enclosing, axis_aligned_box_3s_axis_aligned_box_3s) {
    auto x = axis_aligned_box_3s(point_3s(-1.0f, -1.0f, -1.0f), point_3s(+1.0f, +1.0f, +1.0f));
    auto y = Utilities::get_contained_axis_aligned_box_3s(x);
    ASSERT_TRUE(idlib::is_enclosing(x, y));
    y = Utilities::get_non_contained_axis_aligned_box_3s(x);
    ASSERT_TRUE(!idlib::is_enclosing(x, y));
}

TEST(is_enclosing, axis_aligned_box_3s_point_3s) {
    auto x = axis_aligned_box_3s(point_3s(-1.0f, -1.0f, -1.0f), point_3s(+1.0f, +1.0f, +1.0f));
    auto y = Utilities::get_contained_point_3s(x);
    ASSERT_TRUE(idlib::is_enclosing(x, y));
    y = Utilities::get_non_contained_point_3s(x);
    ASSERT_TRUE(!idlib::is_enclosing(x, y));
}

TEST(is_enclosing, sphere_3s_point_3s) {
    auto x = sphere_3s(point_3s(0.0f, 0.0f, 0.0f), 1.0f);
    auto y = Utilities::get_contained_point_3s(x);
    ASSERT_TRUE(idlib::is_enclosing(x, y));
    y = Utilities::get_non_contained_point_3s(x);
    ASSERT_TRUE(!idlib::is_enclosing(x, y));
}

TEST(is_enclosing, sphere_3s_sphere_3s) {
    auto x = sphere_3s(point_3s(0.0f, 0.0f, 0.0f), 1.0f);
    auto y = Utilities::get_contained_sphere_3s(x);
    ASSERT_TRUE(idlib::is_enclosing(x, y));
    y = Utilities::get_non_contained_sphere_3s(x);
    ASSERT_TRUE(!idlib::is_enclosing(x, y));
}

TEST(is_enclosing, point_3s_point_3s) {
    auto x = point_3s(0.0f, 0.0f, 0.0f);
    auto y = Utilities::get_contained_point_3s(x);
    ASSERT_TRUE(idlib::is_enclosing(x, y));
    y = Utilities::get_non_contained_point_3s(x);
    ASSERT_TRUE(!idlib::is_enclosing(x, y));
}

} // namespace idlib::tests
