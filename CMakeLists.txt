
cmake_minimum_required(VERSION 3.0..3.24)
project(libm2 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(m2_include_files 
    ./include/preconfig.h
    ./include/m2.h
    ./include/m2/m2_allocator.h
    ./include/m2/m2_logger.h
    ./include/m2/text/m2_ascii.h
    ./include/m2/text/m2_regularexpression.h
    ./include/m2/text/m2_string.h
    ./include/m2/text/m2_stringlist.h
    ./include/m2/text/m2_stringtokenizer.h
    ./include/m2/text/m2_textconvertor.h
    ./include/m2/text/m2_utf8.h
    ./include/m2/text/m2_wstring.h
    ./include/m2/math/m2_bigdecimal.h
    ./include/m2/math/m2_biginteger.h
    ./include/m2/math/m2_math.h
    ./include/m2/math/m2_matrix4x4.h
    ./include/m2/math/m2_random.h
    ./include/m2/math/m2_transform.h
    ./include/m2/math/m2_unitsconvertor.h
    ./include/m2/math/m2_uuid.h
    ./include/m2/math/m2_vector.h
    ./include/m2/image/m2_color.h
    ./include/m2/image/m2_image.h
    ./include/m2/image/m2_margins.h
    ./include/m2/image/m2_pagesize.h
    ./include/m2/image/m2_point.h
    ./include/m2/image/m2_rect.h
    ./include/m2/image/m2_size.h
    )

set(m2_source_files 
    ./src/text/string.cpp
)

add_library(libm2 SHARED ${m2_include_files} ${m2_source_files})

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

target_include_directories(libm2 PRIVATE
    ./include
    ./include/m2
    ./include/m2/memory
    ./include/m2/text
    ./include/m2/tm
    ./include/m2/xml
    ./include/m2/thread
    ./include/m2/image
    ./include/m2/json
    ./include/m2/network
    ./include/m2/math
)

if(WIN32 AND NOT MINGW)
  set_source_files_properties(trace/stacktrace.cpp PROPERTIES COMPILE_FLAGS -wd4091)
endif()

if(WIN32 AND NOT MINGW)
  target_link_libraries(libm2 PRIVATE
    dbghelp
  )
endif()