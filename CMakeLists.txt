cmake_minimum_required(VERSION 3.0..3.24)
project(libm2 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(m2_include_files 
    ./include/preconfig.h
    ./include/m2.h
    ./include/m2/m2_allocator.h
    ./include/m2/m2_endian.h
    ./include/m2/m2_enummaskflag.h
    ./include/m2/m2_error.h
    ./include/m2/m2_flags.h
    ./include/m2/m2_object.h
    ./include/m2/m2_trace.h
    ./include/m2/m2_variant.h

    ./include/m2/io/m2_buffer.h
    ./include/m2/io/m2_bytearray.h
    ./include/m2/io/m2_datastream.h
    ./include/m2/io/m2_dir.h
    ./include/m2/io/m2_file.h
    ./include/m2/io/m2_fileinfo.h
    ./include/m2/io/m2_iobase.h
    ./include/m2/io/m2_iodevice.h
    ./include/m2/io/m2_iot.h
    ./include/m2/io/m2_library.h
    ./include/m2/io/m2_lockfile.h
    ./include/m2/io/m2_logger.h
    ./include/m2/io/m2_process.h
    ./include/m2/io/m2_qrcode.h
    ./include/m2/io/m2_serialize.h
    ./include/m2/io/m2_sharedmemory.h
    ./include/m2/io/m2_urlparser.h

    ./include/m2/m2_object.h
    ./include/m2/text/m2_ascii.h
    ./include/m2/text/m2_regularexpression.h
    ./include/m2/text/m2_string.h
    ./include/m2/text/m2_stringlist.h
    ./include/m2/text/m2_stringtokenizer.h
    ./include/m2/text/m2_textconvertor.h
    ./include/m2/text/m2_wstring.h

    ./include/m2/math/m2_bigdecimal.h
    ./include/m2/math/m2_biginteger.h
    ./include/m2/math/m2_cryptographichash.h
    ./include/m2/math/m2_encryption.h
    ./include/m2/math/m2_geometrymath.h
    ./include/m2/math/m2_math.h
    ./include/m2/math/m2_random.h
    ./include/m2/math/m2_transform.h
    ./include/m2/math/m2_unitsconvertor.h
    ./include/m2/math/m2_uuid.h
    ./include/m2/math/m2_vector.h

    ./include/m2/image/m2_bezier.h
    ./include/m2/image/m2_circle.h
    ./include/m2/image/m2_color.h
    ./include/m2/image/m2_colorramp.h
    ./include/m2/image/m2_colorscheme.h
    ./include/m2/image/m2_ellipse.h
    ./include/m2/image/m2_image.h
    ./include/m2/image/m2_line.h
    ./include/m2/image/m2_margins.h
    ./include/m2/image/m2_pagesize.h
    ./include/m2/image/m2_point.h
    ./include/m2/image/m2_polygon.h
    ./include/m2/image/m2_rbtree.h
    ./include/m2/image/m2_rect.h
    ./include/m2/image/m2_regularpolygon.h
    ./include/m2/image/m2_size.h
    ./include/m2/image/m2_triangle.h

    ./include/m2/thread/m2_backgroundtask.h
    ./include/m2/thread/m2_mutex.h
    ./include/m2/thread/m2_rwlock.h
    ./include/m2/thread/m2_safeobject.h
    ./include/m2/thread/m2_semaphore.h
    ./include/m2/thread/m2_thread.h
    ./include/m2/thread/m2_waitcondition.h

    ./include/m2/tm/m2_clock.h
    ./include/m2/tm/m2_datetime.h
    ./include/m2/tm/m2_deadlinetimer.h
    ./include/m2/tm/m2_timer.h
    ./include/m2/tm/m2_timespan.h
    ./include/m2/tm/m2_timestamp.h
    ./include/m2/tm/m2_timezone.h

    ./include/m2/sql/m2_sqldatabase.h
    ./include/m2/sql/m2_sqlstatement.h
    )

set(m2_source_files 
    ./src/image/m2_pagesize.cpp
    
    ./src/io/m2_buffer.cpp
    ./src/io/m2_bytearray.cpp
    
    ./src/text/m2_string.cpp

    ./src/sql/m2_sqldatabase.cpp
    ./src/sql/m2_sqldriver.cpp
    ./src/sql/m2_sqldriver.h
    ./src/sql/sqldrivers/sqlite/m2_sqlitedriver.cpp
    ./src/sql/sqldrivers/sqlite/m2_sqlitedriver.h
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
    ./include/help
    ./include/m2
    ./include/m2/image
    ./include/m2/io
    ./include/m2/json
    ./include/m2/math
    ./include/m2/network
    ./include/m2/sql
    ./include/m2/text
    ./include/m2/thread
    ./include/m2/tm
    ./include/m2/xml
)

if(WIN32 AND NOT MINGW)
  set_source_files_properties(trace/stacktrace.cpp PROPERTIES COMPILE_FLAGS -wd4091)
endif()

if(WIN32 AND NOT MINGW)
  target_link_libraries(libm2 PRIVATE
    dbghelp
  )
endif()