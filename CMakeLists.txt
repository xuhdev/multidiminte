cmake_minimum_required (VERSION 2.8)
project (multidiminte)

set (multidiminte_VERSION_MAJOR 0)
set (multidiminte_VERSION_MINOR 1)
set (multidiminte_VERSION_SUBMINOR 0)

set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMake_Modules")

add_subdirectory(src)
