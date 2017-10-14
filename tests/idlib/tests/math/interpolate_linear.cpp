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

namespace id { namespace math { namespace test {

	using interval_s = id::interval<single>;
	using vector_3s = id::vector<single, 3>;
	using point_3s = id::point<vector_3s>;

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
	ASSERT_EQ(x, id::lineary_interpolate(x, y, 0.0f));
	ASSERT_EQ(y, id::lineary_interpolate(x, y, 1.0f));
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

} } } // namespace id::math::test
