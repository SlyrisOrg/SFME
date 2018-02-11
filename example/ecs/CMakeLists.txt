include(CMakeSources.cmake)

macro(create_ecs_example EXECUTABLE SOURCES)
    add_executable(${EXECUTABLE} "${SOURCES}")
    target_link_libraries(${EXECUTABLE} SFME::ECS)
    set_target_properties(${EXECUTABLE}
            PROPERTIES
            ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
            LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
            RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
            LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/bin"
            LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/bin"
            RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/bin"
            RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/bin")
endmacro()

create_ecs_example(sfme_ecs_system_add_example "${SFME_ECS_SYSTEM_ADD_EXAMPLE_SOURCES}")
create_ecs_example(sfme_ecs_system_update_example "${SFME_ECS_SYSTEM_UPDATE_EXAMPLE_SOURCES}")