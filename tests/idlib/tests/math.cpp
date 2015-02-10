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
#include "idlib/idlib.hpp"

namespace id { namespace tests {

/// @brief Assert id::conditional_generator::operator(size_t) has proper return type.
TEST(generators, conditional_generator)
{
	using namespace id;
	using namespace std;
	auto g = make_conditional_generator(1, constant_generator<float>(one<float>()),
		                                   constant_generator<float>(zero<float>()));
	auto v = g(0);
	static_assert(std::is_floating_point<decltype(v)>::value, "not a floating point value");
}

TEST(dimensionality_testing, test_dimensionality)
{
    ASSERT_FALSE(id::is_dimensionality<0>::value);
    ASSERT_FALSE(id::is_dimensionality_v<0>);
    ASSERT_TRUE(id::is_dimensionality<1>::value);
    ASSERT_TRUE(id::is_dimensionality_v<1>);
    ASSERT_TRUE(id::is_dimensionality<std::numeric_limits<size_t>::max()>::value);
    ASSERT_TRUE(id::is_dimensionality_v<std::numeric_limits<size_t>::max()>);
}

TEST(one_testing, test_one_types)
{
    static_assert(std::is_same<decltype(id::one<signed short>()), signed short>::value, "");
    static_assert(std::is_same<decltype(id::one<unsigned short>()), unsigned short>::value, "");
    static_assert(std::is_same<decltype(id::one<signed int>()), signed int>::value, "");
    static_assert(std::is_same<decltype(id::one<unsigned int>()), unsigned int>::value, "");
    static_assert(std::is_same<decltype(id::one<signed long>()), signed long>::value, "");
    static_assert(std::is_same<decltype(id::one<unsigned long>()), unsigned long>::value, "");
    static_assert(std::is_same<decltype(id::one<signed long long>()), signed long long>::value, "");
    static_assert(std::is_same<decltype(id::one<unsigned long long>()), unsigned long long>::value, "");
    static_assert(std::is_same<decltype(id::one<float>()), float>::value, "");
    static_assert(std::is_same<decltype(id::one<double>()), double>::value, "");
}

TEST(zero_testing, test_zero_types)
{
    static_assert(std::is_same<decltype(id::zero<signed short>()), signed short>::value, "");
    static_assert(std::is_same<decltype(id::zero<unsigned short>()), unsigned short>::value, "");
    static_assert(std::is_same<decltype(id::zero<signed int>()), signed int>::value, "");
    static_assert(std::is_same<decltype(id::zero<unsigned int>()), unsigned int>::value, "");
    static_assert(std::is_same<decltype(id::zero<signed long>()), signed long>::value, "");
    static_assert(std::is_same<decltype(id::zero<unsigned long>()), unsigned long>::value, "");
    static_assert(std::is_same<decltype(id::zero<signed long long>()), signed long long>::value, "");
    static_assert(std::is_same<decltype(id::zero<unsigned long long>()), unsigned long long>::value, "");
    static_assert(std::is_same<decltype(id::zero<float>()), float>::value, "");
    static_assert(std::is_same<decltype(id::zero<double>()), double>::value, "");
}

} } // namespace id::tests
