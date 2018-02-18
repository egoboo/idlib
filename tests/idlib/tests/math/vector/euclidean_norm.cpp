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
	
using scalar = single;
using vector_3s = idlib::vector<single, 3>;

/// @brief Assert the Euclidean norm is zero for a zero vector.
/// Assert for \f$(1,0,0)\f$, \f$(0,1,0)\f$, and \f$(0,0,1)\f$ it is one.
TEST(vector_3s_test, euclidean_norm)
{
	vector_3s x;
	
	//
	x = idlib::zero<vector_3s>();
	ASSERT_EQ(idlib::euclidean_norm(x), idlib::zero<scalar>());
	
	//
    x = vector_3s::unit(0); 
    ASSERT_EQ(idlib::euclidean_norm(x), idlib::one<scalar>());
	
	//
    x = vector_3s::unit(1);
    ASSERT_EQ(idlib::euclidean_norm(x), idlib::one<scalar>());
    
	//
	x = vector_3s::unit(2);
    ASSERT_EQ(idlib::euclidean_norm(x), idlib::one<scalar>());
}

} // namespace idlib::tests
