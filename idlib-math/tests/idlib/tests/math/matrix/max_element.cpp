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

using interval_i = idlib::interval<int>;
using matrix_3i_3i = idlib::matrix<int, 3, 3>;

TEST(max_element_test, matrix_3i_3i)
{
    #if defined(IDLIB_MATH_MATRIX_WITH_RANDOM) && 1 == IDLIB_MATH_MATRIX_WITH_RANDOM
    for (size_t i = 0; i < 1000; ++i)
    {
        auto interval = interval_i(-1000, +1000);
        auto a = idlib::random<matrix_3i_3i>(interval);
        // Explicitly find the maximal element.
        auto e = a(0);
        for (size_t i = 1, n = matrix_3i_3i::order(); i < n; ++i)
        {
            if (a(i) > e) e = a(i);
        }
        ASSERT_TRUE(e == idlib::max_element(a));
    }
    #endif
}

} // namespace idlib::tests
