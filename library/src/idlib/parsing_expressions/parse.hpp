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
