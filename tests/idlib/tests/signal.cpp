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

namespace idlib { namespace tests { namespace signal {

// Connection, invocation, and explicit disconnection.
TEST(signal_testing, test_signal_0)
{
    idlib::signal<void(const std::string&)> signal;
    // (1) Invoke with no subscriber.
    signal("Hello, World!");
    // (2) Invoke with one subscriber.
    bool invoked = false;
    auto function = [&invoked](const std::string& s) { invoked = true; };
    auto connection = signal.subscribe(function);
    signal("Hello, World!");
    connection.disconnect();
    ASSERT_EQ(true, invoked);
}

// Implicit disconnection (upon destruction of a signal).
TEST(signal_testing, test_signal_1)
{
    idlib::connection connection;
    {
        idlib::signal<void(const std::string&)> signal;
        bool invoked = false;
        auto function = [&invoked](const std::string& s) { invoked = true; };
        connection = signal.subscribe(function);
        ASSERT_EQ(true, connection.is_connected());
    }
    ASSERT_EQ(false, connection.is_connected());
}

// Scoped disconnection (upon destruction of a scoped connection).
TEST(signal_testing, test_signal_2) {
    bool invoked = false;
    idlib::signal<void(const std::string&)> signal;
    {
        auto function = [&invoked](const std::string& s) { invoked = true; };
        idlib::scoped_connection scoped_connection(signal.subscribe(function));
        ASSERT_EQ(true, scoped_connection.is_connected());
    }
    signal("Hello, World!");
    ASSERT_EQ(false, invoked);
}

TEST(signal_testing, test_signal_3) {
    bool invoked = false;
    idlib::signal<void(const std::string&, const std::string&)> signal;
    {
        auto function = [&invoked](const std::string& s0, const std::string& s1) { invoked = true; };
        idlib::scoped_connection scoped_connection(signal.subscribe(function));
        ASSERT_EQ(true, scoped_connection.is_connected());
    }
    signal("Hello, ", "World!");
    ASSERT_EQ(false, invoked);
}

TEST(signal_testing, test_signal_4)
{
    bool invoked = false;
    idlib::signal<void(float, float)> signal;
    {
        auto function = [&invoked](float s0, float s1) { invoked = true; };
        idlib::scoped_connection scoped_connection(signal.subscribe(function));
        ASSERT_EQ(true, scoped_connection.is_connected());
    }
    signal(1.0f, 2.0f);
    ASSERT_EQ(false, invoked);
}

} } } // namespace idlib::tests::signal
