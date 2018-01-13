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

#define IDLIB_PRIVATE 1
#include "idlib/signal/signal_base.hpp"
#include "idlib/signal/connection_base.hpp"
#include "idlib/signal/node_base.hpp"
#undef IDLIB_PRIVATE

#include "idlib/signal/internal/header.hpp"

namespace internal {

signal_base::signal_base() noexcept : head(nullptr), disconnected_count(0), connected_count(0), running(false) {}

void signal_base::sweep() noexcept
{
    node_base **predecessor = &head, *current = head;
    while (nullptr != current)
    {
        // Remove disconnected nodes.
        if (current->is_disconnected())
        {
            // Unlink the node.
            node_base *node = current;
            *predecessor = current->next; // Let predecessor refer to the successor.
            current = current->next; // Continue at successor.
            // Decrement the number of disconnected nodes.
            disconnected_count--;
            // Remove the reference from this signal.
            node->remove_reference();
            // If the number of references to the node is @a 0, then the signal was the sole owner of the node.
            // The signal shall delete the node.
            if (0 == node->get_number_of_references())
            {
                delete node;
            }
        }
        else
        {
            predecessor = &current->next;
            current = current->next;
        }
    }
}

signal_base::~signal_base() noexcept
{
    disconnect_all();
    sweep();
    assert(0 == connected_count);
    assert(0 == disconnected_count);
    assert(nullptr == head);

}

bool signal_base::need_sweep() const noexcept
{
    return disconnected_count > std::min(size_t(8), connected_count);
}

void signal_base::maybe_sweep() noexcept
{
    assert(true == running); // Must be true!
    if (need_sweep())
    {
        sweep();
    }
}

void signal_base::disconnect_all() noexcept
{
    for (auto node = head; nullptr != node; node = node->next)
    {
        if (node->state != node_base::state::disconnected)
        {
            node->state = node_base::state::disconnected;
            disconnected_count++;
            connected_count--;
        }
    }
}

} // namespace internal

#include "idlib/signal/internal/footer.hpp"
