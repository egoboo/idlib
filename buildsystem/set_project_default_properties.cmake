include(${CMAKE_CURRENT_LIST_FILE}/../detect_compiler_and_platform.cmake)

# == Doxygen ==================================================================================== #

# Find Doxygen.
# Remark: CMake 3.10 fails under Cygwin for no reason on FIND_PACKAGE(Doxygen).
FIND_PACKAGE(Doxygen)
IF(NOT DOXYGEN_FOUND)
	MESSAGE(STATUS "Doxygen not found. You won't be able to build documentation.")
ENDIF()

# == Default project settings =================================================================== #

# Macro adjusting (mostly compiler-specific) properties of a project.
macro(set_project_default_properties)
	if (${IDLIB_CXX_COMPILER_ID} EQUAL ${IDLIB_CXX_COMPILER_ID_MSVC})
	  message("case of MSVC: add_definitions(-DUNICODE -D_UNICODE)")
	  add_definitions(-DUNICODE -D_UNICODE)
	endif()

	# Non-MSVC-specific settings: The project compiles against C++ 17.
	if (NOT ${IDLIB_CXX_COMPILER_ID} EQUAL ${IDLIB_CXX_COMPILER_ID_MSVC})
	  message("case of NOT MSVC: set(CMAKE_CXX_STANDARD 17)")
	  set(CMAKE_CXX_STANDARD 17)
	endif()

	# GNU GCC specific settings
	if (${IDLIB_CXX_COMPILER_ID} EQUAL ${IDLIB_CXX_COMPILER_ID_GCC})
	  message("case of GCC")
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
    if (${IDLIB_CXX_COMPILER_ID} EQUAL ${IDLIB_CXX_COMPILER_ID_MSVC})
      message("case of MSVC")
	  if (MSVC_VERSION GREATER_EQUAL "1900")
        include(CheckCXXCompilerFlag)
        CHECK_CXX_COMPILER_FLAG("/std:c++latest" _cpp_latest_flag_supported)
        if (_cpp_latest_flag_supported)
          add_compile_options("/std:c++latest")
        endif()
      endif()
    endif()

	# (2) MSVC specific settings
	if (${IDLIB_CXX_COMPILER_ID} EQUAL ${IDLIB_CXX_COMPILER_ID_MSVC})
	  message("case of MSVC")
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
	if (${IDLIB_CXX_COMPILER_ID} EQUAL ${IDLIB_CXX_COMPILER_ID_MSVC})
	    message("case of MSVC")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc")
	endif()
endmacro(set_project_default_properties)

# For configuring the output paths, we distinguish between single- and multi-target generators.
if (IDLIB_IS_MULTI_TARGET_GENERATOR)
    #message("multi-target generator")
	# For multi-target generators like MSVC, we specify disjoint output paths for targets.
	foreach( OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES} )
		# Suffix for CMake's configuration type specific output path variables.
		string( TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG )
		# The name of the output configuration as used in the pathnames.
		string( TOLOWER ${OUTPUTCONFIG} OUTPUTCONFIG_FOLDER_NAME)
		# The name of the output platform as used in the pathnames.
	    if (${IDLIB_PLATFORM_ID} EQUAL ${IDLIB_PLATFORM_ID_X64})
	       set(OUTPUTPLATFORM_FOLDER_NAME "x64")
		elseif (${IDLIB_PLATFORM_ID} EQUAL ${IDLIB_PLATFORM_ID_X86})
		   set(OUTPUTPLATFORM_FOLDER_NAME "x86")
		else()
	      message(FATAL_ERROR "unhandled enumeration element")		
		endif()
	    message("  - Idlib Platform Id: x86")
		message("  - path for CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} is")
		message("    ${CMAKE_BINARY_DIR}/products/${OUTPUTCONFIG_FOLDER_NAME}/${OUTPUTPLATFORM_FOLDER_NAME}/bin")
		set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/products/${OUTPUTCONFIG_FOLDER_NAME}/${OUTPUTPLATFORM_FOLDER_NAME}/bin )
		message("  - path for CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} is")
		message("    ${CMAKE_BINARY_DIR}/products/${OUTPUTCONFIG_FOLDER_NAME}/${OUTPUTPLATFORM_FOLDER_NAME}/lib")
		set( CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/products/${OUTPUTCONFIG_FOLDER_NAME}/${OUTPUTPLATFORM_FOLDER_NAME}/lib )
		message("  - path for CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} is")
		message("    ${CMAKE_BINARY_DIR}/products/${OUTPUTCONFIG_FOLDER_NAME}/${OUTPUTPLATFORM_FOLDER_NAME}/lib")
		set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/products/${OUTPUTCONFIG_FOLDER_NAME}/${OUTPUTPLATFORM_FOLDER_NAME}/lib )
	endforeach( OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES )
else()
    #message("single-target generator")
	
	# The name of the output platform as used in the pathnames.
	if (${IDLIB_PLATFORM_ID} EQUAL ${IDLIB_PLATFORM_ID_X64})
	   set(OUTPUTPLATFORM_FOLDER_NAME "x64")
	elseif (${IDLIB_PLATFORM_ID} EQUAL ${IDLIB_PLATFORM_ID_X86})
	   set(OUTPUTPLATFORM_FOLDER_NAME "x86")
	else()
	  message(FATAL_ERROR "unhandled enumeration element")		
	endif()
	
	# Adjust the archive output directory.
	set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/products/${OUTPUTPLATFORM_FOLDER_NAME}/lib)

	# Adjust the library output directory.
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/products/${OUTPUTPLATFORM_FOLDER_NAME}/lib)

	# Adjust the runtime output directory.
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/products/${OUTPUTPLATFORM_FOLDER_NAME}/bin)
endif()

# This adds the module Google Test.
macro(include_google_test)
	# This ensures that Google Test is compiled against C++ 17.
	# TODO: However, isn't it possible to simply use set(CMAKE_CXX_STANDARD 17)?
	if (${IDLIB_CXX_COMPILER_ID} EQUAL ${IDLIB_CXX_COMPILER_ID_CLANG})
	  set(CMAKE_CXX_FLAGS "-DGTEST_LANG_CXX11=1 -std=gnu++11")
	else()
	  set(CMAKE_CXX_FLAGS "-DGTEST_LANG_CXX11=1")
	endif()
	# Remember the Google Test directory.
	if (NOT DEFINED IDLIB_PATH)
	  set(googletest_dir "${CMAKE_CURRENT_SOURCE_DIR}/external/googletest")
	else()
	  set(googletest_dir "${IDLIB_PATH}/external/googletest")
	endif()
	# Add the Google Test directory.
	add_subdirectory("${googletest_dir}" EXCLUDE_FROM_ALL)
endmacro()
