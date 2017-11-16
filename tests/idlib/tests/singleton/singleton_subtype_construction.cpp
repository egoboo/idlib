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

/// @file idlib/test/singleton/singleton.hpp
/// @brief Replacement for std::clamp until C++17 is fully supported.
/// Directly copied from http://en.cppreference.com/w/cpp/algorithm/clamp.
/// @author Michael Heilmann


#include "gtest/gtest.h"
#include "idlib/idlib.hpp"

namespace id { namespace test { namespace singleton_subtype_construction {
	
class foo;
class bar;
	
struct foo_create_functor {
	foo *operator()(const std::string& string) const;
};

struct foo_destroy_functor {
	void operator()(foo *p) const;
};

class foo : public id::singleton<foo, foo_create_functor, foo_destroy_functor> {
protected:
	friend struct foo_destroy_functor;
    foo(const std::string& string) {
        std::cout << "foo::foo(" << string << ")" << std::endl;
    }
    virtual ~foo() {
        std::cout << "foo::~foo()" << std::endl;
    }
};

struct bar : public foo {
protected:
	friend struct foo_create_functor;
	bar(const std::string& string) : foo(string) {
        std::cout << "bar::bar(" << string << ")" << std::endl;
	}
	virtual ~bar() {
	}
};

foo *foo_create_functor::operator()(const std::string& string) const
{ return new bar(string); }

void foo_destroy_functor::operator()(foo *p) const
{ delete p; }

TEST(singleton, subtype_construction) {
    foo::initialize("Hello, World!");
    foo::uninitialize();
}

} } } // namespace id::test::singleton_subtype_construction
