### Sources for the log module

set(MODULE_PATH
        ${CMAKE_CURRENT_SOURCE_DIR}/SFME/sfml)

set(MODULE_PUBLIC_HEADERS
        "${MODULE_PATH}/systems/graphical.hpp"
        "${MODULE_PATH}/systems/event.hpp"
        "${MODULE_PATH}/systems.hpp"
        "${MODULE_PATH}/resource_manager.hpp"
        "${MODULE_PATH}/components.hpp"
        "${MODULE_PATH}/components/drawable.hpp"
        "${MODULE_PATH}/sfml.hpp"
        )

set(MODULE_PRIVATE_HEADERS
    "")

set(MODULE_SOURCES
        ${MODULE_PUBLIC_HEADERS}
        ${MODULE_PRIVATE_HEADERS})