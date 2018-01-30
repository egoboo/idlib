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

/// @file idlib/signal/scoped_connection.hpp
/// @brief Scoped connection.
/// @author Michael Heilmann

#pragma once

#if !defined(IDLIB_PRIVATE) || IDLIB_PRIVATE != 1
#error(do not include directly, include `idlib/idlib.hpp` instead)
#endif

#include "idlib/signal/connection.hpp"

#include "idlib/signal/internal/header.hpp"

/// @ingroup signal
/// @brief A scoped connection disconnects a signal and a slot of it is destroyed.
/// Scoped connections are neither copy-constructible nor assignable.
struct scoped_connection {
private:
    idlib::connection connection;

public:
    /// @brief Construct this scoped connection from a connection.
    /// @param connection the connection
    scoped_connection(const idlib::connection& connection)
        : connection(connection) {
    }

private:
    /// Deleted copy-constructor.
    scoped_connection(const scoped_connection& other) = delete;

    /// Deleted assignment operator.
    const scoped_connection& operator=(const scoped_connection& other) = delete;

public:
    /// Destruct this scoped connection.
    virtual ~scoped_connection() {
        connection.disconnect();
    }

    /// @brief Get if the connection is connected.
    /// @return @a true if the connection is connected, @a false otherwise
    bool is_connected() const {
        return connection.is_connected();
    }

    /// @brief Disconnect the connection.
    void disconnect() {
        connection.disconnect();
    }

}; // struct scoped_connection

#include "idlib/signal/internal/footer.hpp"
