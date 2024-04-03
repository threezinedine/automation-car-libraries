project(
    LinkList_Test
)

file(
    GLOB
    LINK_LIST_TEST_SOURCE_FILES
    *.c
)

add_executable(
    ${PROJECT_NAME}
    ${LINK_LIST_TEST_SOURCE_FILES}
)

target_link_libraries(
    ${PROJECT_NAME}
    LinkList
)