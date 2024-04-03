project(
    Common
)

file(
    GLOB 
    COMMON_SOURCE_FILES
    *.c
)

add_library(
    ${PROJECT_NAME}
    STATIC
    ${COMMON_SOURCE_FILES}
)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
)