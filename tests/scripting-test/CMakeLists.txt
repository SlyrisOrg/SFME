set(SOURCES scripting-test.cpp scripting_world_test.hpp)
CREATE_UNIT_TEST(scripting-test SFME: "${SOURCES}")
target_link_libraries(scripting-test SFME::World)