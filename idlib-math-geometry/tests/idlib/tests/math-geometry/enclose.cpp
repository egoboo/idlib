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

TEST(enclose, sphere_3f_sphere_3f) {
    auto source = sphere_3s(point_3s(3.0f, 5.0f, 7.0f), 3.0f);
    auto target = idlib::enclose<sphere_3s>(source);
}

TEST(enclose, aabb_3f_aabb_3f) {
    auto source = axis_aligned_box_3s(point_3s(-1.0f, -2.0f, -3.0f), point_3s(+1.0f, +2.0f, +3.0f));
    auto target = idlib::enclose<axis_aligned_box_3s>(source);
}

TEST(enclose, sphere_3f_aabb_3f) {
    auto source = sphere_3s(point_3s(3.0f, 5.0f, 7.0f), 3.0f);
    auto target = idlib::enclose<axis_aligned_box_3s>(source);
}

TEST(enclose, axis_aligned_box_3f_sphere_3f) {
    auto source = axis_aligned_box_3s(point_3s(-1.0f, -2.0f, -3.0f), point_3s(+1.0f, +2.0f, 3.0f));
    auto target = idlib::enclose<sphere_3s>(source);
}

TEST(enclose, axis_aligned_cube_3f_axis_aligned_box_3f) {
    auto source = axis_aligned_cube_3s(point_3s(-1.0f, -2.0f, -3.0f), 3.0f);
    auto target = idlib::enclose<axis_aligned_box_3s>(source);
}

TEST(enclose, axis_aligned_box_3f_axis_aligned_cube_3f) {
    auto source = axis_aligned_box_3s(point_3s(-1.0f, -2.0f, -3.0f), point_3s(+1.0f, +2.0f, 3.0f));
    auto target = idlib::enclose<axis_aligned_cube_3s>(source);
}

} // namespace idlib::tests
