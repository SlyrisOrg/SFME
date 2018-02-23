##! Modules sources
include(CMakeSources.cmake)

##! Modules path
set(MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})

##! Dependancies cmake confiuration files.
set(CMAKE_MODULE_PATH "${SFME_ROOT_DIRECTORY}/cmake_config/")

##! Find dependancies
find_package(SFML 2 COMPONENTS graphics system audio window)
find_package(OpenGL)

##! Module creation
CREATE_MODULE(SFME::SFML "${MODULE_SOURCES}" ${MODULE_PATH})

target_link_libraries(SFME-SFML INTERFACE ${SFML_LIBRARIES} ${SFML_DEPENDENCIES} SFME::ECS)
target_include_directories(SFME-SFML INTERFACE ${SFML_INCLUDE_DIR})
