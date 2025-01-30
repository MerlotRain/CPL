cmake_minimum_required(VERSION 3.10)
project(CommonPortabilityLibrary)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_TESTS "Build tests" OFF)

include(GenerateExportHeader)

find_package(double-conversion CONFIG REQUIRED)
find_package(Iconv REQUIRED)
find_package(fmt REQUIRED)
find_package(pcre2 CONFIG REQUIRED)

set(CPL_VERSION_MAJOR 1)
set(CPL_VERSION_MINOR 1)
set(CPL_VERSION_PATCH 0)
set(CPL_VERSION_STRING "${CPL_VERSION_MAJOR}.${CPL_VERSION_MINOR}.${CPL_VERSION_PATCH}")

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cpl_version.h.in
    ${CMAKE_CURRENT_BINARY_DIR}/cpl_version.h
)

set(cpl_headers 
	cpl_atomic.h
	cpl_byteendian.h
	cpl_datetime.h
	cpl_delegate.h
	cpl_delegateT.h
	cpl_flags.h
	cpl_mathhelp.h
	cpl_memorymanager.h
	cpl_object.h
	cpl_ports.h
	cpl_stringhelp.h
	cpl_any.h
	cpl_image.h
)

set(cpl_sources
	cpl_atomic.cpp
	cpl_byteendian.cpp
	cpl_datetime.cpp
	cpl_mathhelp.cpp
	cpl_memorymanager.cpp
	cpl_object.cpp
	cpl_stringhelp.cpp
	cpl_any.cpp
	cpl_image.cpp
)

add_library(cpl SHARED)
generate_export_header(
	cpl
	EXPORT_FILE_NAME ${CMAKE_CURRENT_BINARY_DIR}/cpl_exports.h
	EXPORT_MACRO_NAME CPL_API
)
set(cpl_headers ${cpl_headers} 
	${CMAKE_CURRENT_BINARY_DIR}/cpl_exports.h
	${CMAKE_CURRENT_BINARY_DIR}/cpl_version.h
)

target_sources(cpl PRIVATE ${cpl_headers} ${cpl_sources})
target_include_directories(cpl PUBLIC 
	${CMAKE_CURRENT_LIST_DIR} 
	${CMAKE_CURRENT_BINARY_DIR}
)

target_link_libraries(cpl PRIVATE 
	fmt::fmt 
	Iconv::Iconv 
	double-conversion::double-conversion 
	PCRE2::8BIT
)

if(WIN32)
	target_compile_definitions(cpl PUBLIC _USE_MATH_DEFINES)
endif()

add_library(CPL::cpl ALIAS cpl)
if(BUILD_TESTS)
	include(CTest)
	add_subdirectory(tests)
endif()