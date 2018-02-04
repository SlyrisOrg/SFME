### Sources for the log module

set(MODULE_PATH
        ${CMAKE_CURRENT_SOURCE_DIR}/SFME/mediator)

set(MODULE_PUBLIC_HEADERS
        ${MODULE_PATH}/mediator.hpp
        ${MODULE_PATH}/receiver.hpp
        ${MODULE_PATH}/event_manager.hpp
        ${MODULE_PATH}/base_event.hpp
        ${MODULE_PATH}/config.hpp
        )

set(MODULE_PRIVATE_HEADERS
        "${MODULE_PATH}/details/event_callback_wrapper.hpp"
        "${MODULE_PATH}/details/type_id.hpp"
        "${MODULE_PATH}/details/type_traits.hpp")

set(MODULE_SOURCES
        ${MODULE_PUBLIC_HEADERS}
        ${MODULE_PRIVATE_HEADERS})
