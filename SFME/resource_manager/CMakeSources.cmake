### Sources for the log module

set(MODULE_PATH
        ${CMAKE_CURRENT_SOURCE_DIR}/SFME/resource_manager)

set(MODULE_PUBLIC_HEADERS
        "${MODULE_PATH}/base_resource_manager.hpp"
        )

set(MODULE_PRIVATE_HEADERS
    "")

set(MODULE_SOURCES
        ${MODULE_PUBLIC_HEADERS}
        ${MODULE_PRIVATE_HEADERS})