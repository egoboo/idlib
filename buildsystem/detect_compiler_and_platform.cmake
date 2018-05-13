# Detect compiler and platform detection.
#
# Provides the following numeric constants:
# - IDLIB_CXX_COMPILER_ID_UNKNOWN
# - IDLIB_CXX_COMPILER_ID_CLANG
# - IDLIB_CXX_COMPILER_ID_GCC
# - IDLIB_CXX_COMPILER_ID_CLANG_MSVC
#
# If compiler detection succeeds, define IDLIB_CXX_COMPILER_ID to IDLIB_CXX_COMPILER_ID_CLANG, IDLIB_CXX_COMPILER_ID_GCC, or IDLIB_CXX_COMPILER_ID_CLANG_MSVC.
# define IDLIX_CXX_COMPILER_ID to IDLIB_CXX_COMPILER_ID_UNKNOWN otherwise.
# Defines macro idlib_report_cxx_compiler_id to report the value of IDLIB_CXX_COMPILER_ID.
#
#
# Provides the following numeric constants:
# - IDLIB_PLATFORM_ID_UNKNOWN
# - IDLIB_PLATFORM_ID_X64
# - IDLIB_PLATFORM_ID_X86
#
# If platform detection succeeds, define IDLIB_PLATFORM_ID to IDLIB_PLATFORM_ID_X64 or IDLIB_PLATFORM_ID_X86.
# Define IDLIB_PLATFORM_ID to IDLIB_PLATFORM_ID_UNKNOWN otherwise.
# Define macro idlib_report_platform_id to report the value of IDLIB_PLATFORM_ID.
#
# If multi target detection succeeds, define IDLIB_IS_MULTI_TARGET_GENERATOR to YES.
# Define IDLIB_IS_MULTI_TARGET_GENERATOR to NO otherwise.
# Define macro idlib_report_is_multi_target_generator to report the value of IDLIB_IS_MULTI_TARGET_GENERATOR.

# Compiler name detection (C++).

set(IDLIB_CXX_COMPILER_ID_UNKNOWN 0)
set(IDLIB_CXX_COMPILER_ID_CLANG 1)
set(IDLIB_CXX_COMPILER_ID_MSVC 2)
set(IDLIB_CXX_COMPILER_ID_GCC 3)

if (CMAKE_CXX_COMPILER MATCHES ".*clang")
  #message("compiler `CLANG` detected")
  set(IDLIB_CXX_COMPILER_ID ${IDLIB_CXX_COMPILER_ID_CLANG})
endif()

if (${CMAKE_CXX_COMPILER_ID} STREQUAL GNU)
  #message("compiler `GCC` detected")
  set(IDLIB_CXX_COMPILER_ID ${IDLIB_CXX_COMPILER_ID_GCC})
endif()

if (${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
  message("compiler `MSVC` detected")
  set(IDLIB_CXX_COMPILER_ID ${IDLIB_CXX_COMPILER_ID_MSVC})
endif()

macro(idlib_report_cxx_compiler_id)
  if (${IDLIB_CXX_COMPILER_ID} EQUAL ${IDLIB_CXX_COMPILER_ID_CLANG})
    message("  - Idlib CXX Compiler Id: CLANG")
  elseif (${IDLIB_CXX_COMPILER_ID} EQUAL ${IDLIB_CXX_COMPILER_ID_GCC})
    message("  - Idlib CXX Compiler Id: GCC")
  elseif (${IDLIB_CXX_COMPILER_ID} EQUAL ${IDLIB_CXX_COMPILER_ID_MSVC})
    message("  - Idlib CXX Compiler Id: MSVC")
  elseif (${IDLIB_CXX_COMPILER_ID} EQUAL ${IDLIB_CXX_COMPILER_ID_UNKNOWN})
    message("  - Idlib CXX Compiler Id: Unknown")
  else()
    message(FATAL_ERROR "unhandled enumeration element")
  endif()
endmacro()

# Platform name detection.

set(IDLIB_PLATFORM_ID_UNKNOWN 0)
set(IDLIB_PLATFORM_ID_X64 1)
set(IDLIB_PLATFORM_ID_X86 2)

if( CMAKE_SIZEOF_VOID_P EQUAL 8 )
    #message("platform `x64` detected")
    set(IDLIB_PLATFORM_ID ${IDLIB_PLATFORM_ID_X64})
elseif ( CMAKE_SIZEOF_VOID_P EQUAL 4)
    #message("platform `x86` detected" )
    set(IDLIB_PLATFORM_ID ${IDLIB_PLATFORM_ID_X86})
endif()

macro(idlib_report_platform_id)
  if (${IDLIB_PLATFORM_ID} EQUAL ${IDLIB_PLATFORM_ID_X64})
    message("  - Idlib Platform Id: x64")
  elseif (${IDLIB_PLATFORM_ID} EQUAL ${IDLIB_PLATFORM_ID_X86})
    message("  - Idlib Platform Id: x86")
  elseif (${IDLIB_PLATFORM_ID} EQUAL ${IDLIB_PLATFORM_ID_UNKNOWN})
    message("  - Idlib Platform Id: Unknown")
  else()
    message(FATAL_ERROR "unhandled enumeration element")
  endif()
endmacro()

# Multi target generator detection.

if (${IDLIB_CXX_COMPILER_ID} EQUAL ${IDLIB_CXX_COMPILER_ID_MSVC})
    set(IDLIB_IS_MULTI_TARGET_GENERATOR YES)
else()
    set(IDLIB_IS_MULTI_TARGET_GENERATOR NO)   
endif()

macro(idlib_report_is_multi_target_generator)
    if (IDLIB_IS_MULTI_TARGET_GENERATOR)
      message("  - Idlib Is Multi Target Generator: Yes")
    else()
      message("  - Idlib Is Multi Target Generator: NO")
    endif()
endmacro()

idlib_report_cxx_compiler_id()
idlib_report_platform_id()
idlib_report_is_multi_target_generator()
