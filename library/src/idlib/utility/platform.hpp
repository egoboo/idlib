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

/// @file idlib/utility/platform.hpp
/// @brief Functionality protecting the programmer from platform and compiler idiosyncrasies.
/// @todo Define and use ID_GNUC, define and use ID_CPP.
/// @author Michael Heilmann

#pragma once

#if !defined(IDLIB_PRIVATE) || IDLIB_PRIVATE != 1
#error(do not include directly, include `idlib/idlib.hpp` instead)
#endif

#include "idlib/platform/platform.hpp"

// Common C and C++ headers.
#if defined(__cplusplus)
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

#if defined(__cplusplus)
    #include <cstddef>
#else
    #include <stddef.h>
#endif

#if defined(__cplusplus)
    #include <cctype>
#else
    #include <ctype.h>
#endif

#if defined(__cplusplus)
    #include <cstdarg>
#else
    #include <stdarg.h>
#endif

#if defined(__cplusplus)
    #include <cstdio>
#else
    #include <stdio.h>
#endif

#if defined(__cplusplus)
    #include <cassert>
#else
    #include <assert.h>
#endif

#if defined(__cplusplus)
    #include <cmath>
#else
    #include <math.h>
#endif

#if defined(__cplusplus)
    #include <cfloat>
#else
    #include <float.h>
#endif

#if defined(__cplusplus)
    #include <ctime>
#else
    #include <time.h>
#endif

#if defined(__cplusplus)
    #include <memory>
#else
    #include <memory.h>
#endif

#if defined(__cplusplus)
    #include <cstring>
#else
    #include <string.h>
#endif

#if defined(__cplusplus)
    #if !defined (_MSC_VER) || _MSC_VER < 1912
      #include <cstdbool>
	#endif
#else
    #include <stdbool.h>
#endif

#if defined(__cplusplus)
    #include <cerrno>
#else
    #include <errno.h>
#endif

#if defined(__cplusplus)
    #include <cstdint>
#else
    #include <stdint.h>
#endif

#if defined(__cplusplus)
    #include <cinttypes>
#else
    #include <inttypes.h>
#endif

// C++ exxclusive headers from here on (in alphabetic order).
#include <array>
#include <algorithm>
#include <atomic>
#include <bitset>
#include <exception>
#include <forward_list>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <locale>
#include <list>
#include <map>
#include <memory>
#include <mutex>
#include <condition_variable>
#include <new>
#include <random>
#include <stdexcept>
#include <sstream>
#include <stack>
#include <string>
#include <thread>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
#include <chrono>
#include <set>
#include <future>
#include <queue>

/// @brief printf/scanf-style format specifier for size_t.
/// @remark This is necessary because of Redmon Retards' (aka Microsoft's) Visual C++.
#if defined(_MSC_VER) || defined(ID_MINGW)
    #define PRIuZ "Iu"
#else
    #define PRIuZ "zu"
#endif

/// @brief printf/scanf-style format specifier for ssize_t.
/// @remark This is necessary because of Redmon Retards' (aka Microsoft's) Visual C++.
#if defined(_MSC_VER) || defined(ID_MINGW)
    #define PRIdZ "Id"
#else
    #define PRIdZ "zd"
#endif

/// @brief A macro alias for Linux-flavored functions for MSVC.
/// @remark This is necessary because of Redmon Retards' (aka Microsoft) Visual C++ / Windows.
#if defined(_MSC_VER)
#define stricmp _stricmp
#define strlwr _strlwr
#define strupr _strupr

// This isn't needed anymore since MSVC 2015 and causes errors.
#if (_MSC_VER < 1900)
#define snprintf _snprintf
#endif

// This isn't needed anymore since MSVC 2013 and causes errors.
#if !(_MSC_VER >= 1800)
#define isnan _isnan
#endif

// This isn't needed anymore since MSVC 2008 and causes errors.
#if (_MSC_VER < 1500)
#define vsnprintf _vsnprintf
#endif
#endif
