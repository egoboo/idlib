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
