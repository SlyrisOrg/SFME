include(CMakeSources.cmake)
set(MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})
CREATE_MODULE(SFME::Timer "${MODULE_SOURCES}" ${MODULE_PATH})
#target_link_libraries(SFME-Mediator INTERFACE Core::Log)
