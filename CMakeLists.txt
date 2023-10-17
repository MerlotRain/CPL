##############################################################################
# Part of CMake configuration for M2
# Copyright (c) 2023 MerlotRain.
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to
# deal in the Software without restriction, including without limitation the
# rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
# sell copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
# IN THE SOFTWARE.
# 
##############################################################################
cmake_minimum_required(VERSION 3.20)

#-----------------------------------------------------------------------------
# Version
#-----------------------------------------------------------------------------
file(READ VERSION.txt _version_)
string(REGEX MATCH "M2_VERSION_MAJOR=([0-9]+)" _ ${_version_})
set(_version_major ${CMAKE_MATCH_1})
string(REGEX MATCH "M2_VERSION_MINOR=([0-9]+)" _ ${_version_})
set(_version_minor ${CMAKE_MATCH_1})
string(REGEX MATCH "M2_VERSION_PATCH=([0-9]+)" _ ${_version_})
set(_version_patch ${CMAKE_MATCH_1})
string(REGEX MATCH "M2_PATCH_WORD=([a-zA-Z0-9]+)" _ ${_version_})
set(_version_patch_word ${CMAKE_MATCH_1})

unset(_version_)

#-----------------------------------------------------------------------------
# Project
#-----------------------------------------------------------------------------
if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.9)
  list(APPEND _project_info DESCRIPTION "M2 - C++ API for cross platform")
endif()

project(libm2 VERSION "${_version_major}.${_version_minor}.${_version_patch}"
  LANGUAGES C CXX
  ${_project_info})

if(NOT "${_version_patch_word}" STREQUAL "")
  # Re-write VERSION variables after project()
  set(M2_VERSION "${M2_VERSION}${_version_patch_word}")
  set(M2_VERSION_PATCH "${_version_patch}${_version_patch_word}")
endif()
set(M2_VERSION_NOPATCH "${_version_major}.${_version_minor}.${_version_patch}")

unset(_version_major)
unset(_version_minor)
unset(_version_patch)
unset(_version_patch_word)

message(STATUS "M2: Version ${M2_VERSION}")

if(CMAKE_VERSION VERSION_LESS 3.21)
  if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    set(PROJECT_IS_TOP_LEVEL ON)
  else()
    set(PROJECT_IS_TOP_LEVEL OFF)
  endif()
endif()

#-----------------------------------------------------------------------------
# Setup
#-----------------------------------------------------------------------------

set(DEFAULT_BUILD_TYPE Release)
if(${CMAKE_GENERATOR} MATCHES "Visual Studio")
  cmake_minimum_required(VERSION 3.13 FATAL_ERROR)
endif()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

#-----------------------------------------------------------------------------
# Options
#-----------------------------------------------------------------------------
## CMake global variables
option(BUILD_SHARED_LIBS "Build GEOS with shared libraries" ON)
set(CMAKE_CXX_STANDARD 17 CACHE STRING "C++ standard version to use (default is 17)")

