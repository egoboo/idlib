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

#pragma once

#include "idlib/math/generator.hpp"

namespace id {

/// @brief A generator returning a constant value.
/// @tparam R the result type
template <typename R>
struct constant_generator : generator
{
    using result_type = R;

    constant_generator(const result_type& c = result_type())
        : m_c(c)
	{}

#if defined(_MSC_VER) // Disable sickening flood of warnings.
    #pragma warning(push)
    #pragma warning(disable: 4100)
#endif

    result_type operator()(size_t index) const
	{ return m_c; }

#if defined(_MSC_VER)
	#pragma warning(pop)
#endif

private:
    const result_type m_c;
}; // struct constant_generator

} // namespace id
