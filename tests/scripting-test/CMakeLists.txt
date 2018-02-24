set(SOURCES scripting-test.cpp scripting_world_test.hpp)
CREATE_UNIT_TEST(scripting-test SFME: "${SOURCES}")
target_link_libraries(scripting-test SFME::Scripting SFME::World)

##! Uncomment this if you want to have a compilation time information on msvc
#if (MSVC)
#    target_compile_options(scripting-test PUBLIC /d2cgsummary)
#endif()