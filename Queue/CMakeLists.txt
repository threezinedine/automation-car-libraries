project(
    Queue
)

file(
    GLOB
    QUEUE_SOURCE_FILES
    *.c
)

add_library(
    ${PROJECT_NAME}
    STATIC
    ${QUEUE_SOURCE_FILES}
)

target_link_libraries(
    ${PROJECT_NAME}
    PUBLIC 
    Common
    LinkList
)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)