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

/// @brief Assert idlib::conditional_generator::operator(size_t) has proper return type.
TEST(generators, conditional_generator)
{
    using namespace idlib;
    using namespace std;
    auto g = make_conditional_generator(1, constant_generator<float>(one<float>()),
                                           constant_generator<float>(zero<float>()));
    auto v = g(0);
    static_assert(std::is_floating_point<decltype(v)>::value, "not a floating point value");
}

TEST(dimensionality_testing, test_dimensionality)
{
    ASSERT_FALSE(idlib::is_dimensionality<0>::value);
    ASSERT_FALSE(idlib::is_dimensionality_v<0>);
    ASSERT_TRUE(idlib::is_dimensionality<1>::value);
    ASSERT_TRUE(idlib::is_dimensionality_v<1>);
    ASSERT_TRUE(idlib::is_dimensionality<std::numeric_limits<size_t>::max()>::value);
    ASSERT_TRUE(idlib::is_dimensionality_v<std::numeric_limits<size_t>::max()>);
}

TEST(one_testing, test_one_types)
{
    static_assert(std::is_same<decltype(idlib::one<signed short>()), signed short>::value, "");
    static_assert(std::is_same<decltype(idlib::one<unsigned short>()), unsigned short>::value, "");
    static_assert(std::is_same<decltype(idlib::one<signed int>()), signed int>::value, "");
    static_assert(std::is_same<decltype(idlib::one<unsigned int>()), unsigned int>::value, "");
    static_assert(std::is_same<decltype(idlib::one<signed long>()), signed long>::value, "");
    static_assert(std::is_same<decltype(idlib::one<unsigned long>()), unsigned long>::value, "");
    static_assert(std::is_same<decltype(idlib::one<signed long long>()), signed long long>::value, "");
    static_assert(std::is_same<decltype(idlib::one<unsigned long long>()), unsigned long long>::value, "");
    static_assert(std::is_same<decltype(idlib::one<float>()), float>::value, "");
    static_assert(std::is_same<decltype(idlib::one<double>()), double>::value, "");
}

TEST(zero_testing, test_zero_types)
{
    static_assert(std::is_same<decltype(idlib::zero<signed short>()), signed short>::value, "");
    static_assert(std::is_same<decltype(idlib::zero<unsigned short>()), unsigned short>::value, "");
    static_assert(std::is_same<decltype(idlib::zero<signed int>()), signed int>::value, "");
    static_assert(std::is_same<decltype(idlib::zero<unsigned int>()), unsigned int>::value, "");
    static_assert(std::is_same<decltype(idlib::zero<signed long>()), signed long>::value, "");
    static_assert(std::is_same<decltype(idlib::zero<unsigned long>()), unsigned long>::value, "");
    static_assert(std::is_same<decltype(idlib::zero<signed long long>()), signed long long>::value, "");
    static_assert(std::is_same<decltype(idlib::zero<unsigned long long>()), unsigned long long>::value, "");
    static_assert(std::is_same<decltype(idlib::zero<float>()), float>::value, "");
    static_assert(std::is_same<decltype(idlib::zero<double>()), double>::value, "");
}

} // namespace idlib::tests
