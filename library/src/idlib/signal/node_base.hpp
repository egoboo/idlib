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

/// @file idlib/signal/node_base.hpp
/// @brief Non-generic base class of all nodes.
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
/// Non-generic base class of any node.
struct node_base
{
    /// The state of the relation of a signal and a slot.
    enum class state
    {
        /// signal and slot are connected.
        connected,
        /// signal and slot are disconnected.
        disconnected,
    };

    /// A pointer to the signal.
    signal_base *signal;
    /// A pointer to the successor of this node if it has a successor, a null pointer otherwise.
    node_base *next;
    /// The state of the relation of the signal and the slot.
    state state;

    node_base(const node_base&) = delete; // Do not allow copying.
    const node_base& operator=(const node_base&) = delete; // Do not allow copying.

    /// @brief Construct this node.
    /// @param numberOfReferences the initial number of references of this node
    /// @post signal = nullptr, next = nullptr, state = State::Disconnected
    node_base(int numberOfReferences);

    /// @brief Virtual destructor.
    virtual ~node_base();

public:
    /// @brief Get if this node has a signal.
    /// @return @a true if this node has a signal, @a false otherwise
    bool has_signal() const;

public:
    /// @brief Ensure that the state of this node is "disconnected".
    /// @post !o.isConnected()
    void disconnect()
    {
        state = state::disconnected;
    }
    /// @brief Get if the state of this node is "connected".
    /// @return @a true if the state of this node is "connected", @a false otherwise
    bool is_connected() const
    {
        return state::connected == state;
    }
    /// @brief Get if the state of this node is "disconnected".
    /// @return @a true if the state of this node is "disconnected", @a false otherwise
    bool is_disconnected() const
    {
        return !is_connected();
    }
public:
    int number_of_references;

public:
    /// @brief Get if this node has references.
    /// @return @a true if this node has references, @a false otherwise
    bool has_references() const;

    /// @brief The number of references to this node.
    int number_of_connections;

    /// @brief Get the number of references of this node.
    /// @return the number of references of this node
    int get_number_of_references() const;

    /// @brief Add a reference to this node.
    void add_reference();

    /// @brief Remove a reference to this node.
    void remove_reference();
}; // struct node_base

} // namespace internal

#include "idlib/signal/internal/footer.hpp"