#-----------------------------------------------------------------------------
# Setup build directories
#-----------------------------------------------------------------------------
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)
message(STATUS "M2: Run-time output: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
message(STATUS "M2: Archives output: ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")

#-----------------------------------------------------------------------------
# Add ASAN build option
#-----------------------------------------------------------------------------
set(CMAKE_C_FLAGS_ASAN "${CMAKE_C_FLAGS_DEBUG} -fsanitize=address -fno-omit-frame-pointer -fno-common")
set(CMAKE_CXX_FLAGS_ASAN "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address -fno-omit-frame-pointer -fno-common")
set(CMAKE_EXE_LINKER_FLAGS_ASAN "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -fsanitize=address")
set(CMAKE_SHARED_LINKER_FLAGS_ASAN "${CMAKE_SHARED_LINKER_FLAGS_DEBUG} -fsanitize=address")

get_property(_cmake_build_type_is_cache CACHE CMAKE_BUILD_TYPE PROPERTY TYPE)
if (_cmake_build_type_is_cache)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo" "ASAN")
endif()
unset(_cmake_build_type_is_cache)

#-----------------------------------------------------------------------------
# Install directories
#-----------------------------------------------------------------------------

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

#-----------------------------------------------------------------------------
# C++ language version and compilation flags
#-----------------------------------------------------------------------------
message(STATUS "M2: Require C++${CMAKE_CXX_STANDARD}")
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#-----------------------------------------------------------------------------
# Target libm2
#-----------------------------------------------------------------------------
add_library(libm2 "")
add_library(M2::libm2 ALIAS libm2)
add_subdirectory(include)
add_subdirectory(src)

if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    target_compile_definitions(libm2 PRIVATE M2_LIBRARY)
    target_compile_definitions(libm2 PRIVATE XPCORE_EXPORTS)
    target_compile_definitions(libm2 PRIVATE JSON_DLL_BUILD)
    target_compile_definitions(libm2 PRIVATE SQLITE_ENABLE_COLUMN_METADATA)
    target_compile_definitions(libm2 PRIVATE SQLITE_ENABLE_FTS3)
    target_compile_definitions(libm2 PRIVATE SQLITE_ENABLE_FTS3_PARENTHESIS)
    target_compile_definitions(libm2 PRIVATE SQLITE_ENABLE_FTS5)
    target_compile_definitions(libm2 PRIVATE SQLITE_ENABLE_JSON1)
    target_compile_definitions(libm2 PRIVATE SQLITE_ENABLE_RTREE)
    target_compile_definitions(libm2 PRIVATE SQLITE_OMIT_COMPLETE)
    target_compile_definitions(libm2 PRIVATE _NO_CVCONST_H)
elseif (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    target_compile_definitions(libm2 PRIVATE -M2_LIBRARY)
    target_compile_definitions(libm2 PRIVATE -SQLITE_ENABLE_COLUMN_METADATA)
    target_compile_definitions(libm2 PRIVATE -SQLITE_ENABLE_FTS3)
    target_compile_definitions(libm2 PRIVATE -SQLITE_ENABLE_FTS3_PARENTHESIS)
    target_compile_definitions(libm2 PRIVATE -SQLITE_ENABLE_FTS5)
    target_compile_definitions(libm2 PRIVATE -SQLITE_ENABLE_JSON1)
    target_compile_definitions(libm2 PRIVATE -SQLITE_ENABLE_RTREE)
    target_compile_definitions(libm2 PRIVATE -SQLITE_OMIT_COMPLETE)
elseif (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    target_compile_definitions(libm2 PRIVATE M2_LIBRARY)
    target_compile_definitions(libm2 PRIVATE SQLITE_ENABLE_COLUMN_METADATA)
    target_compile_definitions(libm2 PRIVATE SQLITE_ENABLE_FTS3)
    target_compile_definitions(libm2 PRIVATE SQLITE_ENABLE_FTS3_PARENTHESIS)
    target_compile_definitions(libm2 PRIVATE SQLITE_ENABLE_FTS5)
    target_compile_definitions(libm2 PRIVATE SQLITE_ENABLE_JSON1)
    target_compile_definitions(libm2 PRIVATE SQLITE_ENABLE_RTREE)
    target_compile_definitions(libm2 PRIVATE SQLITE_OMIT_COMPLETE)
endif ()

if(WIN32 AND NOT MINGW)
  target_link_libraries(libm2 PRIVATE
    dbghelp
  )
endif()

#-----------------------------------------------------------------------------
# Tests
#-----------------------------------------------------------------------------
if(PROJECT_IS_TOP_LEVEL)
  include(CTest)
  if(BUILD_TESTING)
    add_subdirectory(tests)
  endif()
endif()

#-----------------------------------------------------------------------------
# Install and export targets - support 'make install' or equivalent
#-----------------------------------------------------------------------------
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/m2-config-version.cmake"
  VERSION ${M2_VERSION}
  COMPATIBILITY AnyNewerVersion
)

configure_file(cmake/m2-config.cmake
  "{CMAKE_CURRENT_BINARY_DIR}/m2-config.cmake"
  COPYONLY)

# install(TARGET libm2 
#   EXPORT libm2-target
#   LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#   ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
#   RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
#   INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
#   )

# install(EXPORT libm2-target
#   FILE libm2-target.cmake
#   NAMESPACE libm2::
#   DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/libm2)

# install(FILES
#   "${CMAKE_CURRENT_BINARY_DIR}/libm2-config.cmake"
#   "${CMAKE_CURRENT_BINARY_DIR}/libm2-config-version.cmake"
#   DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/libm2)
# install(DIRECTORY
#   "${CMAKE_CURRENT_LIST_DIR}/include/libm2"
#   "${CMAKE_CURRENT_BINARY_DIR}/include/libm2"
#   DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
#   FILES_MATCHING PATTERN "*.h")
# install(DIRECTORY
#   "${CMAKE_CURRENT_LIST_DIR}/include/libm2"
#   "${CMAKE_CURRENT_BINARY_DIR}/include/libm2"
#   DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
#   FILES_MATCHING PATTERN "*.hpp")
# install(FILES "${CMAKE_CURRENT_LIST_DIR}/include/libm2.h"
#   DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

#-----------------------------------------------------------------------------
# Uninstall
#-----------------------------------------------------------------------------