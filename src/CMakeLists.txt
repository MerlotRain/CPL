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

file(GLOB_RECURSE _sources ${CMAKE_CURRENT_LIST_DIR}/*.cpp  CONFIGURE_DEPEND)
file(GLOB_RECURSE _headers ${CMAKE_CURRENT_LIST_DIR}/*.h  CONFIGURE_DEPEND)
target_sources(libm2 PRIVATE ${_sources} ${_headers})
unset(_sources)
unset(_headers)

if(WIN32 AND NOT MINGW)
  set_source_files_properties(trace/stacktrace.cpp PROPERTIES COMPILE_FLAGS -wd4091)
endif()
