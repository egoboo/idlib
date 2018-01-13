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
