### Sources for the log module

set(MODULE_PATH
        ${CMAKE_CURRENT_SOURCE_DIR}/SFME/ecs)

set(MODULE_PUBLIC_HEADERS
        "${MODULE_PATH}/ecs.hpp"
        "${MODULE_PATH}/entity_manager.hpp"
        "${MODULE_PATH}/system_manager.hpp"
        "${MODULE_PATH}/system_base.hpp"
        "${MODULE_PATH}/system_type.hpp"
        "${MODULE_PATH}/system.hpp"
        "${MODULE_PATH}/common_components.hpp"
        )

set(MODULE_PRIVATE_HEADERS
        "${MODULE_PATH}/details/system_type_traits.hpp"
        "${MODULE_PATH}/details/system_type_id.hpp"
        "${MODULE_PATH}/details/entity.hpp"
        "${MODULE_PATH}/details/utils.hpp")

set(MODULE_SOURCES
        ${MODULE_PUBLIC_HEADERS}
        ${MODULE_PRIVATE_HEADERS})
