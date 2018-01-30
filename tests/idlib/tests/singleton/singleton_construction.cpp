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

/// @file idlib/test/singleton/singleton.hpp
/// @brief Replacement for std::clamp until C++17 is fully supported.
/// Directly copied from http://en.cppreference.com/w/cpp/algorithm/clamp.
/// @author Michael Heilmann


#include "gtest/gtest.h"
#include "idlib/idlib.hpp"

namespace idlib { namespace test { namespace singleton_construction {

class foo;

struct foo_create_functor {
	foo *operator()(const std::string& p) const;
};

struct foo_destroy_functor {
	void operator()(foo *p) const;
};

class foo : public idlib::singleton<foo, foo_create_functor,
	                                foo_destroy_functor> {
protected:
	friend struct foo_create_functor;
	friend struct foo_destroy_functor;
    foo(const std::string& p) {
        std::cout << "foo::foo(" << p << ")" << std::endl;
    }
    ~foo() {
        std::cout << "foo::~foo()" << std::endl;
    }
};

foo *foo_create_functor::operator()(const std::string& string) const
{ return new foo(string); }

void foo_destroy_functor::operator()(foo *p) const
{ delete p; }

TEST(singleton, construction) {
    foo::initialize("Hello, World!");
    foo::uninitialize();
}

} } } // namespace idlib::test::singleton_construction
