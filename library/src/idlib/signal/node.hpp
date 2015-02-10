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

/// @file idlib/signal/node.hpp
/// @brief Nodes.
/// @author Michael Heilmann

#pragma once

#if !defined(IDLIB_PRIVATE) || IDLIB_PRIVATE != 1
#error(do not include directly, include `idlib/idlib.hpp` instead)
#endif

#include "idlib/signal/node_base.hpp"

#include "idlib/signal/internal/header.hpp"

namespace internal {

// Forward declaration.
template <class ReturnType, class ... ParameterTypes>
struct node;

/// @ingroup signal
/// @brief A generic node.
template <class ReturnType, class ... ParameterTypes>
struct node<ReturnType(ParameterTypes ...)> : internal::node_base
{
public:
    /// The node type.
    using node_type = node<ReturnType(ParameterTypes ...)>;
    /// The function type.
    using function_type = std::function<ReturnType(ParameterTypes ...)>;

public:
    /// The function.
    function_type function;

public:
    node(const node_type&) = delete; // Do not allow copying.
    const node_type& operator=(const node_type&) = delete; // Do not allow copying.

public:
    /// @brief Construct this node.
    /// @param number_of_references the initial number of references
    /// @param function the function
    explicit node(int number_of_references, const function_type& function)
        : internal::node_base(number_of_references), function(function) {}

public:
    /// @brief Invoke this node
    /// @param arguments (implied)
    /// @return (implied)
    ReturnType operator()(ParameterTypes&& ... arguments)
    {
        return function(std::forward<ParameterTypes>(arguments) ...);
    }

}; // struct node

} // namespace internal

#include "idlib/signal/internal/footer.hpp"
