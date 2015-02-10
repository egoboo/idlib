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
