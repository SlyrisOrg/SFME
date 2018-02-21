### Sources for the log module

set(MODULE_PATH
        ${CMAKE_CURRENT_SOURCE_DIR}/SFME/input)

set(MODULE_PUBLIC_HEADERS
        "${MODULE_PATH}/input.hpp"
        "${MODULE_PATH}/keyboard.hpp"
        "${MODULE_PATH}/mouse.hpp"
        )

set(MODULE_PRIVATE_HEADERS
    "")

set(MODULE_SOURCES
        ${MODULE_PUBLIC_HEADERS}
        ${MODULE_PRIVATE_HEADERS})