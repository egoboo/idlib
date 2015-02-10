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
