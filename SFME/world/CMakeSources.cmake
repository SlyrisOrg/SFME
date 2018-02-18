### Sources for the log module

set(MODULE_PATH
        ${CMAKE_CURRENT_SOURCE_DIR}/SFME/world)

set(MODULE_PUBLIC_HEADERS
        "${MODULE_PATH}/world.hpp"
        "${MODULE_PATH}/base_world.hpp"
        )

set(MODULE_PRIVATE_HEADERS
    "${MODULE_PATH}/details/world_traits.hpp")

set(MODULE_SOURCES
        ${MODULE_PUBLIC_HEADERS}
        ${MODULE_PRIVATE_HEADERS})