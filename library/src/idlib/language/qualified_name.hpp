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

/// @file idlib/language/qualified_name.hpp
/// @brief A qualified names i.e. a name of the form @code{<name>('.'<name>)*}.
/// @author Michael Heilmann

#pragma once

#if !defined(IDLIB_PRIVATE) || IDLIB_PRIVATE != 1
#error(do not include directly, include `idlib/idlib.hpp` instead)
#endif

#include "idlib/crtp.hpp"
#include "idlib/language/location.hpp"
#include <type_traits>

namespace id {

/// @brief A qualified name is an element of the set of strings
/// @code
/// qualified_name := name ('.' name)*
/// name := '_'* (alphabetic) (alphabetic|digit|'_')*
/// @endcode
/// @remark std::hash, std::equal_to and std::less have specializations for qualified names.
class qualified_name final : public id::equal_to_expr<qualified_name>
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

static_assert(std::is_copy_constructible<qualified_name>::value, "id::qualified_name must be copy constructible");
static_assert(std::is_move_constructible<qualified_name>::value, "id::qualified_name must be move constructible");
static_assert(std::is_copy_assignable<qualified_name>::value, "id::qualified_name must be copy assignable");
static_assert(std::is_move_assignable<qualified_name>::value, "id::qualified_name must be move assignable");

} // id

namespace std {

template <>
struct hash<id::qualified_name>
{
    size_t operator()(const id::qualified_name& x) const;
};

template <>
struct equal_to<id::qualified_name>
{
    bool operator()(const id::qualified_name& x, const id::qualified_name& y) const;
};

template <>
struct less<id::qualified_name>
{
    bool operator()(const id::qualified_name& x, const id::qualified_name& y) const;
};

} // namespace std
