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

/// @file idlib/signal/Signal.hpp
/// @detail Signal-slot implementation.
/// @author Michael Heilmann

#pragma once

#if !defined(IDLIB_PRIVATE) || IDLIB_PRIVATE != 1
#error(do not include directly, include `idlib/idlib.hpp` instead)
#endif

#include "idlib/signal/connection.hpp"
#include "idlib/signal/node.hpp"
#include "idlib/signal/signal_base.hpp"

/// @defgroup signal
/// @brief C++ 11 signal-slot library.
/// Features:
/// - signals support arbitrary argument lists
/// - signals need to provided single-thread re-entrancy i.e. it is possible to connect and disconnect
///   signal handlers and re-emit a signal from a running signal handler.
/// - signals support void return values
/// - a signal member in a user-defined type has moderate impact
/// -- on the cost of a call to a constructor/destructor of that type and
///   -- on the size of an object of that type.

#include "idlib/signal/internal/header.hpp"

// Forward declarations.
struct connection;
template <class> struct signal;

/// @ingroup signal
/// @brief Generic signal.
/// @tparam ReturnType the return type
/// @tparam ... ParameterTypes the parameter types
/// @remark Non-copyable.
template <class ReturnType, class ... ParameterTypes>
struct signal<ReturnType(ParameterTypes ...)> : internal::signal_base
{
public:
    /// @brief The node type.
    using node_type = internal::node<ReturnType(ParameterTypes ...)>;
    /// @brief The function type.
    using function_type = std::function<ReturnType(ParameterTypes ...)>;

public:
    signal(const signal&) = delete; // Do not allow copying.
    const signal& operator=(const signal&) = delete; // Do not allow copying.

public:
    /// @brief Construct this signal.
    signal() noexcept : signal_base() {}

    /// @brief Destruct this signal
    /// Disconnects all subscribers.
    ~signal() noexcept {}

public:
    /// @brief Subscribe to this signal.
    /// @param function a non-empty function
    /// @return the connection
    connection subscribe(const function_type& function)
    {
        // Create the node.
        internal::node_base *node = new node_type(1, function);
        // Configure and add the node.
        node->state = internal::node_base::state::connected;
        node->next = head; head = node;
        node->signal = this;
        // Increment the connected count.
        connected_count++;
        // Return the connection.
        return connection(node);
    }


public:
    /// @brief Notify all subscribers.
    /// @param arguments the arguments
    /// @remark
    /// Iterate over the nodes. If a node is connected, then it is invoked.
    void operator()(ParameterTypes ... arguments)
    {
        if (!running)
        { 
            /// @todo Use ReentrantBarrier (not committed yet).
            running = true;
            try
            {
                for (internal::node_base *cur = head; nullptr != cur; cur = cur->next)
                {
                    if (cur->state == internal::node_base::state::connected)
                    {
                        (*static_cast<node_type *>(cur))(std::forward<ParameterTypes>(arguments) ...);
                    }
                }
            }
            catch (...)
            {
                running = false;
                std::rethrow_exception(std::current_exception());
            }
            maybe_sweep();
            running = false;
        }
    }

}; // struct signal

#include "idlib/signal/internal/footer.hpp"
