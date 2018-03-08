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

/// @file idlib/platform/platform.hpp
/// @brief Compile-time platform detection.
/// @author Michael Heilmann

/// @detail
/// This file makes attempts to detect the target platform based on common predefined preprocessor symbols.
/// In particular, this file will either not compile or define one of the following symbolic constants indicating the target platform:
/// - #ID_LINUX (Linux),
/// - #ID_OSX (OSX),
/// - #ID_WINDOWS (Windows),
/// - #ID_IOSSIMULATOR (iOS simulator),
/// - #ID_IOS (iOS).
/// By pre-defining any of those constants to @a 1, you can skip the detection mechanism in this files.
/// Defining any of those constants to a value not equal to @a 1 or defining multiple constants, will result in a compile-time error.
/// </br>
/// In addition to the above constants, the following constants may be defined.
/// - #ID_POSIX (POSIX) and
/// - #ID_UNIX (UNIX).
/// POSIX and UNIX are not operating systems. Rather they are formal or de facto standards followed to some degree by all certain operating systems.
/// They indicate that a certain functionality is provided to some degree by the OS in question.
/// </br>
/// If ID_WINDOWS is defined, then there is the possibility that the target platform is MinGW.
/// MinGW is a blending of native Windows and Linux functionality. If the target platform is MinGW then the constant ID_MINGW is defined.
/// MinGW target platforms always distinguish between the 32- and 64-Bit versions.
/// The 32-Bit variant is indicated by the definition of the constant ID_MING32,
/// the 64-Bit variant is indicated by the definition of the constant ID_MING64.
/// One of these two constants - but not both - is defined iff ID_MINGW is defined.
/// @remark
/// The author wants to thank Nadeau software as these comments and the code is based on the an the article
/// http://nadeausoftware.com/articles/2012/01/c_c_tip_how_use_compiler_predefined_macros_detect_operating_system
/// written in 2012 published by this company. On the converse, no guarantees are made that this information is still up-2-date.

#pragma once

#if !defined(IDLIB_PRIVATE) || IDLIB_PRIVATE != 1
#error(do not include directly, include `idlib/idlib.hpp` instead)
#endif


// "defining any of those constants to a value not equal to @a 1, will result in a compile-time error"
#if defined(ID_LINUX)
    #if ID_LINUX != 1
        #error ID_LINUX must be defined to 1 or must not be defined
    #endif
#endif

#if defined(ID_OSX)
    #if ID_OSX != 1
        #error ID_OSX must be defined to 1 or must not be defined
    #endif
#endif

#if defined (ID_WINDOWS)
    #if ID_WINDOWS != 1
        #error ID_WINDOWS must be defined to 1 or must not be defined
    #endif
#endif

#if defined(ID_IOSSIMULATOR)
    #if ID_IOSSIMULATOR != 1
        #error ID_IOSSIMULATOR must be defined to 1 or must not be defined
    #endif
#endif

#if defined(ID_IOS)
    #if ID_IOS != 1
        #error ID_IOS must be defined to 1 or must not be defined
    #endif
#endif

#if defined (ID_MINGW32)
    #if ID_MINGW32 != 1
        #error ID_MINGW32 must be defined to 1 or must not be defined
    #endif 
#endif

#if defined (ID_MINGW64)
    #if ID_MINGW64 != 1
        #error ID_MINGW64 must be defined to 1 or must not be defined
    #endif 
#endif

#if defined (ID_MINGW)
    #if ID_MINGW != 1
        #error ID_MINGW must be defined to 1 or must not be defined
    #endif 
#endif

#if defined (ID_POSIX)
    #if ID_POSIX != 1
        #error ID_POSIX must be defined to 1 or must not be defined
    #endif 
#endif


// "defining multiple constants, will result in a compile-time error"
#if defined(ID_LINUX)
    #if defined (DEFINED)
        #error more than one platform target specified
    #else
        #undef DEFINED
        #define DEFINED 1
    #endif
#endif

#if defined(ID_OSX)
    #if defined (DEFINED)
        #error more than one platform target specified
    #else
        #undef DEFINED
        #define DEFINED 1
    #endif
#endif

#if defined (ID_WINDOWS)
    #if defined (DEFINED)
        #error more than one platform target specified
    #else
        #undef DEFINED
        #define DEFINED 1
    #endif
#endif

#if defined(ID_IOSSIMULATOR)
    #if defined (DEFINED)
        #error more than one platform target specified
    #else
        #undef DEFINED
        #define DEFINED 1
    #endif
#endif

#if defined(ID_IOS)
    #if defined (DEFINED)
        #error more than one platform target specified
    #else
        #undef DEFINED
        #define DEFINED 1
    #endif
#endif

// "If ID_MINGW is defined, then ID_WINDOWS must be defined."
#if defined (ID_MINGW)
    #if !defined(ID_WINDOWS)
        #error ID_MINGW can not be defined without ID_WINDOWS being defined
    #endif
#endif

// If the target platform is MingGW32 or MinGW64, then either the constant ID_MINGW32 or the constant ID_MINGW64 is defined (but not both).
#if defined (ID_MING64) && defined (ID_MINGW32)
    #error either ID_MINGW64 or ID_MINGW32 may be defined, not both
#endif

#if defined (ID_MINGW)
    #if !defined(ID_MINGW32) && !defined(ID_MINGW64)
        #error if ID_MINGW is defined, then either ID_MINGW64 or ID_MINGW32 must be defined
    #endif
#endif


/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
// "by pre-defining any of those constants to @a 1, you can skip the detection mechanism in this file"

#include "idlib/platform/windows.in"
#include "idlib/platform/mingw.in"
#include "idlib/platform/apple.in"
#include "idlib/platform/linux.in"

// Check for Unix-/Posix-compliance.
#include "idlib/platform/check_unix_posix.in"

#if !defined(ID_WINDOWS) && !defined(ID_LINUX) && !defined(ID_OSX) && !defined(ID_IOS) && !defined(ID_IOSSIMULATOR)
    #error target platform not detected
#endif


/// @brief An alias for @a (float).
using single = float;
/// @brief An alias for @a (long double).
using quadruple = long double;

/// @brief Format attributes for printf-style functions for GCC/Clang.
/// @see https://gcc.gnu.org/onlinedocs/gcc/Common-Function-Attributes.html#Common-Function-Attributes
#if defined(__GNUC__)
    #define GCC_PRINTF_FUNC(fmtargnum) __attribute__ (( format( __printf__, fmtargnum, fmtargnum+1 ) ))
#else
    #define GCC_PRINTF_FUNC(fmtargnum)
#endif

/// @brief Format attributes for scanf-style functions for GCC/Clang.
/// @see https://gcc.gnu.org/onlinedocs/gcc/Common-Function-Attributes.html#Common-Function-Attributes
#if defined(__GNUC__)
    #define GCC_SCANF_FUNC(fmtargnum) __attribute__ (( format( __scanf__, fmtargnum, fmtargnum+1 ) ))
#else
    #define GCC_SCANF_FUNC(fmtargnum)
#endif
