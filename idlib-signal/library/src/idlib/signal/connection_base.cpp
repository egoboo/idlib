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

/// @file idlib/signal/connection_base.cpp
/// @brief Non-generic base class of all connections.
/// @author Michael Heilmann

#define IDLIB_PRIVATE 1
#include "idlib/signal/connection_base.hpp"
#include "idlib/signal/signal_base.hpp"
#include "idlib/signal/node_base.hpp"
#undef IDLIB_PRIVATE

#include "idlib/signal/internal/header.hpp"

namespace internal {

connection_base::connection_base()
    : node(nullptr)
{}

connection_base::connection_base(node_base *node)
    : node(node)
{
    if (node)
    {
        node->add_reference();
    }
}

connection_base::connection_base(const connection_base& other)
    : node(other.node)
{
    if (node)
    {
        node->add_reference();
    }
}

connection_base::~connection_base()
{
    reset();
}

const connection_base& connection_base::operator=(const connection_base& other)
{
    if (&other != this)
    {
        reset();
        node = other.node;
        if (node)
        {
            node->add_reference();
        }
    }
    return *this;
}

bool connection_base::operator==(const connection_base& other) const
{
    return node == other.node;
}

bool connection_base::operator!=(const connection_base& other) const
{
    return node != other.node;
}

bool connection_base::is_connected() const
{
    if (node)
    {
        return node_base::state::disconnected != node->state;
    }
    return false;
}

void connection_base::reset()
{
    if (nullptr == node)
    {
        return;
    }
    // Remove our reference to the node.
    node->remove_reference();
    // If the number of references to the node is @a 0,
    // then we were the sole owner of this node.
    // We delete the node.
    if (0 == node->get_number_of_references())
    {
        delete node;
        // If the number of references to the node is @a 1,
        // and the node has a signal, then the signal is the sole owner of this node.
        // If the node is disconnected, then the signal may want to delete the node.
    }
    else if (1 == node->get_number_of_references() && nullptr != node->signal && node->state == node_base::state::disconnected)
    {
        // If this signal is not running ...
        if (!node->signal->running)
        {
            // ... mark it as running and sweep it.
            node->signal->running = true;
            node->signal->maybe_sweep();
            node->signal->running = false;
        }
        // Otherwise some other connection owns the node now.
    }
    else
    {
        /* Nothing to do. */
    }
    node = nullptr;
}

void connection_base::disconnect()
{
    if (node)
    {
        if (node->state != node_base::state::disconnected)
        {
            node->state = node_base::state::disconnected;
            signal_base *signal = node->signal;
            if (signal)
            {
                // >> notify signal node disconnected
                signal->connected_count--;
                signal->disconnected_count++;
                // << notify signal node disconnected
                // If this signal is not running ...
                if (!signal->running)
                {
                    // ... mark it as running and sweep it.
                    signal->running = true;
                    signal->maybe_sweep();
                    signal->running = false;
                }
            }
        }
        node = nullptr;
    }
}

} // namespace internal

#include "idlib/signal/internal/footer.hpp"
