### Sources for the log module

set(MODULE_PATH
        ${CMAKE_CURRENT_SOURCE_DIR}/SFME/scripting)

set(MODULE_PUBLIC_HEADERS
        "${MODULE_PATH}/scripting.hpp"
        "${MODULE_PATH}/scripting_engine.hpp"
        "${MODULE_PATH}/scripting_lua.hpp"
        "${MODULE_PATH}/scripting_base.hpp"
        )

set(MODULE_PRIVATE_HEADERS
    "")

set(MODULE_SOURCES
        ${MODULE_PUBLIC_HEADERS}
        ${MODULE_PRIVATE_HEADERS})