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

#pragma push_macro("IDLIB_PRIVATE")
#undef IDLIB_PRIVATE
#define IDLIB_PRIVATE (1)

#include "idlib/hll/decoder.hpp"
#include "idlib/hll/classify.hpp"

#undef IDLIB_PRIVATE
#pragma pop_macro("IDLIB_PRIVATE")

#include "idlib/exception.hpp"

namespace idlib::hll {

/// @brief Specialization of idlib::c::decoder for decoding <c>boolean</c> literals to @a bool values.
/// @tparam V the type of the values to decode the <c>boolean</c> literals to
template <>
struct decoder<bool, void>
{
    bool operator()(const std::string& s, bool& v) const
    {
        if (s == "true")
        {
            v = true;
            return true;
        }
        else if (s == "false")
        {
            v = false;
            return true;
        }
        else
        {
            throw invalid_argument_error(__FILE__, __LINE__, "not a valid boolean literal");
        }
    }
}; // struct decoder

} // namespace idlib::hll
