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
using vector_3i = idlib::vector<int, 3>;

TEST(zip_min_test, vector_3i)
{
    for (size_t i = 0; i < 1000; ++i)
    {
        auto interval = interval_i(-1000, +1000);
        auto a = idlib::random<vector_3i>(interval);
        auto b = idlib::random<vector_3i>(interval);
        auto c = idlib::zip_min(a,b);
        for (size_t i = 1, n = vector_3i::dimensionality(); i < n; ++i)
        {
            ASSERT_TRUE(c[i] == std::min(a[i], b[i]));
        }
    }
}

} // namespace idlib::tests
