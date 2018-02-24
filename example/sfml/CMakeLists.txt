set(SOURCES main.cpp)

add_executable(sfme_sfml_example ${SOURCES})
target_link_libraries(sfme_sfml_example SFME::SFML SFME::World SFME::ECS SFME::Scripting SFME::ResourceManager)

set_target_properties(sfme_sfml_example
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
        LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/bin"
        LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/bin"
        RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/bin"
        RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/bin"
        PDB_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
        PDB_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/bin"
        PDB_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/bin")

if (MSVC)
    target_compile_options(sfme_sfml_example PUBLIC /bigobj)
endif()

if (CLANG OR GCC)
    target_compile_options(sfme_sfml_example PUBLIC -ftime-report)
endif()