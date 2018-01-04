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

/// @file idlib/parsing_expressions/action.hpp
/// @brief Basic definitions for actions.
/// @author Michael Heilmann

#pragma once

#include "idlib/parsing_expressions/header.in"

template <typename Expression>
struct action
{
private:
	Expression m_expression;
public:
	template <typename Iterator>
	match<std::decay_t<Iterator>> operator()(Iterator at, Iterator end) const
	{
		auto result = m_expression(at, end);
		return result;
	}
}; // struct action

#include "idlib/parsing_expressions/footer.in"
