find_package (GSL REQUIRED)
include_directories (${GSL_INCLUDE_DIRS})

set (multidiminte_LIBSRCS multi_dim_inte.c handle.c)

# shared library
add_library (multidiminte_shared SHARED ${multidiminte_LIBSRCS})
set_target_properties (multidiminte_shared PROPERTIES
    OUTPUT_NAME multidiminte
    SOVERSION 0
    VERSION
    ${multidiminte_VERSION_MAJOR}.${multidiminte_VERSION_MINOR}.${multidiminte_VERSION_SUBMINOR})
target_link_libraries (multidiminte_shared ${GSL_LIBRARIES})

# static library
add_library (multidiminte_static STATIC ${multidiminte_LIBSRCS})
set_target_properties (multidiminte_static PROPERTIES
    OUTPUT_NAME multidiminte_static
    SOVERSION 0
    VERSION
    ${multidiminte_VERSION_MAJOR}.${multidiminte_VERSION_MINOR}.${multidiminte_VERSION_SUBMINOR})
target_link_libraries (multidiminte_static ${GSL_LIBRARIES})

install (TARGETS multidiminte_shared multidiminte_static
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib)

# install header files
install (FILES gmdi.h DESTINATION include/gmdi)

# testing executable
link_directories (${CMAKE_CURRENT_BINARY_DIR})
add_executable (test test.c)
target_link_libraries (test multidiminte)
add_dependencies (test multidiminte_shared)
set_target_properties (test PROPERTIES OUTPUT_NAME test)
