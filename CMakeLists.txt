# Minimum required CMake version.
cmake_minimum_required(VERSION 3.6)

# Project name and language.
project(idlib CXX)

# == CCache ===================================================================================== #

# Enable ccache if it is available.
#find_program(CCACHE_FOUND ccache)
#if(CCACHE_FOUND)
#    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
#    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
#endif()

# == MSVC character encoding ==================================================================== #

if (${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
  add_definitions(-DUNICODE -D_UNICODE)
endif()

# == x86 / x64 detection ======================================================================== #

# This way it can be detected wether the target is x86 or x64.
# TODO: Isn't there a more semantic way to do this.
if( CMAKE_SIZEOF_VOID_P EQUAL 8 )
    MESSAGE( "64 bits compiler detected" )
    SET( EX_PLATFORM 64 )
	# The name of the platform as used in pathnames.
    SET( EX_PLATFORM_NAME "x64" )
elseif( CMAKE_SIZEOF_VOID_P EQUAL 4 ) 
    MESSAGE( "32 bits compiler detected" )
    SET( EX_PLATFORM 32 )
	# The name of the platform as used in pathnames.
    SET( EX_PLATFORM_NAME "x86" )
endif( CMAKE_SIZEOF_VOID_P EQUAL 8 )

macro(set_project_default_properties)
	# (1) GNU GCC specific settings
	# TODO: Raise an error if the MSVC version is too low.
	if (${CMAKE_CXX_COMPILER_ID} STREQUAL GNU)
	  message("compiler is GNUCC")
	  # Set standard to C++ 17, enable -Wall and -Wextra
	  add_definitions("-std=gnu++17 -Wall -Wextra -D_GNU_SOURCE")
	  # Disable some warnings
	  # TODO: IdLib can have these warnings enabled.
	  add_definitions("-Wno-reorder -Wno-sign-compare -Wno-missing-braces -Wno-unused-parameter")
	  # Enable optimizations that do not interfere with debug experience.
	  add_definitions("-Og")
	  # Enable extra debug information.
	  add_definitions("-ggdb3")
	endif()

    # (2) MSVC specific settings
    # TODO: Raise an error if the MSVC version is too low.
    if (${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
      if (MSVC_VERSION GREATER_EQUAL "1900")
        include(CheckCXXCompilerFlag)
        CHECK_CXX_COMPILER_FLAG("/std:c++latest" _cpp_latest_flag_supported)
        if (_cpp_latest_flag_supported)
          add_compile_options("/std:c++latest")
        endif()
      endif()
    endif()

	# (2) MSVC specific settings
	if (${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
	  message("compiler is MSVC")
	  set(variables
		  CMAKE_C_FLAGS_DEBUG
		  CMAKE_C_FLAGS_MINSIZEREL
		  CMAKE_C_FLAGS_RELEASE
		  CMAKE_C_FLAGS_RELWITHDEBINFO
		  CMAKE_CXX_FLAGS_DEBUG
		  CMAKE_CXX_FLAGS_MINSIZEREL
		  CMAKE_CXX_FLAGS_RELEASE
		  CMAKE_CXX_FLAGS_RELWITHDEBINFO)
	  foreach(variable ${variables})
		if(${variable} MATCHES "/MD")
		  string(REGEX REPLACE "/MD" "/MT" ${variable} "${${variable}}")
		endif()
	  endforeach()
	  set(MSVC_RUNTIME "static")
	endif()

	# (3) MSVC specific settings
	if (${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc")
	endif()
endmacro(set_project_default_properties)

# == output directories ========================================================================= #

# The output directories.
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/products/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/products/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/products/bin)

# For multi-target generators like MSVC, we specifiy disjoint output paths for targets.
foreach( OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES} )
	# Suffix for CMake's configuration type specific output path variables.
    string( TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG )
	# The name of the configuration as used in the pathnames.
    string( TOLOWER ${OUTPUTCONFIG} EX_CONFIGURATION_NAME )
	message("configurating output paths for ${EX_CONFIGURATION_NAME}")
    set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/products/${EX_CONFIGURATION_NAME}/${EX_PLATFORM_NAME}/bin )
    set( CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/products/${EX_CONFIGURATION_NAME}/${EX_PLATFORM_NAME}/lib )
    set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/products/${EX_CONFIGURATION_NAME}/${EX_PLATFORM_NAME}/lib )
endforeach( OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES )

# Add module "googletet".
set(googletest_dir "${CMAKE_CURRENT_SOURCE_DIR}/external/googletest")
set(CMAKE_CXX_FLAGS "-DGTEST_LANG_CXX11=1")
add_subdirectory("${googletest_dir}" EXCLUDE_FROM_ALL)

# Add subdirectories for the library and the tests.
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/library)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tests)
