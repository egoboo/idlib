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

namespace id { namespace test { namespace singleton_subtype_default_construction {
	
class foo;
class bar;
	
struct foo_create_functor {
	foo *operator()() const;
};

struct foo_destroy_functor {
	void operator()(foo *p) const;
};

class foo : public id::singleton<foo, foo_create_functor, foo_destroy_functor> {
protected:
	friend struct foo_destroy_functor;
    foo() {
        std::cout << "foo::foo()" << std::endl;
    }
    virtual ~foo() {
        std::cout << "foo::~foo()" << std::endl;
    }
};

class bar : public foo {
protected:
	friend struct foo_create_functor;
	bar() {
	}
	virtual ~bar() {
	}
};

foo *foo_create_functor::operator()() const
{ return new bar(); }

void foo_destroy_functor::operator()(foo *p) const
{ delete p; }

TEST(singleton, subtype_default_construction) {
    foo::initialize();
    foo::uninitialize();
}

} } } // namespace id::test::singleton_subtype_default_construction
