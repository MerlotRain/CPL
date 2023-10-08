
cmake_minimum_required(VERSION 3.0..3.24)
PROJECT(gsutility)

add_library(${PROJECT_NAME} SHARED)

if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    target_compile_definitions(${PROJECT_NAME} PRIVATE UTILITY_LIBRARY)
    target_compile_definitions(${PROJECT_NAME} PRIVATE XPCORE_EXPORTS)
    target_compile_definitions(${PROJECT_NAME} PRIVATE JSON_DLL_BUILD)
    target_compile_definitions(${PROJECT_NAME} PRIVATE SQLITE_ENABLE_COLUMN_METADATA)
    target_compile_definitions(${PROJECT_NAME} PRIVATE SQLITE_ENABLE_FTS3)
    target_compile_definitions(${PROJECT_NAME} PRIVATE SQLITE_ENABLE_FTS3_PARENTHESIS)
    target_compile_definitions(${PROJECT_NAME} PRIVATE SQLITE_ENABLE_FTS5)
    target_compile_definitions(${PROJECT_NAME} PRIVATE SQLITE_ENABLE_JSON1)
    target_compile_definitions(${PROJECT_NAME} PRIVATE SQLITE_ENABLE_RTREE)
    target_compile_definitions(${PROJECT_NAME} PRIVATE SQLITE_OMIT_COMPLETE)
    target_compile_definitions(${PROJECT_NAME} PRIVATE _NO_CVCONST_H)
