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

/// @file idlib/language/qualified_name.hpp
/// @brief A qualified names i.e. a name of the form @code{<name>('.'<name>)*}.
/// @author Michael Heilmann

#pragma once

#if !defined(IDLIB_PRIVATE) || IDLIB_PRIVATE != 1
#error(do not include directly, include `idlib/idlib.hpp` instead)
#endif

#include "idlib/crtp.hpp"
#include "idlib/language/location.hpp"
#include <functional>
#include <type_traits>

namespace idlib { namespace c {

/// @brief A qualified name is an element of the set of strings
/// @code
/// qualified_name := name ('.' name)*
/// name := '_'* (alphabetic) (alphabetic|digit|'_')*
/// @endcode
/// @remark std::hash, std::equal_to and std::less have specializations for qualified names.
class qualified_name final : public idlib::equal_to_expr<qualified_name>
{
private:
    /// @brief The string.
    std::string m_string;

public:
    /// @brief Construct a qualified name from a string.
    /// @param string the string
    /// @post This qualified name was assigned the string.
    /// @throw Id::LexicalErrorException the argument string @a string does not represent a qualified name
    qualified_name(const std::string& string);

    /// @brief Construct this qualified name from another qualified name.
    /// @param other the other qualified name
    /// @post This qualified name was assigned the string of the other qualified name.
    qualified_name(const qualified_name& other);

    /// @brief Destruct this qualified name.
    ~qualified_name();

    /// @brief Assign this qualified name another qualified name.
    /// @param other the other qualified name
    /// @return this qualified name
    /// @post This qualified name was assigned the string of the other qualified name.
    qualified_name& operator=(const qualified_name& other);

    /// @brief Get the string of this qualified name.
    /// @return the string
    const std::string& string() const;

    // CRTP
    bool equal_to(const qualified_name& other) const;
};

static_assert(std::is_copy_constructible<qualified_name>::value, "idlib::qualified_name must be copy constructible");
static_assert(std::is_move_constructible<qualified_name>::value, "idlib::qualified_name must be move constructible");
static_assert(std::is_copy_assignable<qualified_name>::value, "idlib::qualified_name must be copy assignable");
static_assert(std::is_move_assignable<qualified_name>::value, "idlib::qualified_name must be move assignable");

} } // idlib::c

namespace std {

template <>
struct hash<idlib::c::qualified_name>
{
    size_t operator()(const idlib::c::qualified_name& x) const;
};

template <>
struct equal_to<idlib::c::qualified_name>
{
    bool operator()(const idlib::c::qualified_name& x, const idlib::c::qualified_name& y) const;
};

template <>
struct less<idlib::c::qualified_name>
{
    bool operator()(const idlib::c::qualified_name& x, const idlib::c::qualified_name& y) const;
};

} // namespace std
