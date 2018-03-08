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

/// @file idlib/signal/signal.hpp
/// @detail Signal-slot implementation.
/// @author Michael Heilmann

#pragma once

#if !defined(IDLIB_PRIVATE) || IDLIB_PRIVATE != 1
#error(do not include directly, include `idlib/signal.hpp` instead)
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