elseif (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    target_compile_definitions(${PROJECT_NAME} PRIVATE -UTILITY_LIBRARY)
    target_compile_definitions(${PROJECT_NAME} PRIVATE -SQLITE_ENABLE_COLUMN_METADATA)
    target_compile_definitions(${PROJECT_NAME} PRIVATE -SQLITE_ENABLE_FTS3)
    target_compile_definitions(${PROJECT_NAME} PRIVATE -SQLITE_ENABLE_FTS3_PARENTHESIS)
    target_compile_definitions(${PROJECT_NAME} PRIVATE -SQLITE_ENABLE_FTS5)
    target_compile_definitions(${PROJECT_NAME} PRIVATE -SQLITE_ENABLE_JSON1)
    target_compile_definitions(${PROJECT_NAME} PRIVATE -SQLITE_ENABLE_RTREE)
    target_compile_definitions(${PROJECT_NAME} PRIVATE -SQLITE_OMIT_COMPLETE)
elseif (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    target_compile_definitions(${PROJECT_NAME} PRIVATE UTILITY_LIBRARY)
    target_compile_definitions(${PROJECT_NAME} PRIVATE SQLITE_ENABLE_COLUMN_METADATA)
    target_compile_definitions(${PROJECT_NAME} PRIVATE SQLITE_ENABLE_FTS3)
    target_compile_definitions(${PROJECT_NAME} PRIVATE SQLITE_ENABLE_FTS3_PARENTHESIS)
    target_compile_definitions(${PROJECT_NAME} PRIVATE SQLITE_ENABLE_FTS5)
    target_compile_definitions(${PROJECT_NAME} PRIVATE SQLITE_ENABLE_JSON1)
    target_compile_definitions(${PROJECT_NAME} PRIVATE SQLITE_ENABLE_RTREE)
    target_compile_definitions(${PROJECT_NAME} PRIVATE SQLITE_OMIT_COMPLETE)
endif ()

target_sources(${PROJECT_NAME} PRIVATE
    ${UTILITY_INCLUDE_DIR}/configuration.h
    ${UTILITY_INCLUDE_DIR}/datetime.h
    ${UTILITY_INCLUDE_DIR}/delegate.h
    ${UTILITY_INCLUDE_DIR}/delegateT.h
    ${UTILITY_INCLUDE_DIR}/encryption.h
    ${UTILITY_INCLUDE_DIR}/endian.h
    ${UTILITY_INCLUDE_DIR}/filesystem.h
    ${UTILITY_INCLUDE_DIR}/flags.h
    ${UTILITY_INCLUDE_DIR}/http.h
    ${UTILITY_INCLUDE_DIR}/html.h
    ${UTILITY_INCLUDE_DIR}/image.h
    ${UTILITY_INCLUDE_DIR}/iot.h
    ${UTILITY_INCLUDE_DIR}/jsonfile.h
    ${UTILITY_INCLUDE_DIR}/library.h
    ${UTILITY_INCLUDE_DIR}/locker.h
    ${UTILITY_INCLUDE_DIR}/logger.h
    ${UTILITY_INCLUDE_DIR}/mathhelp.h
    ${UTILITY_INCLUDE_DIR}/matrix.h
    ${UTILITY_INCLUDE_DIR}/memorymanager.h
    ${UTILITY_INCLUDE_DIR}/object.h
    ${UTILITY_INCLUDE_DIR}/preconfig.h
    ${UTILITY_INCLUDE_DIR}/process.h
    ${UTILITY_INCLUDE_DIR}/qrcode.h
    ${UTILITY_INCLUDE_DIR}/shape.inl
    ${UTILITY_INCLUDE_DIR}/sharedmemory.h
    ${UTILITY_INCLUDE_DIR}/socket.h
    ${UTILITY_INCLUDE_DIR}/sqldatabase.h
    ${UTILITY_INCLUDE_DIR}/sqlite3.h
    ${UTILITY_INCLUDE_DIR}/sqlitehelp.h
    ${UTILITY_INCLUDE_DIR}/stlhelp.h
    ${UTILITY_INCLUDE_DIR}/stringhelp.h
    ${UTILITY_INCLUDE_DIR}/timer.h
    ${UTILITY_INCLUDE_DIR}/tinyxml2.h
    ${UTILITY_INCLUDE_DIR}/trace.h
    ${UTILITY_INCLUDE_DIR}/variant.h
    ${UTILITY_INCLUDE_DIR}/workthread.h
    ${UTILITY_INCLUDE_DIR}/zipper.h

)

target_sources(${PROJECT_NAME} PRIVATE
    configuration/jsonserializestream.cpp
    configuration/jsonserializestream.h
    configuration/serialize.cpp
    configuration/xmlserializestream.cpp
    configuration/xmlserializestream.h
    datetime/clock.cpp
    datetime/datetime.cpp
    datetime/deallinetimer.cpp
    datetime/elapsedtimer.cpp
    datetime/timer.cpp
    datetime/timespan.cpp
    datetime/timestamp.cpp
    datetime/timezone.cpp
    encryption/cryptographichash.cpp
    filesystem/dir.cpp
    filesystem/file.cpp

    image/bmpimageio.cpp
    image/color.cpp
    image/ddsimageio.cpp
    image/gifimageio.cpp
    image/icoimageio.cpp
    image/image.cpp
    image/imageio.cpp
    image/imageprocess.cpp
    image/pngimageio.cpp
    image/ppmimageio.cpp
    image/rect.cpp
    image/size.cpp
    image/svgimageio.cpp
    image/tgaimageio.cpp
    image/tiffimageio.cpp
    image/wbmpimageio.cpp
    image/webpimageio.cpp
    image/xbmimageio.cpp
    image/xpmimageio.cpp
    json/libjson/arraylist.h
    json/libjson/config.h
    json/libjson/debug.h
    json/libjson/json.h
    json/libjson/json_c_version.h
    json/libjson/json_config.h
    json/libjson/json_inttypes.h
    json/libjson/json_object.h
    json/libjson/json_object_private.h
    json/libjson/json_tokener.h
    json/libjson/json_util.h
    json/libjson/linkhash.h
    json/libjson/json_object_iterator.h
    json/libjson/printbuf.h
    json/libjson/symbol_renames.h
    json/libjson/arraylist.c
    json/libjson/debug.c
    json/libjson/json_c_version.c
    json/libjson/json_object.c
    json/libjson/json_object_iterator.c
    json/libjson/json_tokener.c
    json/libjson/json_util.c
    json/libjson/linkhash.c
    json/libjson/printbuf.c
    json/libjson/random_seed.c
    json/libjson/strerror_override.c
    json/jsonfile.cpp
    math/bigdecimal.cpp
    math/biginteger.cpp
    math/mathvector.cpp
    math/math_traits.h
    math/random.cpp
    math/sine_table.cpp
    math/unitarea.cpp
    math/unitlength.cpp
    math/unitvolume.cpp
    math/uuid.cpp
    memorymanager/bitset.cpp
    memorymanager/bytebuffer.cpp
    memorymanager/bytebufferstream.cpp
    memorymanager/cborserializestream.cpp
    memorymanager/cborserializestream.h
    memorymanager/fileinputstream.cpp
    memorymanager/fileoutputstream.cpp
    memorymanager/filesystem.cpp
    memorymanager/inputstream.cpp
    memorymanager/memoryinputstream.cpp
    memorymanager/memoryoutputstream.cpp
    memorymanager/operatorsystemenvironment.cpp
    memorymanager/outputstream.cpp
    sql/sqlite/sqlite3.c
    sql/sqlite/sqlitehelp.cpp
    sql/sqlfield.cpp
    sql/sqlstatement.cpp
    stringhelp/ascii.cpp
    stringhelp/numericstring.cpp
    stringhelp/numericstring.h
    stringhelp/regularexpression.cpp
    stringhelp/string.cpp
    stringhelp/stringlist.cpp
    stringhelp/stringstream.cpp
    stringhelp/stringtokenizer.cpp
    stringhelp/textconverter.cpp
    stringhelp/wstring.cpp
    thread/backgroundtask.cpp
    thread/condition.cpp
    thread/handleholder.h
    thread/mutex.cpp
    thread/packagedtask.cpp
    thread/pipe.cpp
    thread/pipehandle.h
    thread/process.cpp
    thread/processhandle.cpp
    thread/processhandle.h
    thread/rwlock.cpp
    thread/semaphore.cpp
    thread/waitevent.cpp
    thread/waitevent.h
    thread/workthread.cpp
    trace/crashreport.cpp
    trace/error.cpp
    trace/stacktrace.cpp
    classfactory.cpp
    endian.cpp
    library.cpp
    logger.cpp
    object.cpp
    sharedmemory.cpp
    sharedmemoryhandle.cpp
    sharedmemoryhandle.h
    stlhelp.cpp
    tinyxml2.cpp
    variant.cpp

)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${UTILITY_INCLUDE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

if(WIN32 AND NOT MINGW)
  set_source_files_properties(trace/stacktrace.cpp PROPERTIES COMPILE_FLAGS -wd4091)
endif()

if(WIN32 AND NOT MINGW)
  target_link_libraries(${PROJECT_NAME} PRIVATE
    dbghelp
  )
endif()