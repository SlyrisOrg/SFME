macro(generate_local_test FILENAME EXENAME)
    set(SOURCES ${FILENAME} common_ecs_test.hpp)
    CREATE_UNIT_TEST(${EXENAME} SFME: "${SOURCES}")
    target_include_directories(${EXENAME} PUBLIC ${CMAKE_SOURCE_DIR}/SFME/scripting)
    target_link_libraries(${EXENAME} SFME::World)
endmacro()

macro(generate_local_plugin SOURCES EXECUTABLE)
    add_library(${EXECUTABLE} SHARED "${SOURCES}")
    target_link_libraries(${EXECUTABLE} SFME::World)
    set_target_properties(${EXECUTABLE}
            PROPERTIES
            ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/systems"
            LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/systems"
            RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/systems"
            LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/bin/systems"
            LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/bin/systems"
            RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/bin/systems"
            RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/bin/systems")
endmacro()

generate_local_test(ecs-system-test.cpp ecs-system-test)
generate_local_test(ecs-entity_test.cpp ecs-entity-test)
generate_local_plugin("ecs_plugin_foo.hpp;ecs_plugin_foo.cpp" ecs-plugin-foo)
generate_local_plugin("ecs_plugin_bar.hpp;ecs_plugin_bar.cpp" ecs-plugin-bar)
add_dependencies(ecs-system-test ecs-plugin-foo ecs-plugin-bar)
target_compile_definitions(ecs-system-test PRIVATE -DSILENT_SYSTEMS_MANAGER_LOGGING)