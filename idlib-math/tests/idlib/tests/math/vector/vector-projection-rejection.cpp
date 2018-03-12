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
#include "idlib/math.hpp"

namespace idlib::tests {

using vector_3s = idlib::vector<single, 3>;

TEST(vector_projection_rejection_test, vector_3s_special)
    {
        vector_3s x, y, z;
        // vector x = {1, 4, 0} on vector y = {4, 2, 4} yields z = {4/3, 2/3, 4/3}
        x = vector_3s(1, 4, 0);
        y = vector_3s(4, 2, 4);
        z = idlib::vector_projection(x, y);
        ASSERT_TRUE(vector_3s(4.0f / 3.0f, 2.0f / 3.0f, 4.0f / 3.0f) == z);
}

} // namespace idlib::tests
