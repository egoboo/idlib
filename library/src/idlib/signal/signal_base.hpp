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

/// @file idlib/signal/signal_base.hpp
/// @brief Non-generic base class of all signals.
/// @author Michael Heilmann

#pragma once

#if !defined(IDLIB_PRIVATE) || IDLIB_PRIVATE != 1
#error(do not include directly, include `idlib/idlib.hpp` instead)
#endif

#include "idlib/utility/platform.hpp"

#include "idlib/signal/internal/header.hpp"

namespace internal {

// Forward declarations.
struct connection_base;
struct node_base;
struct signal_base;

/// @internal
/// @ingroup signal
/// @brief Non-generic base class of any signal.
struct signal_base
{
    friend struct connection_base;
protected:
    node_base *head; ///< @brief The head of the nodes.
    bool running; ///< @brief @a true if the signal is currently running, @a false otherwise.
    size_t connected_count; ///< @brief The number of connected nodes.
    size_t disconnected_count; ///< @brief The number of disconnected nodes.

    /// @brief Remove all dead subscriptions if the number of dead nodes exceeds the number of live nodes.
    /// @precondition The signal is not currently running.
    void maybe_sweep() noexcept;

    /// @brief Does the subscriber list need sweeping?
    /// @return @a true if the subscriber list needs sweeping, @a false otherwise
    bool need_sweep() const noexcept;

public:
    signal_base(const signal_base&) = delete; // Do not allow copying.
    const signal_base& operator=(const signal_base&) = delete; // Do not allow copying.

public:
    /// @brief Default construct this signal base.
    signal_base() noexcept;

    /// @brief Destruct this signal base.
    /// Disconnects all nodes.
    virtual ~signal_base() noexcept;

    /// @brief Disconnect all nodes.
    void disconnect_all() noexcept;

private:
    /// @brief Sweep the list of nodes.
    /// Delete any node (from the singly-linked list of nodes) that is not referenced by a connection.
    void sweep() noexcept;

};

} // namespace Internal
} // namespace Id
