### Sources for the log module

set(MODULE_PATH
        ${CMAKE_CURRENT_SOURCE_DIR}/SFME/scripting)

set(MODULE_PUBLIC_HEADERS
        "${MODULE_PATH}/world.hpp"
        )

set(MODULE_PRIVATE_HEADERS
    "")

set(MODULE_SOURCES
        ${MODULE_PUBLIC_HEADERS}
        ${MODULE_PRIVATE_HEADERS})