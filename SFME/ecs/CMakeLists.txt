include(CMakeSources.cmake)
set(MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})
CREATE_MODULE(SFME::ECS "${MODULE_SOURCES}" ${MODULE_PATH})
target_link_libraries(SFME-ECS INTERFACE SFME::Mediator SFME::Timer Core::Lib Core::Algorithm)
