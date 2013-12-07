# Generate documentation

find_package(Doxygen)

if (DOXYGEN_FOUND)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in
        ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    add_custom_command(
        OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/html/index.html
        COMMAND ${DOXYGEN_EXECUTABLE} "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile"
        MAIN_DEPENDENCY
        ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in
        DEPENDS
        ${PROJECT_SOURCE_DIR}/src/gmdi.h
        ${PROJECT_SOURCE_DIR}/README.md
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

    add_custom_target(doc ALL DEPENDS
        ${CMAKE_CURRENT_BINARY_DIR}/html/index.html)

    install(DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/html"
        DESTINATION share/doc/multidiminte)
endif()
