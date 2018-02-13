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

#pragma once

#include <type_traits>

namespace idlib {

/// @internal
/// @brief The following templates obtain the relation of one the boolean values in a variadic template argument list @a size_t compile-time constants.
template <bool...> struct bool_pack;

/// @internal
/// @brief Provide a member constant value <tt>value</tt>.
/// That constant is equal to <tt>true</tt> if
/// all boolean values in the variadic template argument list are true.
/// Otherwise it is equal to <tt>false</tt>.
/// @tparam ... v a possibly empty list of @a bool values
/// @remark @a true is prepended to the first list of values and appended to the second list of values to ensure the lists are not empty.
template <bool ... v>
using all_true = std::is_same<bool_pack<true, v ...>, bool_pack<v ..., true>>;

/// @brief Provide a member constant value <tt>value</tt>.
/// That constant is equal to <tt>true</tt> if
/// all boolean values in the variadic template argument list are true.
/// Otherwise it is equal to <tt>false</tt>.
/// @tparam ... v a possibly empty list of @a bool values
/// @remark @a false is prepended to the first list of values and appended to the second list of values to ensure the lists are not empty.
template <bool ... v>
using all_false = std::is_same<bool_pack<false, v ...>, bool_pack<v ..., false>>;

} // namespace idlib
