set(SOURCES world-test.cpp world_common_test.hpp)
CREATE_UNIT_TEST(world-test SFME: "${SOURCES}")
target_link_libraries(world-test SFME::World)