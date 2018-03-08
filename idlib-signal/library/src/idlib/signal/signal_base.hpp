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

/// @file idlib/signal/signal_base.hpp
/// @brief Non-generic base class of all signals.
/// @author Michael Heilmann

#pragma once

#if !defined(IDLIB_PRIVATE) || IDLIB_PRIVATE != 1
#error(do not include directly, include `idlib/signal.hpp` instead)
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
