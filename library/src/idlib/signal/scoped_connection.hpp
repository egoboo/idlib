// Copyright Michael Heilmann 2016, 2017, 2018.
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
    id::connection connection;

public:
    /// @brief Construct this scoped connection from a connection.
    /// @param connection the connection
    scoped_connection(const id::connection& connection)
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
