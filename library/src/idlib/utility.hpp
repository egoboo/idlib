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

/// @file idlib/utility.hpp
/// @brief Master include file of the Idlib utility library.
/// @author Michael Heilmann

#pragma once

#pragma push_macro("IDLIB_PRIVATE")
#undef IDLIB_PRIVATE
#define IDLIB_PRIVATE (1)

#include "idlib/utility/target.hpp"
#include "idlib/utility/platform.hpp"

#include "idlib/utility/fold_expressions.hpp"

#include "idlib/utility/swap_bytes.hpp"
#include "idlib/utility/byte_order.hpp"

#include "idlib/utility/non_copyable.hpp"

#include "idlib/utility/bitmask_type.hpp"

#include "idlib/utility/exception.hpp"
#include "idlib/utility/environment_error.hpp"
#include "idlib/utility/assertion_failed_error.hpp"
#include "idlib/utility/unhandled_switch_case_error.hpp"
#include "idlib/utility/runtime_error.hpp"
#include "idlib/utility/invalid_argument_error.hpp"
#include "idlib/utility/null_error.hpp"
#include "idlib/utility/out_of_bounds_error.hpp"

#include "idlib/utility/to_upper.hpp"
#include "idlib/utility/to_lower.hpp"

#include "idlib/utility/prefix.hpp"
#include "idlib/utility/suffix.hpp"

#undef IDLIB_PRIVATE
#pragma pop_macro("IDLIB_PRIVATE")
