if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "Prevented in-tree built. Please create a build directory outside of the source code and call cmake from there")
endif ()


cmake_minimum_required(VERSION 3.10)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

##! Project
project(SFME)

##! Prerequisites CTEST
enable_testing()

##! Core-V2
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/vendor/core-v2/cmake)
add_subdirectory(vendor/core-v2)
include(${CMAKE_MODULE_PATH}/library.cmake)

##! SFME_MODULE_PATH
set(SFME_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake_config)

##! SFME CMake file configuration
include(${SFME_MODULE_PATH}/${PROJECT_NAME}.cmake)

option(SFME_BUILD_TESTS "Build tests of SFME C++ Engine" OFF)
option(SFME_BUILD_EXAMPLES "Build the examples of SFME C++ Engine" OFF)

add_subdirectory(${PROJECT_NAME})

##! Project Tests
if (SFME_BUILD_TESTS)
    add_subdirectory(tests)
endif ()

##! Demo project, contains all the documented examples.
if (SFME_BUILD_EXAMPLES)
    set(SFME_DEMO_PATH ${CMAKE_SOURCE_DIR}/example)
    add_subdirectory(example)
endif ()
