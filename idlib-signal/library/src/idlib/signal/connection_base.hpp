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

/// @file idlib/signal/connection_base.hpp
/// @brief Non-generic base class of all connections.
/// @author Michael Heilmann

#pragma once

#if !defined(IDLIB_PRIVATE) || IDLIB_PRIVATE != 1
#error(do not include directly, include `idlib/signal.hpp` instead)
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
