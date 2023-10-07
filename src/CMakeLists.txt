
cmake_minimum_required(VERSION 3.0..3.24)
PROJECT(gsutility)

add_library(${PROJECT_NAME} SHARED)

IF (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
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
    ${UTILITY_INCLUDE_DIR}/bigdecimal.h
    ${UTILITY_INCLUDE_DIR}/biginteger.h
    ${UTILITY_INCLUDE_DIR}/bitset.h
    ${UTILITY_INCLUDE_DIR}/bytebuffer.h
    ${UTILITY_INCLUDE_DIR}/color.h
    ${UTILITY_INCLUDE_DIR}/configuration.h
    ${UTILITY_INCLUDE_DIR}/cryptographichash.h
    ${UTILITY_INCLUDE_DIR}/datastream.h
    ${UTILITY_INCLUDE_DIR}/datetime.h
    ${UTILITY_INCLUDE_DIR}/delegate.h
    ${UTILITY_INCLUDE_DIR}/delegateT.h
    ${UTILITY_INCLUDE_DIR}/encryption.h
    ${UTILITY_INCLUDE_DIR}/endian.h
    ${UTILITY_INCLUDE_DIR}/error.h
    ${UTILITY_INCLUDE_DIR}/exception.h
    ${UTILITY_INCLUDE_DIR}/filesystem.h
    ${UTILITY_INCLUDE_DIR}/flags.h
    ${UTILITY_INCLUDE_DIR}/globalstatic.h
    ${UTILITY_INCLUDE_DIR}/http.h
    ${UTILITY_INCLUDE_DIR}/html.h
    ${UTILITY_INCLUDE_DIR}/image.h
    ${UTILITY_INCLUDE_DIR}/iot.h
    ${UTILITY_INCLUDE_DIR}/jsonfile.h
    ${UTILITY_INCLUDE_DIR}/library.h
    ${UTILITY_INCLUDE_DIR}/locker.h
    ${UTILITY_INCLUDE_DIR}/logger.h
    ${UTILITY_INCLUDE_DIR}/mathhelp.h
    ${UTILITY_INCLUDE_DIR}/mathvector.h
    ${UTILITY_INCLUDE_DIR}/matrix.h
    ${UTILITY_INCLUDE_DIR}/object.h
    ${UTILITY_INCLUDE_DIR}/packagedtask.h
    ${UTILITY_INCLUDE_DIR}/preconfig.h
    ${UTILITY_INCLUDE_DIR}/process.h
    ${UTILITY_INCLUDE_DIR}/qrcode.h
    ${UTILITY_INCLUDE_DIR}/random.h
    ${UTILITY_INCLUDE_DIR}/regularexpression.h
    ${UTILITY_INCLUDE_DIR}/serialize.h
    ${UTILITY_INCLUDE_DIR}/shape.h
    ${UTILITY_INCLUDE_DIR}/shape.inl
    ${UTILITY_INCLUDE_DIR}/sharedmemory.h
    ${UTILITY_INCLUDE_DIR}/socket.h
    ${UTILITY_INCLUDE_DIR}/sqldatabase.h
    ${UTILITY_INCLUDE_DIR}/sqlite3.h
    ${UTILITY_INCLUDE_DIR}/sqlitehelp.h
    ${UTILITY_INCLUDE_DIR}/stlhelp.h
    ${UTILITY_INCLUDE_DIR}/stringhelp.h
    ${UTILITY_INCLUDE_DIR}/stringtokenizer.h
    ${UTILITY_INCLUDE_DIR}/timer.h
    ${UTILITY_INCLUDE_DIR}/tinyxml2.h
    ${UTILITY_INCLUDE_DIR}/trace.h
    ${UTILITY_INCLUDE_DIR}/unitsconverter.h
    ${UTILITY_INCLUDE_DIR}/urlparser.h
    ${UTILITY_INCLUDE_DIR}/uuid.h
    ${UTILITY_INCLUDE_DIR}/variant.h
    ${UTILITY_INCLUDE_DIR}/workthread.h
    ${UTILITY_INCLUDE_DIR}/zipper.h

)

target_sources(${PROJECT_NAME} PRIVATE
    #平台
    exception_p.h
    error.cpp
    tinyxml2.cpp
    variant.cpp
    logger.cpp
    crthelp.cpp
    # json库
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
    #字符库
    text/ascii.cpp
    text/numericstring.cpp
    text/numericstring.h
    text/regularexpression.cpp
    text/string.cpp
    text/stringlist.cpp
    text/stringstream.cpp
    text/stringtokenizer.cpp
    text/textconverter.cpp
    text/wstring.cpp
    #对象和内存模型库
    byte/bitset.cpp
    byte/bytebuffer.cpp
    byte/classfactory.cpp
    byte/endian.cpp
    byte/library.cpp
    byte/object.cpp
    byte/sharedmemory.cpp
    byte/sharedmemoryhandle.cpp
    byte/sharedmemoryhandle.h
    byte/stlhelp.cpp
    #数据流操作
    stream/bytebufferstream.cpp
    stream/cborserializestream.cpp
    stream/cborserializestream.h
    stream/dir.cpp
    stream/file.cpp
    stream/fileinputstream.cpp
    stream/fileoutputstream.cpp
    stream/filesystem.cpp
    stream/inputstream.cpp
    stream/jsonserializestream.cpp
    stream/jsonserializestream.h
    stream/memoryinputstream.cpp
    stream/memoryoutputstream.cpp
    stream/operatorsystemenvironment.cpp
    stream/outputstream.cpp
    stream/serialize.cpp
    stream/xmlserializestream.cpp
    stream/xmlserializestream.h
    #数学库
    math/bigdecimal.cpp
    math/biginteger.cpp
    math/cryptographichash.cpp
    math/mathvector.cpp
    math/random.cpp
    math/sine_table.cpp
    math/uuid.cpp
    math/unitarea.cpp
    math/unitlength.cpp
    math/unitvolume.cpp
    #时间库
    tm/clock.cpp
    tm/datetime.cpp
    tm/deallinetimer.cpp
    tm/elapsedtimer.cpp
    tm/timespan.cpp
    tm/timezone.cpp
    tm/timestamp.cpp
    #图像库
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
    #线程模块
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
    #sql
    sql/sqlite/sqlite3.c
    sql/sqlite/sqlitehelp.cpp
    sql/sqlfield.cpp
    sql/sqlstatement.cpp
    #崩溃日志
    trace/crashreport.cpp
    trace/stacktrace.cpp
    #html解析
    html/htmldocument.cpp
    #http模块
    http/url.cpp
    http/httpcookie.cpp
    http/httprequest.cpp
    http/httpsession.cpp
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