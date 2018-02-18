include(CMakeSources.cmake)

macro(create_ecs_example EXECUTABLE SOURCES)
    add_executable(${EXECUTABLE} "${SOURCES}")
    target_link_libraries(${EXECUTABLE} SFME::World)
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

macro(create_ecs_plugins EXECUTABLE SOURCES)
    add_library(${EXECUTABLE} SHARED "${SOURCES}")
    target_link_libraries(${EXECUTABLE} SFME::World)
    set_target_properties(${EXECUTABLE}
            PROPERTIES
            ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/example/systems"
            LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/example/systems"
            RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/example/systems"
            LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/bin/example/systems"
            LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/bin/example/systems"
            RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/bin/example/systems"
            RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/bin/example/systems")
endmacro()

create_ecs_example(sfme_ecs_system_enable_disable_example "${SFME_ECS_SYSTEM_ENABLE_DISABLE_EXAMPLE_SOURCES}")
create_ecs_example(sfme_ecs_system_create_example "${SFME_ECS_SYSTEM_ADD_EXAMPLE_SOURCES}")
create_ecs_example(sfme_ecs_system_update_example "${SFME_ECS_SYSTEM_UPDATE_EXAMPLE_SOURCES}")
create_ecs_plugins(sfme_ecs_foo_plugin_example "${SFME_ECS_PLUGINS_FOO_EXAMPLE_SOURCES}")
create_ecs_plugins(sfme_ecs_bar_plugin_example "${SFME_ECS_PLUGINS_BAR_EXAMPLE_SOURCES}")
add_dependencies(sfme_ecs_system_create_example sfme_ecs_foo_plugin_example sfme_ecs_bar_plugin_example)