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

/// @file idlib/signal/node_base.cpp
/// @brief Non-generic base class of all nodes.
/// @author Michael Heilmann

#define IDLIB_PRIVATE 1
#include "idlib/signal/node_base.hpp"
#undef IDLIB_PRIVATE

#include "idlib/signal/internal/header.hpp"

namespace internal {

node_base::node_base(int number_of_references)
    : state(state::disconnected), signal(nullptr), number_of_references(number_of_references), next(nullptr)
{}

node_base::~node_base() {}

bool node_base::has_signal() const
{
    return nullptr != signal;
}

bool node_base::has_references() const
{
    return 0 < get_number_of_references();
}

int node_base::get_number_of_references() const
{
    return number_of_references;
}

void node_base::add_reference()
{
    number_of_references++;
}

void node_base::remove_reference()
{
    if (0 == --number_of_references)
    {
        /* Nothing to do yet. */
    }
}

} // namespace internal

#include "idlib/signal/internal/footer.hpp"
