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

namespace idlib { namespace math { namespace test {

using interval_s = idlib::interval<single>;
using vector_3s = idlib::vector<single, 3>;
using point_3s = idlib::point<vector_3s>;

// Generate the tuples (1,0,0), (0,1,0), (0,0,1).
template <typename T>
std::vector<T> basis(std::vector<T> l) {
	std::vector<T> l1{ l };
	l1.emplace_back(1.0f, 0.0f, 0.0f);
	l1.emplace_back(0.0f, 1.0f, 0.0f);
	l1.emplace_back(0.0f, 0.0f, 1.0f);
	return l1;
}

// Add the tuple (0,0,0).
template <typename T>
std::vector<T> zero(std::vector<T> l) {
	std::vector<T> l1{ l };
	l1.emplace_back(0.0f, 0.0f, 0.0f);
	return l1;
}

// Add negation of all list elements to a list.
template <typename T>
std::vector<T> negation(std::vector<T> l) {
	std::vector<T> l1{ l };
	for (auto e : l) {
		auto e1 = -e;
		l1.emplace_back(-e1);
	}
	return l1;
}

// Cartesian product list of two list.
template <typename T>
static std::vector<std::pair<T, T>> cartesian(const std::vector<T>& a, const std::vector<T>& b) {
	std::vector<std::pair<T, T>> c;
	for (auto x : a) {
		for (auto y : b) {
			c.emplace_back(x, y);
		}
	}
	return c;
}

template <typename T>
void do_test(const T& x, const T& y) {
	ASSERT_EQ(x, idlib::lineary_interpolate(x, y, 0.0f));
	ASSERT_EQ(y, idlib::lineary_interpolate(x, y, 1.0f));
}

TEST(linear_interpolation, vector_3s) {
	auto l = zero(negation(basis(std::vector<vector_3s>())));
	auto cl = cartesian(l, l);
	for (auto c : cl) {
		do_test(c.first, c.second);
	}
}

TEST(linear_interpolation, point_3s) {
	/// @todo Should we allow negation of points?
	auto l = zero(basis(std::vector<point_3s>()));
	auto cl = cartesian(l, l);
	for (auto c : cl) {
		do_test(c.first, c.second);
	}
}

} } } // namespace idlib::math::test
