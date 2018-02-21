include(CMakeSources.cmake)
set(MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})
CREATE_MODULE(SFME::Input "${MODULE_SOURCES}" ${MODULE_PATH})
target_link_libraries(SFME-Input INTERFACE Core::Utils)
