include(CMakeSources.cmake)
set(MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})
CREATE_MODULE(SFME::World "${MODULE_SOURCES}" ${MODULE_PATH})
target_link_libraries(SFME-World INTERFACE SFME::ECS SFME::Scripting SFME::Mediator)