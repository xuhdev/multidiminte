# Copyright (c) 2013 Hong Xu

cmake_minimum_required (VERSION 2.8)
project (multidiminte)

set (multidiminte_VERSION_MAJOR 0)
set (multidiminte_VERSION_MINOR 0)
set (multidiminte_VERSION_SUBMINOR 90)
set (multidiminte_VERSION_SUFFIX -alpha)

set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMake_Modules")

add_subdirectory (src)
add_subdirectory (doc)
