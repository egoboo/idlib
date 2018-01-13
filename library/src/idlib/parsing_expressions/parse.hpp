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

/// @file idlib/parsing_expressions/parse.hpp
/// @brief "parse" function
/// @author Michael Heilmann

#include "idlib/parsing_expressions/match.hpp"

#include "idlib/parsing_expressions/header.in"

/// @brief Perform parsing.
/// @tparam Expression the type of the parsing grammar expression
/// @tparam Iterator the type of the input iterator
/// @param expression the parsing grammar expression of the parse
/// @param begin, end iterators to the beginning and the ending of the input of the parse
/// @return the match of the parse
template <typename Expression, typename Iterator>
decltype(auto) parse(const Expression& expression, const Iterator& begin, const Iterator& end)
{
	return expression(begin, end);
}

#include "idlib/parsing_expressions/footer.in"
