project(
    Stack
)

file(
    GLOB
    STACK_SOURCE_FILES
    *.c
)

add_library(
    ${PROJECT_NAME}
    STATIC
    ${STACK_SOURCE_FILES}
)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(
    ${PROJECT_NAME}
    PUBLIC
    Common
    LinkList
)