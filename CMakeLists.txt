cmake_minimum_required(VERSION 3.10)

project(
    AutomationCarLibraries
)

option(DEBUG "Enable debug mode" OFF)

if (DEBUG)
    add_compile_definitions(_DEBUG)
endif()

set(
    LIBRARY_FOLDERS
    Common
    LinkList
    Queue
)

foreach(LIBRARY_FOLDER ${LIBRARY_FOLDERS})
    add_subdirectory(${LIBRARY_FOLDER})
    if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${LIBRARY_FOLDER}_Test)
        add_subdirectory(${LIBRARY_FOLDER}_Test)
    endif()
endforeach()
