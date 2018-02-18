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

TEST(arithmetic_array_2d_test, trace)
{
	using A = idlib::arithmetic_array_2d<single, 4, 4, idlib::zero_functor<single>>;
    A a;
    // trace of non-empty zero N x N array must be zero
    a = idlib::zero<A>();
    ASSERT_EQ(idlib::zero<single>(), idlib::trace(a));
    // trace of non-empty identity N x N array must be its width and height
    a = idlib::identity<A>();
    ASSERT_EQ(A::width(), idlib::trace(a));
    ASSERT_EQ(A::height(), idlib::trace(a));
}

} // namespace idlib::tests
