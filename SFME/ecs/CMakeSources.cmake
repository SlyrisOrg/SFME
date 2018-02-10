### Sources for the log module

set(MODULE_PATH
        ${CMAKE_CURRENT_SOURCE_DIR}/SFME/ecs)

set(MODULE_PUBLIC_HEADERS
        "${MODULE_PATH}/ecs.hpp"
        "${MODULE_PATH}/system_manager.hpp"
        "${MODULE_PATH}/system_base.hpp"
        "${MODULE_PATH}/system_type.hpp"
        )

set(MODULE_PRIVATE_HEADERS
        "${MODULE_PATH}/details/system_type_traits.hpp")

set(MODULE_SOURCES
        ${MODULE_PUBLIC_HEADERS}
        ${MODULE_PRIVATE_HEADERS})
