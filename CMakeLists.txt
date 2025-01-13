cmake_minimum_required(VERSION 3.10)
project(geoport)

add_library(geoport SHARED)

add_subdirectory(include)
add_subdirectory(src)

