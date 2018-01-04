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

/// @file idlib/signal/Connection.hpp
/// @brief A connection.
/// @author Michael Heilmann

#pragma once

#if !defined(IDLIB_PRIVATE) || IDLIB_PRIVATE != 1
#error(do not include directly, include `idlib/idlib.hpp` instead)
#endif

#include "idlib/signal/connection_base.hpp"
#include "idlib/signal/node_base.hpp"
#include "idlib/signal/signal_base.hpp"

#include "idlib/signal/internal/header.hpp"

/// @ingroup signal
/// @brief A connection.
struct connection : internal::connection_base
{
    connection()
        : internal::connection_base(nullptr) {}
    connection(id::internal::node_base *node)
        : internal::connection_base(node) {}
    connection(const connection& other)
        : internal::connection_base(other) {}
    const connection& operator=(const connection& other)
    {
        connection_base::operator=(other);
        return *this;
    }
    bool operator==(const connection& other) const
    {
        return connection_base::operator==(other);
    }
    bool operator!=(const connection& other) const
    {
        return connection_base::operator!=(other);
    }
}; // struct connection

#include "idlib/signal/internal/footer.hpp"
