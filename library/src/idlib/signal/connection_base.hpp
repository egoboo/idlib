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

/// @file idlib/signal/connection_base.hpp
/// @brief Non-generic base class of all connections.
/// @author Michael Heilmann

#pragma once

#if !defined(IDLIB_PRIVATE) || IDLIB_PRIVATE != 1
#error(do not include directly, include `idlib/idlib.hpp` instead)
#endif

#include "idlib/utility/platform.hpp"

#include "idlib/signal/internal/header.hpp"

namespace internal {

// Forward declarations.
struct node_base;
struct signal_base;

/// @internal
/// @ingroup signal
/// @brief Non-generic base class of all connections.
struct connection_base
{
    /// @brief A pointer to the node.
    node_base *node;

    /// @brief Default construct this connection.
    /// @post This connection is not connected.
    connection_base();

    /// @brief Construct this connection with the specified arguments.
    /// @param node a pointer to a node of the signal
    connection_base(node_base *node);

    /// Copy construct this connection with the values of another connection.
    /// @param other the other connection
    connection_base(const connection_base& other);

    /// @brief Destruct this connection.
    virtual ~connection_base();

    const connection_base& operator=(const connection_base& other);

    bool operator==(const connection_base& other) const;

    bool operator!=(const connection_base& other) const;


    /// @brief Get if the connection is connected.
    /// @return @a true if this connection is connected, @a false otherwise
    bool is_connected() const;

    /// @brief Disconnect this connection.
    void disconnect();

private:
    void reset();

}; // struct connection_base

} // namespace internal

#include "idlib/signal/internal/footer.hpp"
